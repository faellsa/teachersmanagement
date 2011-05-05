#include "usermanagementdialog.h"
#include "ui_usermanagementdialog.h"
#include <QMessageBox>
#include "accountmanage.h"

UserManagementDialog::UserManagementDialog(QDialog *parent) :
	ChildDialogBase(parent),
    ui(new Ui::UserManagementDialog)
{
    ui->setupUi(this);

	m_DataCenter = DataCenter::instance();
	m_accountManage = m_DataCenter->accountManageInstance();

	setupSignals();
}

UserManagementDialog::~UserManagementDialog()
{
    delete ui;
}

void UserManagementDialog::setupSignals()
{
	connect(ui->m_ModifyPassword,SIGNAL(clicked()),this,SLOT(onOkForModify()));
	connect(ui->m_Cancel,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void UserManagementDialog::onOkForModify()
{
	if(!m_accountManage->authentication(ui->m_UserName->text(),ui->m_CurrentPassword->text()))
	{
		QMessageBox::critical(this,tr("错误"),tr("用户名或密码错误，请重新输入！"));
		clearEdit();
		return;
	}
	if(ui->m_NewPassword->text() != ui->m_NewPasswordAgain->text())
	{
		QMessageBox::critical(this,tr("错误"),tr("两次输入的密码不一致！"));
		clearEdit();
		return;
	}
	if(m_accountManage->setPassword(ui->m_NewPassword->text()))
	{
		QMessageBox::information(this,tr("成功"),tr("修改成功！"));
	}
	else
	{
		QMessageBox::critical(this,tr("错误"),tr("修改失败！"));
	}

	clearEdit();

	return;
}

void UserManagementDialog::onCancel()
{
	clearEdit();
}

void UserManagementDialog::clearEdit()
{
	ui->m_UserName->setText("");
	ui->m_CurrentPassword->setText("");
	ui->m_NewPassword->setText("");
	ui->m_NewPasswordAgain->setText("");
}
