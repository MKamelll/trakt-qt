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
    layout->setContentsMargins(0, 0, 0, 0);

    auto *container_widget = new QWidget;
    auto *container_layout = new QVBoxLayout(container_widget);

    for (const auto &season : seasons) {
        auto *contentWidget = new QWidget;
        auto *contentLayout = new QVBoxLayout(contentWidget);

        for (const auto &episode : season.episodes) {
            auto *episodeSection = new CollapsableWidget(
                episode.title, new EpisodeWidget(episode));
            contentLayout->addWidget(episodeSection);
        }

        auto *section = new CollapsableWidget(season.title, contentWidget);

        container_layout->addWidget(section);
    }

    container_layout->addStretch();

    auto *scrollarea = new QScrollArea;
    scrollarea->setWidget(container_widget);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(scrollarea);
}
