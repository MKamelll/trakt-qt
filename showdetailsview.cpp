#include "showdetailsview.hpp"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QPushButton>
#include <QRadioButton>

ShowDetailsView::ShowDetailsView(ShowDetails show, QWidget *parent)
    : QWidget(parent) {

    setWindowTitle(show.title);
    resize(640, 420);

    m_titleGroup = createInfoGroup("Title", show.title);
    m_yearGroup = createInfoGroup("Year", show.year);
    m_overviewGroup = createInfoGroup("Overview", show.overview, true);
    m_taglineGroup = createInfoGroup("TagLine", show.tagLine);
    m_firstAiredGroup = createInfoGroup("First Aired", show.firstAired);
    m_runtimeGroup = createInfoGroup("Runtime (minutes)", show.runtime);
    m_networkGroup = createInfoGroup("Network", show.network);
    m_countryGroup = createInfoGroup("Country", show.country);
    m_ratingGroup = createInfoGroup("Rating/10", show.rating);
    m_languagesGroup = createInfoGroup("Languages", show.languages);
    m_genresGroup = createInfoGroup("Genres", show.genres);
    m_originalTitleGroup =
        createInfoGroup("Original Title", show.originalTitle);

    QList<QGroupBox *> infoGroups = {
        m_titleGroup,     m_yearGroup,       m_taglineGroup,
        m_overviewGroup,  m_firstAiredGroup, m_runtimeGroup,
        m_networkGroup,   m_countryGroup,    m_ratingGroup,
        m_languagesGroup, m_genresGroup,     m_originalTitleGroup};

    auto *controlsPanel = createControlsPanel();
    auto *scroll = createInfoSection(infoGroups);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scroll);
    mainLayout->addWidget(controlsPanel);
}

QWidget *ShowDetailsView::createControlsPanel() {
    auto *content = new QWidget;
    auto *layout = new QHBoxLayout(content);
    layout->setContentsMargins(0, 0, 0, 0);
    auto *watchListBtn = new QRadioButton("Watchlist");
    auto *watchedBtn = new QRadioButton("Watched");
    auto *applyBtn = new QPushButton("Apply");
    layout->addWidget(watchListBtn);
    layout->addWidget(watchedBtn);
    layout->addStretch();
    layout->addWidget(applyBtn);
    return content;
}

QScrollArea *ShowDetailsView::createInfoSection(QList<QGroupBox *> infoGroups) {
    auto *content = new QWidget;
    auto *layout = new QVBoxLayout(content);
    layout->setContentsMargins(0, 0, 0, 0);
    auto *scroll = new QScrollArea;
    scroll->setWidget(content);
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (const auto &gp : infoGroups) {
        layout->addWidget(gp);
    }

    return scroll;
}

QGroupBox *ShowDetailsView::createInfoGroup(QString title, QString labelTxt,
                                            bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(labelTxt);
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createInfoGroup(QString title, double labelTxt,
                                            bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(QString::number(labelTxt));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createInfoGroup(QString title, QDateTime labelTxt,
                                            bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label =
        new QLabel(labelTxt.toString("dddd, MMMM d, yyyy - hh:mm AP t"));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createInfoGroup(QString title,
                                            QList<QString> labelTxt,
                                            bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    QString st("");
    for (const auto &lang : labelTxt) {
        st.append(lang + ", ");
    }
    st.chop(2);
    auto *label = new QLabel(st);
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}
