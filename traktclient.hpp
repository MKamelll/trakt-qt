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

struct EpisodeDetails {
    int season;
    int number;
    QString title;
    StandardIDs ids;
    QString overview;
    QDateTime firstAired;
    double rating;
    int runtime;
    QString originalTitle;

    static EpisodeDetails fromJson(QJsonObject obj) {
        EpisodeDetails s;
        s.season = obj["season"].toInt();
        s.number = obj["number"].toInt();
        s.title = obj["title"].toString("N/A");
        s.ids.trakt = obj["ids"].toObject()["trakt"].toInt();
        s.ids.slug = obj["ids"].toObject()["slug"].toString("N/A");
        s.ids.tvdb = obj["ids"].toObject()["tvdb"].toInt();
        s.ids.imdb = obj["ids"].toObject()["imdb"].toString("N/A");
        s.ids.tmdb = obj["ids"].toObject()["tmdb"].toString("N/A");
        s.overview = obj["overview"].toString("N/A");
        s.firstAired = QDateTime::fromString(obj["first_aired"].toString("N/A"),
                                             Qt::ISODate);
        s.rating = obj["rating"].toDouble();
        s.runtime = obj["runtime"].toInt();
        s.originalTitle = obj["original_title"].toString("N/A");
        return s;
    }

    friend QDebug operator<<(QDebug debug, const EpisodeDetails &episode) {
        debug << "EpisodeDetails(title: " << episode.title
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
    QList<EpisodeDetails> episodes;

    static SeasonDetails fromJson(QJsonObject obj) {
        SeasonDetails s;
        s.title = obj.value("title").toString("N/A");
        s.ids.trakt = obj.value("ids").toObject().value("trakt").toInt();
        s.ids.slug = obj.value("ids").toObject().value("slug").toString("N/A");
        s.ids.tvdb = obj.value("ids").toObject().value("tvdb").toInt();
        s.ids.imdb = obj.value("ids").toObject().value("imdb").toString("N/A");
        s.ids.tmdb = obj.value("ids").toObject().value("tmdb").toString("N/A");
        s.overview = obj.value("overview").toString("N/A");
        s.firstAired = QDateTime::fromString(
            obj.value("first_aired").toString("N/A"), Qt::ISODate);
        s.network = obj.value("network").toString("N/A");
        s.rating = obj.value("rating").toDouble();
        s.originalTitle = obj.value("original_title").toString("N/A");
        s.number = obj.value("number").toInt();
        s.episodeCount = obj.value("episode_count").toInt();
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

signals:
    void authenticated();
    void searchDone(QList<StandardShow> results);
    void showDetailsReady(ShowDetails show, QList<SeasonDetails> seasons);

private slots:
    void saveTokens();

private:
    TraktClient();
    TraktClient(const TraktClient &) = delete;
    TraktClient &operator=(const TraktClient &) = delete;
    bool shouldRefreshToken();
    void getWithAuth(QString endpoint,
                     std::function<void(QNetworkReply *)> callback);
    void getWithAuth(QString endpoint, QHash<QString, QString> params,
                     std::function<void(QNetworkReply *)> callback);
    void get(QString endpoint, QHash<QString, QString> params,
             std::function<void(QNetworkReply *)> callback);
    void get(QString endpoint, std::function<void(QNetworkReply *)> callback);

    bool loadTokens();
    void getShowSeasons(ShowDetails show);
    void getSeasonEpisodes(ShowDetails show,
                           std::shared_ptr<SeasonDetails> seasonDetails,
                           std::function<void(QList<EpisodeDetails>)> callback);

    QString m_baseUrl;
    QString m_clientId;
    QString m_clientSecret;
    QSettings m_settings;
    QNetworkAccessManager *m_manager;
    QOAuth2AuthorizationCodeFlow *m_oauth;
    QDateTime m_expiresAt;
    bool m_isAuthenticated;
    bool m_isRefreshingToken;
};
