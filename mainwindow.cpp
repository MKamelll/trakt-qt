#include "mainwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include "traktclient.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("trakt");
    resize(640, 420);

    auto traktClient = new TraktClient(this);

    auto *centralWidget = new QWidget;
    auto *vbox = new QVBoxLayout(centralWidget);

    auto *loginBtn = new QPushButton("Login", this);

    vbox->addWidget(loginBtn, 25, Qt::AlignCenter);

    connect(loginBtn, &QPushButton::clicked, this,
            [=]() { traktClient->authenticate(); });

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}
