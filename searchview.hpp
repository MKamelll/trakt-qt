#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QProgressBar>

class SearchView : public QWidget {
public:
    SearchView(QWidget *parent = nullptr);

private:
    QLineEdit *m_searchBar;
    QPushButton *m_searchBtn;
    QListWidget *m_listWidget;
    QProgressBar *m_progressBar;
};
