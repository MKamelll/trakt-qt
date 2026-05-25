#include <QApplication>
#include <QSettings>
#include <QFile>
#include "mainwindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("trakt-qt");
    QCoreApplication::setApplicationName("trakt-qt");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QFile file(":/styles.css");
    if (file.open(QFile::ReadOnly))
        qApp->setStyleSheet(file.readAll());

    MainWindow w;

    w.show();
    return app.exec();
}
