#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
	setupSignals();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupSignals()
{
	connect(ui->m_Login,SIGNAL(clicked()),this,SLOT(onLoginButton()));
	connect(ui->m_Cancle,SIGNAL(clicked()),this,SLOT(onCancleButton()));
}

void LoginDialog::onLoginButton()
{
	m_MainWindow = new MainWindow;
	close();
	m_MainWindow->show();

}

void LoginDialog::onCancleButton()
{

}
