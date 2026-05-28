#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QOAuth2AuthorizationCodeFlow>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

struct StandardIDs {
    int trakt;
    QString slug;
    int tvdb;
    QString imdb;
    QString tmdb;
};

struct StandardShow {
    QString title;
    int year;
    StandardIDs ids;

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

struct ShowDetails {
    QString title;
    int year;
    StandardIDs ids;
    QString tagLine;
    QString overview;
    QDateTime firstAired;
    int runtime;
    QString network;
    QString country;
    double rating;
    QList<QString> languages;
    QList<QString> genres;
    QString originalTitle;

    static ShowDetails fromJson(QJsonObject obj) {
        ShowDetails s;
        s.title = obj["title"].toString();
        s.year = obj["year"].toInt();
        s.ids.trakt = obj["ids"].toObject()["trakt"].toInt();
        s.ids.slug = obj["ids"].toObject()["slug"].toString();
        s.ids.tvdb = obj["ids"].toObject()["tvdb"].toInt();
        s.ids.imdb = obj["ids"].toObject()["imdb"].toString();
        s.ids.tmdb = obj["ids"].toObject()["tmdb"].toString();
        s.tagLine = obj["tagline"].toString();
        s.overview = obj["overview"].toString();
        s.firstAired =
            QDateTime::fromString(obj["first_aired"].toString(), Qt::ISODate);
        s.runtime = obj["runtime"].toInt();
        s.network = obj["network"].toString();
        s.country = obj["country"].toString();
        s.rating = obj["rating"].toDouble();
        s.languages = {};
        for (const auto &lang : obj["languages"].toArray()) {
            s.languages.append(lang.toString());
        }
        s.genres = {};
        for (const auto &lang : obj["genres"].toArray()) {
            s.genres.append(lang.toString());
        }
        s.originalTitle = obj["original_title"].toString();
        return s;
    }

    friend QDebug operator<<(QDebug debug, const ShowDetails &show) {
        debug << "ShowDetails(title: " << show.title << ", year: " << show.year
              << ", overview: " << show.overview << ")";
        return debug;
    }
};

struct StandardEpisode {
    int season;
    int number;
    QString title;
    StandardIDs ids;

    static StandardEpisode fromJson(QJsonObject obj) {
        StandardEpisode s;
        s.title = obj["title"].toString();
        s.ids.trakt = obj["ids"].toObject()["trakt"].toInt();
        s.ids.slug = obj["ids"].toObject()["slug"].toString();
        s.ids.tvdb = obj["ids"].toObject()["tvdb"].toInt();
        s.ids.imdb = obj["ids"].toObject()["imdb"].toString();
        s.ids.tmdb = obj["ids"].toObject()["tmdb"].toString();
        s.number = obj["number"].toInt();
        s.season = obj["season"].toInt();
        return s;
    }

    friend QDebug operator<<(QDebug debug, const StandardEpisode &episode) {
        debug << "StandardEpisode(title: " << episode.title
              << ", number: " << episode.number
              << ", season: " << episode.season << ")";
        return debug;
    }
};

struct SeasonDetails {
    int number;
    StandardIDs ids;
    double rating;
    int episodeCount;
    QString title;
    QString overview;
    QDateTime firstAired;
    QString network;
    QString originalTitle;
    QList<StandardEpisode> episodes;

    static SeasonDetails fromJson(QJsonObject obj) {
        SeasonDetails s;
        s.title = obj["title"].toString();
        s.ids.trakt = obj["ids"].toObject()["trakt"].toInt();
        s.ids.slug = obj["ids"].toObject()["slug"].toString();
        s.ids.tvdb = obj["ids"].toObject()["tvdb"].toInt();
        s.ids.imdb = obj["ids"].toObject()["imdb"].toString();
        s.ids.tmdb = obj["ids"].toObject()["tmdb"].toString();
        s.overview = obj["overview"].toString();
        s.firstAired =
            QDateTime::fromString(obj["first_aired"].toString(), Qt::ISODate);
        s.network = obj["network"].toString();
        s.rating = obj["rating"].toDouble();
        s.originalTitle = obj["original_title"].toString();
        s.number = obj["number"].toInt();
        return s;
    }

    friend QDebug operator<<(QDebug debug, const SeasonDetails &season) {
        debug << "SeasonDetails(title: " << season.title
              << ", number: " << season.number
              << ", overview: " << season.overview << ")";
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
    void getShowDetails(int traktId);
    void getShowSeasons(int traktId);

signals:
    void authenticated();
    void searchDone(QList<StandardShow> results);
    void showDetailsReady(ShowDetails result);
    void showSeasonsReady(QList<SeasonDetails> results);

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
