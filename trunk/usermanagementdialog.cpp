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
		QMessageBox::critical(this,tr("����"),tr("�û���������������������룡"));
		clearEdit();
		return;
	}
	if(ui->m_NewPassword->text() != ui->m_NewPasswordAgain->text())
	{
		QMessageBox::critical(this,tr("����"),tr("������������벻һ�£�"));
		clearEdit();
		return;
	}
	if(m_accountManage->setPassword(ui->m_NewPassword->text()))
	{
		QMessageBox::information(this,tr("�ɹ�"),tr("�޸ĳɹ���"));
	}
	else
	{
		QMessageBox::critical(this,tr("����"),tr("�޸�ʧ�ܣ�"));
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
