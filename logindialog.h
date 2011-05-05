#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include "datacenter.h"

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
	void setupSignals();
	MainWindow *m_MainWindow;
	DataCenter *m_DataCenter;
	AccountManage* m_accountManage;

private slots:
	void onLoginButton();
	void onExitButton();
};

#endif // LOGINDIALOG_H
