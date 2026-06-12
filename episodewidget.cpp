#include "episodewidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "sectionwidget.hpp"
#include "awesome.hpp"
#include <QToolButton>
#include "collapsablewidget.hpp"

EpisodeWidget::EpisodeWidget(EpisodeDetails episode, QWidget *parent)
    : QWidget(parent), m_episode(episode) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setObjectName("episode-frame");

    auto *content_widget = new QWidget;
    auto *content_layout = new QHBoxLayout(content_widget);
    content_layout->setContentsMargins(0, 0, 0, 0);

    auto *left_widget = new QWidget;
    auto *left_layout = new QVBoxLayout(left_widget);
    auto *overview = new SectionWidget("Overview", episode.overview, true);
    left_layout->addWidget(overview);

    auto *right_widget = new QWidget;
    auto *right_layout = new QVBoxLayout(right_widget);
    auto *runtime = new SectionWidget("Runtime", episode.runtime);
    right_layout->addWidget(runtime);

    auto *rating = new SectionWidget("Rating/10", episode.rating);
    right_layout->addWidget(rating);

    auto *firstAired = new SectionWidget("First Aired", episode.firstAired);
    right_layout->addWidget(firstAired);

    content_layout->addWidget(left_widget);
    content_layout->addWidget(right_widget);

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
