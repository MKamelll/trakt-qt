#pragma once
#include <QWidget>
#include "traktclient.hpp"
#include <QGroupBox>
#include <QFrame>
#include <QScrollArea>

class ShowDetailsView : public QWidget {
    Q_OBJECT
public:
    ShowDetailsView(ShowDetails show, QWidget *parent = nullptr);

private:
    QGroupBox *createInfoGroup(QString title, QString labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, double labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, QDateTime labelTxt,
                               bool wrap = false);
    QGroupBox *createInfoGroup(QString title, QList<QString> labelTxt,
                               bool wrap = false);

    QWidget *createInfoWidget();

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
    QFrame *m_separator;
    ShowDetails m_show;
};
