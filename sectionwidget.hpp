#pragma once
#include <QWidget>
#include <QDateTime>

class SectionWidget : public QWidget {
    Q_OBJECT
public:
    SectionWidget(QString title, QString content, bool wrap = false,
                  QWidget *parent = nullptr);
    SectionWidget(QString title, int content, bool wrap = false,
                  QWidget *parent = nullptr);
    SectionWidget(QString title, double content, bool wrap = false,
                  QWidget *parent = nullptr);
    SectionWidget(QString title, QDateTime content, bool wrap = false,
                  QWidget *parent = nullptr);
};
