#include "mainwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include "traktclient.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("trakt");
    resize(640, 420);

    TraktClient::instance()->search("breaking bad");

    connect(TraktClient::instance(), &TraktClient::searchDone, this,
            [=](QList<StandardShow> arr) { qDebug() << arr << "\n"; });

    auto centralWidget = new QWidget;
    auto vbox = new QVBoxLayout(centralWidget);

    auto loginBtn = new QPushButton("Login", this);

    vbox->addWidget(loginBtn, 25, Qt::AlignCenter);

    connect(loginBtn, &QPushButton::clicked, this,
            [=]() { TraktClient::instance()->authenticate(); });

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}
