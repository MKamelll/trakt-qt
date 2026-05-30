#include "loadingdialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

LoadingDialog::LoadingDialog(QWidget *parent) : QDialog(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setAlignment(Qt::AlignCenter);
    auto *loadingLabel = new QLabel("loading...");
    loadingLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(loadingLabel);
    auto *progressBar = new QProgressBar;
    progressBar->setRange(0, 0);
    layout->addWidget(progressBar);
}
