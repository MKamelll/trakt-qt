#include "episodeswidget.hpp"
#include <QVBoxLayout>
#include "collapsablewidget.hpp"
#include "episodewidget.hpp"
#include <QScrollArea>
#include <QToolButton>
#include "awesome.hpp"

EpisodesWidget::EpisodesWidget(QList<EpisodeDetails> episodes, QWidget *parent)
    : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    for (const auto &episode : episodes) {
        layout->addWidget(new EpisodeWidget(episode));
    }

    layout->addStretch(1);
}
