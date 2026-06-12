#include "episodewidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "sectionwidget.hpp"
#include "awesome.hpp"
#include <QToolButton>
#include "collapsablewidget.hpp"
#include <QGridLayout>

EpisodeWidget::EpisodeWidget(EpisodeDetails episode, QWidget *parent)
    : QWidget(parent), m_episode(episode) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setObjectName("episode-frame");

    auto *content_widget = new QWidget;
    auto *content_layout = new QGridLayout(content_widget);

    auto *overview = new SectionWidget("Overview", episode.overview, true);
    auto *runtime = new SectionWidget("Runtime", episode.runtime);
    auto *rating = new SectionWidget("Rating/10", episode.rating);
    auto *firstAired = new SectionWidget("First Aired", episode.firstAired);

    content_layout->addWidget(overview, 0, 0, 4, 1);
    content_layout->addWidget(runtime, 0, 1);
    content_layout->addWidget(rating, 1, 1);
    content_layout->addWidget(firstAired, 2, 1);

    auto *markWatchedBtn = new QToolButton;
    markWatchedBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    markWatchedBtn->setChecked(false);
    markWatchedBtn->setCheckable(true);
    markWatchedBtn->setMinimumSize(20, 20);
    markWatchedBtn->setIconSize(QSize(20, 20));
    markWatchedBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    markWatchedBtn->setIcon(
        Awesome::instance()->icon(fa::fa_regular, fa::fa_circle_check));

    layout->addWidget(
        new CollapsableWidget(episode.title, markWatchedBtn, content_widget));
}
