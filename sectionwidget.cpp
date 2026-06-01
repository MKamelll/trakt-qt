#include "sectionwidget.hpp"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

SectionWidget::SectionWidget(QString title, QString content, bool wrap,
                             QWidget *parent)
    : QWidget(parent) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(content);
    label->setWordWrap(wrap);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    vbox->addWidget(label);

    layout->addWidget(gp);
}

SectionWidget::SectionWidget(QString title, int content, bool wrap,
                             QWidget *parent)
    : QWidget(parent) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(QString::number(content));
    label->setWordWrap(wrap);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    vbox->addWidget(label);

    layout->addWidget(gp);
}

SectionWidget::SectionWidget(QString title, double content, bool wrap,
                             QWidget *parent)
    : QWidget(parent) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(QString::number(content));
    label->setWordWrap(wrap);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    vbox->addWidget(label);

    layout->addWidget(gp);
}

SectionWidget::SectionWidget(QString title, QDateTime content, bool wrap,
                             QWidget *parent)
    : QWidget(parent) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel("N/A");
    label->setWordWrap(wrap);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    if (content.isValid()) {
        label->setText(content.toString());
    }
    vbox->addWidget(label);

    layout->addWidget(gp);
}
