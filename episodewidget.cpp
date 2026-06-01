#include "episodewidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "sectionwidget.hpp"

EpisodeWidget::EpisodeWidget(EpisodeDetails episode, QWidget *parent)
    : QWidget(parent), m_episode(episode) {

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setObjectName("episode-frame");

    auto *left_layout = new QVBoxLayout;
    auto *overview = new SectionWidget("Overview", episode.overview, true);
    left_layout->addWidget(overview);

    auto *right_layout = new QVBoxLayout;

    auto *runtime = new SectionWidget("Runtime", episode.runtime);
    right_layout->addWidget(runtime);

    auto *rating = new SectionWidget("Rating/10", episode.rating);
    right_layout->addWidget(rating);

    auto *firstAired = new SectionWidget("First Aired", episode.firstAired);
    right_layout->addWidget(firstAired);

    layout->addLayout(left_layout);
    layout->addLayout(right_layout);
}
