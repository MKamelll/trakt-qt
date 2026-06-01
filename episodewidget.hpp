#pragma once
#include <QWidget>
#include "traktclient.hpp"

class EpisodeWidget : public QWidget {
public:
    EpisodeWidget(EpisodeDetails episode, QWidget *parent = nullptr);

private:
    EpisodeDetails m_episode;
};
