#include "traktclient.hpp"
#include <QUrlQuery>
#include <QOAuthHttpServerReplyHandler>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopServices>
#include <QVariant>
#include <QNetworkReply>

TraktClient::TraktClient()
    : m_baseUrl("https://api.trakt.tv"), m_settings(this),
      m_isAuthenticated(false) {

    m_manager = new QNetworkAccessManager(this);
    m_oauth = new QOAuth2AuthorizationCodeFlow(this);

    m_clientId = m_settings.value("app/client_id").toString();
    m_clientSecret = m_settings.value("app/client_secret").toString();

    if (m_settings.contains("auth/access_token")) {
        m_oauth->setToken(m_settings.value("auth/access_token").toString());
        m_oauth->setRefreshToken(
            m_settings.value("auth/refresh_token").toString());
        m_expiresAt = QDateTime::fromString(
            m_settings.value("auth/expires_at").toString(), Qt::ISODate);
        m_isAuthenticated = true;
    }
}

bool TraktClient::isAuthenticated() { return m_isAuthenticated; }

void TraktClient::authenticate() {
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

    auto replyHandler =
        new QOAuthHttpServerReplyHandler(QHostAddress::Any, 3000, this);
    replyHandler->setCallbackPath("/callback");
    m_oauth->setReplyHandler(replyHandler);

    connect(m_oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this,
            &QDesktopServices::openUrl);

    connect(m_oauth, &QAbstractOAuth::granted, this, [=]() {
        m_settings.setValue("auth/access_token", m_oauth->token());
        m_settings.setValue("auth/refresh_token", m_oauth->refreshToken());
        m_settings.setValue("auth/expires_at",
                            m_oauth->expirationAt().toString(Qt::ISODate));
        m_expiresAt = m_oauth->expirationAt();
        emit authenticated();
    });

    m_oauth->grant();
}

bool TraktClient::shouldRefreshToken() {
    return QDateTime::currentDateTime() >= m_expiresAt;
}

QNetworkReply *TraktClient::get(QString endpoint,
                                QHash<QString, QString> params, bool auth) {

    if (shouldRefreshToken()) {
        m_oauth->refreshTokens();
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

    if (auth)
        req.setRawHeader("Authorization", m_oauth->token().toLatin1());

    return m_manager->get(req);
}

void TraktClient::search(QString query) {
    auto *reply = get("/search/show", {{"query", query}});
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QList<StandardShow> results;
        for (const auto &show : doc.array()) {
            results.append(StandardShow::fromJson(show.toObject()));
        }
        emit searchDone(results);
    });
}

void TraktClient::getShowDetails(int traktId) {
    auto *reply =
        get(QString("/shows/%1").arg(traktId), {{"extended", "full"}});
    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        ShowDetails show = ShowDetails::fromJson(doc.object());
        getShowSeasons(show);
    });
}

void TraktClient::getShowSeasons(ShowDetails show) {
    auto *reply = get(QString("/shows/%1/seasons").arg(show.ids.trakt),
                      {{"extended", "full"}});

    connect(reply, &QNetworkReply::finished, this, [=]() {
        reply->deleteLater();

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        auto result = std::make_shared<QList<SeasonDetails>>();

        int i = 0;
        auto arr = doc.array();
        auto pending = std::make_shared<int>(arr.size() - 1);

        for (const auto &season : arr) {
            auto seasonDetails = std::make_shared<SeasonDetails>(
                SeasonDetails::fromJson(season.toObject()));
            auto *reply =
                get(QString("/shows/%1/seasons/%2").arg(show.ids.trakt).arg(i));

            ++i;

            connect(reply, &QNetworkReply::finished, this, [=]() {
                QList<StandardEpisode> episodes;
                reply->deleteLater();

                QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

                for (const auto &episode : doc.array()) {
                    episodes.append(
                        StandardEpisode::fromJson(episode.toObject()));
                }

                seasonDetails->episodes = episodes;

                result->append(*seasonDetails);
                if (--(*pending) == 0) {
                    std::sort(
                        result->begin(), result->end(),
                        [](const SeasonDetails &a, const SeasonDetails &b) {
                            return a.number < b.number;
                        });
                    emit showDetailsReady(show, *result);
                }
            });
        }
    });
}
