#include "seasonswidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "episodewidget.hpp"
#include <QScrollArea>
#include <QToolBox>

SeasonsWidget::SeasonsWidget(QList<SeasonDetails> seasons, QWidget *parent)
    : QWidget(parent), m_seasons(seasons) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *container_widget = new QWidget;
    auto *container_layout = new QVBoxLayout(container_widget);

    auto *toolbox = new QToolBox;

    for (const auto &season : seasons) {
        auto *seasonWidget = new QWidget;
        auto *seasonLayout = new QVBoxLayout(seasonWidget);

        for (const auto &episode : season.episodes) {
            seasonLayout->addWidget(new EpisodeWidget(episode));
        }

        toolbox->addItem(seasonWidget, QString("Season %1").arg(season.number));
    }

    container_layout->addWidget(toolbox);
    container_layout->addStretch();

    auto *scrollarea = new QScrollArea;
    scrollarea->setWidget(container_widget);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(scrollarea);
}
