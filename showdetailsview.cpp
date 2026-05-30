#include "showdetailsview.hpp"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QPushButton>
#include <QRadioButton>
#include <QTabWidget>
#include <QToolBox>

ShowDetailsView::ShowDetailsView(ShowDetails show, QList<SeasonDetails> seasons,
                                 QWidget *parent)
    : QWidget(parent), m_show(show), m_seasons(seasons) {

    setWindowTitle(show.title);
    resize(640, 420);

    auto *tabs = new QTabWidget;
    m_infoWidget = new InfoWidget(m_show, m_seasons);
    m_seasonsWidget = new SeasonsWidget(m_seasons);

    tabs->addTab(m_infoWidget, "Info");
    tabs->addTab(m_seasonsWidget, "Seasons");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabs);
}
