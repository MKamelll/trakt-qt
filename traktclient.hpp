#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QOAuth2AuthorizationCodeFlow>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

struct StandardShow {
    QString title;
    int year;
    struct {
        int trakt;
        QString slug;
        int tvdb;
        QString imdb;
        QString tmdb;
    } ids;

    static StandardShow fromJson(QJsonObject obj) {
        StandardShow s;
        s.title = obj["show"].toObject()["title"].toString();
        s.year = obj["show"].toObject()["year"].toInt();
        s.ids.trakt = obj["show"].toObject()["ids"].toObject()["trakt"].toInt();
        s.ids.slug =
            obj["show"].toObject()["ids"].toObject()["slug"].toString();
        s.ids.tvdb = obj["show"].toObject()["ids"].toObject()["tvdb"].toInt();
        s.ids.imdb =
            obj["show"].toObject()["ids"].toObject()["imdb"].toString();
        s.ids.tmdb =
            obj["show"].toObject()["ids"].toObject()["tmdb"].toString();
        return s;
    }

    friend QDebug operator<<(QDebug debug, const StandardShow &show) {
        debug << "StandardShow(title: " << show.title << ", year: " << show.year
              << ")";
        return debug;
    }
};

class TraktClient : public QObject {
    Q_OBJECT
public:
    static TraktClient *instance() {
        static TraktClient inst;
        return &inst;
    }
    void authenticate();
    bool isAuthenticated();
    void search(QString query);

signals:
    void authenticated();
    void searchDone(QList<StandardShow> results);

private:
    TraktClient();
    TraktClient(const TraktClient &) = delete;
    TraktClient &operator=(const TraktClient &) = delete;

    bool shouldRefreshToken();
    QNetworkReply *get(QString endpoint, QHash<QString, QString> params = {},
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
