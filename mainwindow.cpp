#include "mainwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include "loginwindow.hpp"
#include <QStackedWidget>
#include "traktclient.hpp"
#include "homewindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("trakt");
    resize(640, 420);

    auto loginwindow = new LoginWindow;
    auto homeWindow = new HomeWindow;

    auto stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(loginwindow);
    stackedWidget->addWidget(homeWindow);

    if (TraktClient::instance()->isAuthenticated()) {
        stackedWidget->setCurrentWidget(homeWindow);
    } else {
        stackedWidget->setCurrentWidget(loginwindow);
    }

    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow() {}
