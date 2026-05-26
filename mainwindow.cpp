#include "mainwindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include "loginview.hpp"
#include <QTabWidget>
#include "traktclient.hpp"
#include "homeview.hpp"
#include "searchview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("trakt");
    resize(640, 420);

    auto *loginView = new LoginView;
    auto *homeView = new HomeView;
    auto *searchView = new SearchView;

    auto *tabs = new QTabWidget;
    tabs->addTab(homeView, "Home");
    tabs->addTab(searchView, "Search");

    if (TraktClient::instance()->isAuthenticated()) {
        setCentralWidget(tabs);
    } else {
        setCentralWidget(loginView);
    }
}

MainWindow::~MainWindow() {}
