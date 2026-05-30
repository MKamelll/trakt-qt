#include "loadingdialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

LoadingDialog::LoadingDialog(QWidget *parent) : QProgressDialog(parent) {
    setRange(0, 0);
    setCancelButton(nullptr);
    setLabelText("loading...");
    cancel();
}
