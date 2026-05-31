#include "episodewidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

EpisodeWidget::EpisodeWidget(EpisodeDetails episode, QWidget *parent)
    : QFrame(parent), m_episode(episode) {

    auto *layout = new QHBoxLayout(this);
    setObjectName("episode-frame");

    auto *left_layout = new QVBoxLayout;
    auto *label =
        new QLabel(QString("%1: %2").arg(episode.number).arg(episode.title));
    left_layout->addWidget(label);

    layout->addLayout(left_layout);
}
