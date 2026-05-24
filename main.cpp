#include <QApplication>
#include <QSettings>
#include "mainwindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("trakt-qt");
    QCoreApplication::setApplicationName("trakt-qt");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    MainWindow w;

    w.show();
    return app.exec();
}
