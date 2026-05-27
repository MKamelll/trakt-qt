#include "showdetailsview.hpp"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QPushButton>
#include <QRadioButton>
#include <QTabWidget>

ShowDetailsView::ShowDetailsView(ShowDetails show, QWidget *parent)
    : QWidget(parent), m_show(show) {

    setWindowTitle(show.title);
    resize(640, 420);

    auto *tabs = new QTabWidget;
    auto *infoWidget = createInfoWidget();

    auto *seasonsWidget = new QWidget;
    auto *seasonsLayout = new QVBoxLayout(seasonsWidget);
    seasonsLayout->setContentsMargins(0, 0, 0, 0);

    tabs->addTab(infoWidget, "Info");
    tabs->addTab(seasonsWidget, "Seasons");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabs);
}

QWidget *ShowDetailsView::createInfoWidget() {
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
    controlsWidget->setObjectName("ShowDetailsView-controls-panel");

    auto *widget = new QWidget;
    auto *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(scrollAreaWidget);
    layout->addWidget(controlsWidget);

    return widget;
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
