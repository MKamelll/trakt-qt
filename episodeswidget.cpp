#include "episodeswidget.hpp"
#include <QVBoxLayout>
#include "collapsablewidget.hpp"
#include "episodewidget.hpp"
#include <QScrollArea>

EpisodesWidget::EpisodesWidget(QList<EpisodeDetails> episodes, QWidget *parent)
    : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    for (const auto &episode : episodes) {
        auto *episode_section =
            new CollapsableWidget(episode.title, new EpisodeWidget(episode));
        layout->addWidget(episode_section);
    }
}
