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
    QString clientId();
    QString clientSecret();

signals:
    void authenticated();

private:
    QString m_baseUrl;
    QString m_clientId;
    QString m_clientSecret;
    QSettings m_settings;
    QNetworkAccessManager *m_manager;
    QOAuth2AuthorizationCodeFlow *m_oauth;
};
