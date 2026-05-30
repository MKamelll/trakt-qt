#include "seasonswidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "episodewidget.hpp"
#include <QScrollArea>
#include <QToolBox>
#include "collapsablewidget.hpp"

SeasonsWidget::SeasonsWidget(QList<SeasonDetails> seasons, QWidget *parent)
    : QWidget(parent), m_seasons(seasons) {

    auto *layout = new QVBoxLayout(this);

    auto *container_widget = new QWidget;
    auto *container_layout = new QVBoxLayout(container_widget);
    container_layout->setContentsMargins(0, 0, 0, 0);

    for (const auto &season : seasons) {
        auto *contentWidget = new QWidget;
        auto *contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setContentsMargins(0, 0, 0, 0);

        for (const auto &episode : season.episodes) {
            contentLayout->addWidget(new EpisodeWidget(episode));
        }

        auto *section =
            new CollapsableWidget(QString(season.title), contentWidget);

        container_layout->addWidget(section);
    }

    container_layout->addStretch();

    auto *scrollarea = new QScrollArea;
    scrollarea->setWidget(container_widget);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(scrollarea);
}
