#pragma once
#include <QFrame>
#include "traktclient.hpp"

class EpisodeWidget : public QFrame {
public:
    EpisodeWidget(EpisodeDetails episode, QWidget *parent = nullptr);

private:
    EpisodeDetails m_episode;
};
