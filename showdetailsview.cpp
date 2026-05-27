#include "showdetailsview.hpp"
#include <QGridLayout>
#include <QVBoxLayout>

ShowDetailsView::ShowDetailsView(ShowDetails show, QWidget *parent)
    : QWidget(parent) {

    setWindowTitle(show.title);
    resize(640, 420);

    auto *grid = new QGridLayout;

    m_titleLabel = new QLabel(QString("Title: %1").arg(show.title));
    m_yearLabel = new QLabel(QString("Year: %1").arg(show.year));
    m_overviewLabel = new QLabel(QString("Overview: %1").arg(show.overview));
    m_overviewLabel->setWordWrap(true);
    m_taglineLabel = new QLabel(QString("TagLine: %1").arg(show.tagLine));
    m_firstAiredLabel = new QLabel(
        QString("First Aired: %1")
            .arg(show.firstAired.toString("dddd, MMMM d, yyyy - hh:mm AP t")));
    m_runtimeLabel =
        new QLabel(QString("Runtime: %1 minutes").arg(show.runtime));
    m_networkLabel = new QLabel(QString("Network: %1").arg(show.network));
    m_countryLabel = new QLabel(QString("Country: %1").arg(show.country));
    m_ratingLabel = new QLabel(QString("Rating: %1 /10").arg(show.rating));

    QString languages("Languages: ");
    for (const auto &lang : show.languages) {
        languages.append(lang + ", ");
    }
    languages.chop(2);
    m_languagesLabel = new QLabel(languages);

    QString genres("Genres: ");
    for (const auto &genre : show.genres) {
        genres.append(genre + ", ");
    }
    genres.chop(2);
    m_genresLabel = new QLabel(genres);
    m_originalTitleLabel =
        new QLabel(QString("Original Title: %1").arg(show.originalTitle));

    m_separator = new QFrame;
    m_separator->setFrameShape(QFrame::VLine);

    QList<QLabel *> infoCol = {
        m_titleLabel,   m_yearLabel,         m_ratingLabel,  m_taglineLabel,
        m_genresLabel,  m_languagesLabel,    m_countryLabel, m_firstAiredLabel,
        m_networkLabel, m_originalTitleLabel};

    for (int i = 0; i < infoCol.size(); i++) {
        grid->addWidget(infoCol[i]);
    }

    grid->setRowStretch(infoCol.size() + 1, 1);
    grid->addWidget(m_separator, 0, 1, infoCol.size(), 1);
    grid->addWidget(m_overviewLabel, 0, 2, infoCol.size(), 1);

    setLayout(grid);
}
