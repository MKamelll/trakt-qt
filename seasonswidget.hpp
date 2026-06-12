#pragma once
#include <QWidget>
#include "traktclient.hpp"
#include "episodeswidget.hpp"

class SeasonsWidget : public QWidget {
public:
    SeasonsWidget(QList<SeasonDetails> seasons, QWidget *parent = nullptr);

private:
    QList<SeasonDetails> m_seasons;
};
