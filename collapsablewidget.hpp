#pragma once

#include <QWidget>
#include <QToolButton>

class CollapsableWidget : public QWidget {
    Q_OBJECT
public:
    CollapsableWidget(QString btnText, QWidget *content,
                      QWidget *parent = nullptr);

private:
    QWidget *m_contentWidget;
    QToolButton *m_toggleBtn;
    QString m_btnText;
};
