#pragma once
#include <QWidget>
#include "traktclient.hpp"

class EpisodesWidget : public QWidget {
    Q_OBJECT
public:
    EpisodesWidget(QList<EpisodeDetails> episodes, QWidget *parent = nullptr);
};
