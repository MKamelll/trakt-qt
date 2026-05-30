#include "infowidget.hpp"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

InfoWidget::InfoWidget(ShowDetails show, QList<SeasonDetails> seasons,
                       QWidget *parent)
    : QWidget(parent), m_show(show), m_seasons(seasons) {

    m_titleGroup = createInfoGroup("Title", m_show.title);
    m_yearGroup = createInfoGroup("Year", m_show.year);
    m_overviewGroup = createInfoGroup("Overview", m_show.overview, true);
    m_taglineGroup = createInfoGroup("TagLine", m_show.tagLine);
    m_firstAiredGroup = createInfoGroup("First Aired", m_show.firstAired);
    m_runtimeGroup = createInfoGroup("Runtime (minutes)", m_show.runtime);
    m_networkGroup = createInfoGroup("Network", m_show.network);
    m_countryGroup = createInfoGroup("Country", m_show.country);
    m_ratingGroup = createInfoGroup("Rating/10", m_show.rating);
    m_languagesGroup = createInfoGroup("Languages", m_show.languages);
    m_genresGroup = createInfoGroup("Genres", m_show.genres);
    m_originalTitleGroup =
        createInfoGroup("Original Title", m_show.originalTitle);

    QList<QGroupBox *> infoGroups = {
        m_titleGroup,     m_yearGroup,       m_taglineGroup,
        m_overviewGroup,  m_firstAiredGroup, m_runtimeGroup,
        m_networkGroup,   m_countryGroup,    m_ratingGroup,
        m_languagesGroup, m_genresGroup,     m_originalTitleGroup};

    auto *scrollWidget = new QWidget;
    auto *scrollLayout = new QVBoxLayout(scrollWidget);
    auto *scrollAreaWidget = new QScrollArea;
    scrollAreaWidget->setWidget(scrollWidget);
    scrollAreaWidget->setWidgetResizable(true);
    scrollAreaWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (const auto &gp : infoGroups) {
        scrollLayout->addWidget(gp);
    }

    auto *controlsWidget = new QWidget;
    auto *controlsLayout = new QHBoxLayout(controlsWidget);
    auto *watchListBtn = new QRadioButton("Watchlist");
    auto *watchedBtn = new QRadioButton("Watched");
    auto *applyBtn = new QPushButton("Apply");
    controlsLayout->addWidget(watchListBtn);
    controlsLayout->addWidget(watchedBtn);
    controlsLayout->addStretch();
    controlsLayout->addWidget(applyBtn);
    controlsWidget->setObjectName("InfoWidget-controls-panel");

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(scrollAreaWidget);
    layout->addWidget(controlsWidget);
}

QGroupBox *InfoWidget::createInfoGroup(QString title, QString labelTxt,
                                       bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(labelTxt);
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *InfoWidget::createInfoGroup(QString title, double labelTxt,
                                       bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(QString::number(labelTxt));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *InfoWidget::createInfoGroup(QString title, QDateTime labelTxt,
                                       bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label =
        new QLabel(labelTxt.toString("dddd, MMMM d, yyyy - hh:mm AP t"));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *InfoWidget::createInfoGroup(QString title, QList<QString> labelTxt,
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
