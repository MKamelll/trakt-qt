#include "collapsablewidget.hpp"
#include <QVBoxLayout>

CollapsableWidget::CollapsableWidget(QString btnText, QWidget *content,
                                     QWidget *parent)
    : QWidget(parent), m_contentWidget(content), m_btnText(btnText) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_toggleBtn = new QToolButton;
    m_toggleBtn->setText(m_btnText);
    m_toggleBtn->setCheckable(true);
    m_toggleBtn->setChecked(false);
    m_toggleBtn->setArrowType(Qt::RightArrow);
    m_toggleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_toggleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    content->setVisible(false);

    connect(m_toggleBtn, &QToolButton::toggled, this, [=](bool checked) {
        content->setVisible(checked);
        m_toggleBtn->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
    });

    layout->addWidget(m_toggleBtn);
    layout->addWidget(m_contentWidget);
}

CollapsableWidget::CollapsableWidget(QString btnText, QToolButton *addOnBtn,
                                     QWidget *content, QWidget *parent)
    : QWidget(parent), m_contentWidget(content), m_addOnBtn(addOnBtn),
      m_btnText(btnText) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *toggle_widget = new QWidget;
    auto *toggle_layout = new QHBoxLayout(toggle_widget);

    m_toggleBtn = new QToolButton;
    m_toggleBtn->setText(m_btnText);
    m_toggleBtn->setCheckable(true);
    m_toggleBtn->setChecked(false);
    m_toggleBtn->setArrowType(Qt::RightArrow);
    m_toggleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    content->setVisible(false);

    connect(m_toggleBtn, &QToolButton::toggled, this, [=](bool checked) {
        content->setVisible(checked);
        m_toggleBtn->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
    });

    toggle_layout->addWidget(m_toggleBtn, 1);
    toggle_layout->addWidget(m_addOnBtn, 0);

    layout->addWidget(toggle_widget);
    layout->addWidget(m_contentWidget);
}
