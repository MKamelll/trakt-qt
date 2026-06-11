#include "seasonswidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "episodewidget.hpp"
#include <QScrollArea>
#include <QToolBox>
#include "collapsablewidget.hpp"
#include <QListWidget>
#include <QSplitter>
#include "episodeswidget.hpp"

SeasonsWidget::SeasonsWidget(QList<SeasonDetails> seasons, QWidget *parent)
    : QWidget(parent), m_seasons(seasons) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *list_widget = new QListWidget;
    auto *splitter = new QSplitter(Qt::Horizontal);

    int i = 0;
    for (const auto &season : seasons) {
        auto *list_item = new QListWidgetItem;
        list_item->setText(season.title);
        list_item->setData(Qt::UserRole, i++);
        list_widget->addItem(list_item);
        m_episodesWidgetList.append(new EpisodesWidget(season.episodes, this));
    }

    auto *left_scroll = new QScrollArea;
    left_scroll->setWidget(list_widget);
    left_scroll->setWidgetResizable(true);
    left_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    splitter->addWidget(left_scroll);

    auto *right_scroll = new QScrollArea;
    right_scroll->setWidgetResizable(true);
    right_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    splitter->addWidget(right_scroll);

    connect(list_widget, &QListWidget::currentItemChanged, this,
            [=](QListWidgetItem *current, QListWidgetItem *) {
                if (current) {
                    auto i = current->data(Qt::UserRole).toInt();
                    right_scroll->setWidget(m_episodesWidgetList[i]);
                }
            });

    if (!seasons.isEmpty())
        list_widget->setCurrentRow(0);

    layout->addWidget(splitter);
}
