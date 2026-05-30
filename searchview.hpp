#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "traktclient.hpp"
#include "loadingdialog.hpp"

class SearchView : public QWidget {
public:
    SearchView(QWidget *parent = nullptr);

private slots:
    void search();
    void onSearchDone(QList<StandardShow> results);
    void onShowDetails(ShowDetails show);
    void onShowSeasons(QList<SeasonDetails> seasons);

private:
    QLineEdit *m_searchBar;
    QPushButton *m_searchBtn;
    QListWidget *m_listWidget;
    LoadingDialog *m_loadingDialog;
    ShowDetails m_show;
    QList<SeasonDetails> m_seasons;
};
