#pragma once
#include <QWidget>
#include "traktclient.hpp"
#include <QLabel>
#include <QFrame>

class ShowDetailsView : public QWidget {
    Q_OBJECT
public:
    ShowDetailsView(ShowDetails show, QWidget *parent = nullptr);

private:
    QLabel *m_titleLabel;
    QLabel *m_yearLabel;
    QLabel *m_overviewLabel;
    QLabel *m_taglineLabel;
    QLabel *m_firstAiredLabel;
    QLabel *m_runtimeLabel;
    QLabel *m_networkLabel;
    QLabel *m_countryLabel;
    QLabel *m_ratingLabel;
    QLabel *m_languagesLabel;
    QLabel *m_genresLabel;
    QLabel *m_originalTitleLabel;
    QFrame *m_separator;
};
