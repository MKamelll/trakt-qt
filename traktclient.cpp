#include "traktclient.hpp"
#include <QUrlQuery>
#include <QOAuthHttpServerReplyHandler>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopServices>
#include <QVariant>

TraktClient::TraktClient(QObject *parent)
    : QObject(parent), m_baseUrl("https://api.trakt.tv"), m_settings(this) {

    m_manager = new QNetworkAccessManager(this);
    m_clientId = m_settings.value("app/client_id").toString();
    m_clientSecret = m_settings.value("app/client_secret").toString();

    if (m_settings.contains("auth/access_token")) {
        m_oauth->setToken(m_settings.value("auth/access_token").toString());
        m_oauth->setRefreshToken(
            m_settings.value("auth/refresh_token").toString());
        m_expiresAt = QDateTime::fromString(
            m_settings.value("auth/expires_at").toString(), Qt::ISODate);
    } else {
        emit needAuthentication();
    }
}

void TraktClient::authenticate() {
    m_oauth = new QOAuth2AuthorizationCodeFlow(this);
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

QNetworkReply *TraktClient::get(QString &endpoint,
                                QHash<QString, QString> params, bool auth) {}
