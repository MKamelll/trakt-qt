#include "collapsablewidget.hpp"
#include <QVBoxLayout>

CollapsableWidget::CollapsableWidget(QString btnText, QWidget *content,
                                     QWidget *parent)
    : QWidget(parent), m_contentWidget(content), m_btnText(btnText) {

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *m_toggleBtn = new QToolButton;
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
