#pragma once
#include <QWidget>
#include "traktclient.hpp"
#include <QGroupBox>
#include <QFrame>
#include <QScrollArea>
#include "infowidget.hpp"
#include "seasonswidget.hpp"

class ShowDetailsView : public QWidget {
    Q_OBJECT
public:
    ShowDetailsView(ShowDetails show, QList<SeasonDetails> seasons,
                    QWidget *parent = nullptr);

private:
    ShowDetails m_show;
    QList<SeasonDetails> m_seasons;
    InfoWidget *m_infoWidget;
    SeasonsWidget *m_seasonsWidget;
};
