#pragma once
#include <QWidget>
#include <QLineEdit>

class HomeWindow : public QWidget {
public:
    HomeWindow(QWidget *parent = nullptr);

private:
    QLineEdit *m_searchBar;
};
