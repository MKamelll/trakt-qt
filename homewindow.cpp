#include "homewindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

HomeWindow::HomeWindow(QWidget *parent) : QWidget(parent) {
    m_searchBar = new QLineEdit;
    m_searchBar->setPlaceholderText("show name...");
    auto vbox = new QVBoxLayout;
    auto searchBoxRow = new QHBoxLayout;
    auto searchBtn = new QPushButton("Search");
    searchBoxRow->addWidget(m_searchBar, 90);
    searchBoxRow->addWidget(searchBtn, 10);

    vbox->addLayout(searchBoxRow);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
}
