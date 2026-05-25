#include "mainwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include "loginview.hpp"
#include <QStackedWidget>
#include "traktclient.hpp"
#include "homeview.hpp"
#include "searchview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("trakt");
    resize(640, 420);

    auto *loginView = new LoginView;
    auto *homeView = new HomeView;
    auto *searchView = new SearchView;

    auto stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(loginView);
    stackedWidget->addWidget(homeView);
    stackedWidget->addWidget(searchView);

    if (TraktClient::instance()->isAuthenticated()) {
        stackedWidget->setCurrentWidget(searchView);
    } else {
        stackedWidget->setCurrentWidget(loginView);
    }

    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow() {}
