#include "logindialog.h"
#include "ui_logindialog.h"
#include "QDebug"
#include "databaseexception.h"
#include "QMessageBox"
#include "accountmanage.h"

LoginDialog::LoginDialog(QWidget *parent) :
		QDialog(parent),
		ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

	setWindowTitle(tr("��ӭʹ�ý�ְ����Ϣ����ϵͳ"));

	try{
		m_DataCenter = DataCenter::instance();
		m_accountManage = m_DataCenter->accountManageInstance();
	}catch(DatabaseException& e)
	{
		QMessageBox::critical(this, tr("���ش���"), tr("�������ݿ����\n")+e.errorMsg());
		::exit(1);
	}

	ui->m_Username->setText("admin");
	ui->m_Password->setText("888888");

	setupSignals();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupSignals()
{
	connect(ui->m_Login,SIGNAL(clicked()),this,SLOT(onLoginButton()));
	connect(ui->m_Exit,SIGNAL(clicked()),this,SLOT(onExitButton()));
}

void LoginDialog::onLoginButton()
{
	if(m_accountManage->authentication(ui->m_Username->text(),ui->m_Password->text()))
	{
		m_MainWindow = new MainWindow;
		close();
		m_MainWindow->show();
	}
	else
	{
		ui->m_Username->setText("");
		ui->m_Password->setText("");
		QMessageBox::critical(this,tr("����"),tr("�û���������������������룡"));
	}
}

void LoginDialog::onExitButton()
{
	::exit(0);
}

