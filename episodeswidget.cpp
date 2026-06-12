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
        auto *markWatchedBtn = new QToolButton;
        markWatchedBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        markWatchedBtn->setChecked(false);
        markWatchedBtn->setCheckable(true);
        markWatchedBtn->setMinimumSize(20, 20);
        markWatchedBtn->setIconSize(QSize(20, 20));
        markWatchedBtn->setSizePolicy(QSizePolicy::Expanding,
                                      QSizePolicy::Fixed);
        markWatchedBtn->setIcon(
            Awesome::instance()->icon(fa::fa_regular, fa::fa_circle_check));

        auto *episode_section = new CollapsableWidget(
            episode.title, markWatchedBtn, new EpisodeWidget(episode));
        layout->addWidget(episode_section);
    }
}
