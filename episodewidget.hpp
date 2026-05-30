#pragma once
#include <QFrame>
#include "traktclient.hpp"

class EpisodeWidget : public QFrame {
public:
    EpisodeWidget(StandardEpisode episode, QWidget *parent = nullptr);

private:
    StandardEpisode m_episode;
};
