#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QProgressBar>
#include "traktclient.hpp"

class SearchView : public QWidget {
public:
    SearchView(QWidget *parent = nullptr);

private slots:
    void onSearchDone(QList<StandardShow> results);
    void onShowDetails(ShowDetails result);

private:
    QLineEdit *m_searchBar;
    QPushButton *m_searchBtn;
    QListWidget *m_listWidget;
    QProgressBar *m_progressBar;
};
