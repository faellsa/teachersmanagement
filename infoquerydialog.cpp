#include "infoquerydialog.h"
#include "ui_infoquerydialog.h"

InfoQueryDialog::InfoQueryDialog(QDialog *parent) :
	ChildDialogBase(parent),
    ui(new Ui::InfoQueryDialog)
{
    ui->setupUi(this);
	setupWidgets();
}

InfoQueryDialog::~InfoQueryDialog()
{
    delete ui;
}

void InfoQueryDialog::setupWidgets()
{
	ui->m_ConditionType2->hide();
	ui->m_ConditionType3->hide();
	ui->m_ConditionType4->hide();
	ui->m_ConditionType5->hide();

	ui->m_AddCondition2->hide();
	ui->m_AddCondition3->hide();
	ui->m_AddCondition4->hide();

	ui->m_DelCondition2->hide();
	ui->m_DelCondition3->hide();
	ui->m_DelCondition4->hide();
	ui->m_DelCondition5->hide();

	ui->m_ConditionData1->hide();
	ui->m_ConditionData2->hide();
	ui->m_ConditionData3->hide();
	ui->m_ConditionData4->hide();
	ui->m_ConditionData5->hide();

	ui->m_ConditionEdit1->hide();
	ui->m_ConditionEdit2->hide();
	ui->m_ConditionEdit3->hide();
	ui->m_ConditionEdit4->hide();
	ui->m_ConditionEdit5->hide();

}
