#include "traktclient.hpp"
#include <QUrlQuery>
#include <QOAuthHttpServerReplyHandler>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopServices>
#include <QVariant>
#include <QNetworkReply>
#include <QtLogging>

TraktClient::TraktClient()
    : m_baseUrl("https://api.trakt.tv"), m_settings(this),
      m_isAuthenticated(false) {

    m_manager = new QNetworkAccessManager(this);
    m_oauth = new QOAuth2AuthorizationCodeFlow(this);

    m_clientId = m_settings.value("app/client_id").toString();
    m_clientSecret = m_settings.value("app/client_secret").toString();

    m_oauth->setClientIdentifier(m_clientId);
    m_oauth->setClientIdentifierSharedKey(m_clientSecret);
    m_oauth->setAuthorizationUrl(QUrl(m_baseUrl + "/oauth/authorize"));
    m_oauth->setTokenUrl(QUrl(m_baseUrl + "/oauth/token"));
    m_oauth->setAutoRefresh(true);
    m_oauth->setRequestedScopeTokens({"public"});
    m_oauth->setModifyParametersFunction(
        [](QAbstractOAuth::Stage stage, QMultiMap<QString, QVariant> *params) {
            if (stage == QAbstractOAuth::Stage::RequestingAuthorization) {
                params->replace("redirect_uri",
                                "http://localhost:3000/callback");
            }
        });

    m_isAuthenticated = loadTokens();

    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::tokenChanged, this,
            &TraktClient::saveTokens);

    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this,
            &QDesktopServices::openUrl);

    connect(m_oauth, &QAbstractOAuth::granted, this, [=]() {
        saveTokens();
        emit authenticated();
    });
}

bool TraktClient::loadTokens() {
    if (m_settings.contains("auth/access_token")) {
        m_oauth->setToken(m_settings.value("auth/access_token").toString());
        m_oauth->setRefreshToken(
            m_settings.value("auth/refresh_token").toString());
        m_expiresAt = QDateTime::fromString(
            m_settings.value("auth/expires_at").toString(), Qt::ISODate);
        return true;
    }
    return false;
}

void TraktClient::saveTokens() {
    m_settings.setValue("auth/access_token", m_oauth->token());
    m_settings.setValue("auth/refresh_token", m_oauth->refreshToken());
    m_settings.setValue("auth/expires_at",
                        m_oauth->expirationAt().toString(Qt::ISODate));
    m_expiresAt = m_oauth->expirationAt();
}

bool TraktClient::isAuthenticated() { return m_isAuthenticated; }

void TraktClient::authenticate() {
    auto replyHandler =
        new QOAuthHttpServerReplyHandler(QHostAddress::Any, 3000, this);
    replyHandler->setCallbackPath("/callback");
    m_oauth->setReplyHandler(replyHandler);
    m_oauth->grant();
}

bool TraktClient::shouldRefreshToken() {
    return QDateTime::currentDateTime() >= m_expiresAt;
}

void TraktClient::get(QString endpoint, QHash<QString, QString> params,
                      std::function<void(QNetworkReply *)> callback) {

    QUrl url(m_baseUrl + endpoint);
    QUrlQuery query;
    for (const auto &[key, value] : std::as_const(params).asKeyValueRange()) {
        query.addQueryItem(key, value);
    }
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setRawHeader("Content-Type", "application/json");
    req.setRawHeader("trakt-api-version", "2");
    req.setRawHeader("trakt-api-key", m_clientId.toUtf8());

    callback(m_manager->get(req));
}

void TraktClient::get(QString endpoint,
                      std::function<void(QNetworkReply *)> callback) {

    QUrl url(m_baseUrl + endpoint);
    QNetworkRequest req(url);
    req.setRawHeader("Content-Type", "application/json");
    req.setRawHeader("trakt-api-version", "2");
    req.setRawHeader("trakt-api-key", m_clientId.toUtf8());

    callback(m_manager->get(req));
}

void TraktClient::getWithAuth(QString endpoint, QHash<QString, QString> params,
                              std::function<void(QNetworkReply *)> callback) {

    if (shouldRefreshToken()) {
        if (!m_isRefreshingToken) {
            m_isRefreshingToken = true;
            m_oauth->refreshTokens();
            qInfo() << "TraktClient: Refreshing tokens" << Qt::endl;
        }

        connect(
            m_oauth, &QOAuth2AuthorizationCodeFlow::tokenChanged, this,
            [=]() {
                m_isRefreshingToken = false;
                getWithAuth(endpoint, params, callback);
            },
            Qt::SingleShotConnection);
        return;
    }

    QUrl url(m_baseUrl + endpoint);
    QUrlQuery query;
    for (const auto &[key, value] : std::as_const(params).asKeyValueRange()) {
        query.addQueryItem(key, value);
    }
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setRawHeader("Content-Type", "application/json");
    req.setRawHeader("trakt-api-version", "2");
    req.setRawHeader("trakt-api-key", m_clientId.toUtf8());
    req.setRawHeader("Authorization", "Bearer " + m_oauth->token().toLatin1());

    callback(m_manager->get(req));
}

void TraktClient::getWithAuth(QString endpoint,
                              std::function<void(QNetworkReply *)> callback) {

    if (shouldRefreshToken()) {
        if (!m_isRefreshingToken) {
            m_isRefreshingToken = true;
            m_oauth->refreshTokens();
            qInfo() << "TraktClient: Refreshing tokens" << Qt::endl;
        }

        connect(
            m_oauth, &QOAuth2AuthorizationCodeFlow::tokenChanged, this,
            [=]() {
                m_isRefreshingToken = false;
                getWithAuth(endpoint, callback);
            },
            Qt::SingleShotConnection);
        return;
    }

    QUrl url(m_baseUrl + endpoint);
    QNetworkRequest req(url);
    req.setRawHeader("Content-Type", "application/json");
    req.setRawHeader("trakt-api-version", "2");
    req.setRawHeader("trakt-api-key", m_clientId.toUtf8());
    req.setRawHeader("Authorization", "Bearer " + m_oauth->token().toLatin1());

    callback(m_manager->get(req));
}

void TraktClient::search(QString query) {
    get("/search/show", {{"query", query}}, [=](QNetworkReply *reply) {
        connect(reply, &QNetworkReply::finished, this, [=]() {
            reply->deleteLater();
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            QList<StandardShow> results;
            for (const auto &show : doc.array()) {
                results.append(StandardShow::fromJson(show.toObject()));
            }
            emit searchDone(results);
        });
    });
}

void TraktClient::getShowDetails(int traktId) {
    get(QString("/shows/%1").arg(traktId), {{"extended", "full"}},
        [=](QNetworkReply *reply) {
            connect(reply, &QNetworkReply::finished, this, [=]() {
                reply->deleteLater();
                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
                ShowDetails show = ShowDetails::fromJson(doc.object());
                getShowSeasons(show);
            });
        });
}

void TraktClient::getShowSeasons(ShowDetails show) {
    get(QString("/shows/%1/seasons").arg(show.ids.trakt),
        {{"extended", "full"}}, [=](QNetworkReply *reply) {
            connect(reply, &QNetworkReply::finished, this, [=]() {
                reply->deleteLater();

                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

                auto result = std::make_shared<QList<SeasonDetails>>();

                auto arr = doc.array();
                auto pending = std::make_shared<int>(arr.size());

                for (const auto &season : arr) {
                    auto seasonDetails = std::make_shared<SeasonDetails>(
                        SeasonDetails::fromJson(season.toObject()));

                    getSeasonEpisodes(
                        show, seasonDetails,
                        [=](QList<EpisodeDetails> episodes) {
                            seasonDetails->episodes = episodes;
                            result->append(*seasonDetails);
                            if (--(*pending) == 0) {
                                std::sort(result->begin(), result->end(),
                                          [](const SeasonDetails &a,
                                             const SeasonDetails &b) {
                                              return a.number < b.number;
                                          });
                                emit showDetailsReady(show, *result);
                            }
                        });
                }
            });
        });
}

void TraktClient::getSeasonEpisodes(
    ShowDetails show, std::shared_ptr<SeasonDetails> seasonDetails,
    std::function<void(QList<EpisodeDetails>)> callback) {

    get(QString("/shows/%1/seasons/%2")
            .arg(show.ids.trakt)
            .arg(seasonDetails->number),
        {{"extended", "full"}}, [=](QNetworkReply *reply) {
            connect(reply, &QNetworkReply::finished, this, [=]() {
                QList<EpisodeDetails> episodes;
                reply->deleteLater();

                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

                for (const auto &episode : doc.array()) {
                    episodes.append(
                        EpisodeDetails::fromJson(episode.toObject()));
                }

                callback(episodes);
            });
        });
}
