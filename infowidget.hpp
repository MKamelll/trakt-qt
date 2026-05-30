#pragma once
#include <QWidget>
#include <QGroupBox>
#include "traktclient.hpp"

class InfoWidget : public QWidget {
    Q_OBJECT
public:
    InfoWidget(ShowDetails show, QList<SeasonDetails> seasons,
               QWidget *parent = nullptr);

private:
    QGroupBox *createInfoGroup(QString title, QString labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, double labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, QDateTime labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, QList<QString> labelTxt,
                               bool wrap = false);

    QGroupBox *m_titleGroup;
    QGroupBox *m_yearGroup;
    QGroupBox *m_overviewGroup;
    QGroupBox *m_taglineGroup;
    QGroupBox *m_firstAiredGroup;
    QGroupBox *m_runtimeGroup;
    QGroupBox *m_networkGroup;
    QGroupBox *m_countryGroup;
    QGroupBox *m_ratingGroup;
    QGroupBox *m_languagesGroup;
    QGroupBox *m_genresGroup;
    QGroupBox *m_originalTitleGroup;
    ShowDetails m_show;
    QList<SeasonDetails> m_seasons;
};
