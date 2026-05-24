#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QOAuth2AuthorizationCodeFlow>
#include <QSettings>

class TraktClient : public QObject {
    Q_OBJECT
public:
    TraktClient(QObject *parent = nullptr);

    void authenticate();
    bool isAuthenticated();

signals:
    void authenticated();

private:
    bool shouldRefreshToken();
    QNetworkReply *get(QString &endpoint, QHash<QString, QString> params = {},
                       bool auth = false);

    QString m_baseUrl;
    QString m_clientId;
    QString m_clientSecret;
    QSettings m_settings;
    QNetworkAccessManager *m_manager;
    QOAuth2AuthorizationCodeFlow *m_oauth;
    QDateTime m_expiresAt;
    bool m_isAuthenticated;
};
