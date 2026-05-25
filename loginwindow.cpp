#include "loginwindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include "traktclient.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    auto vbox = new QVBoxLayout(this);

    auto loginBtn = new QPushButton("Login", this);

    vbox->addWidget(loginBtn, 25, Qt::AlignCenter);

    connect(loginBtn, &QPushButton::clicked, this,
            [=]() { TraktClient::instance()->authenticate(); });
}
