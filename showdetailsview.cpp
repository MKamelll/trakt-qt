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

    auto *toolBox = new QToolBox;
    for (const auto &season : seasons) {
        auto *seasonWidget = new QWidget;
        auto *seasonLayout = new QVBoxLayout(seasonWidget);

        for (const auto &episode : season.episodes) {
            seasonLayout->addWidget(new QLabel(QString("Episode %1: %2")
                                                   .arg(episode.number)
                                                   .arg(episode.title)));
        }

        toolBox->addItem(seasonWidget, QString("Season %1").arg(season.number));
    }

    tabs->addTab(m_infoWidget, "Info");
    tabs->addTab(toolBox, "Seasons");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabs);
}
