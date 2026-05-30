#pragma once
#include <QProgressDialog>

class LoadingDialog : public QProgressDialog {
    Q_OBJECT
public:
    LoadingDialog(QWidget *parent = nullptr);
};
