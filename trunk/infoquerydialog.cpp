#include "infoquerydialog.h"
#include "ui_infoquerydialog.h"
#include <QComboBox>
#include <QDebug>

InfoQueryDialog::InfoQueryDialog(QDialog *parent) :
		ChildDialogBase(parent),
		ui(new Ui::InfoQueryDialog)
{
    ui->setupUi(this);
	setupWidgets();
	setupSignals();
}

InfoQueryDialog::~InfoQueryDialog()
{
    delete ui;
}

void InfoQueryDialog::setupWidgets()
{
	ui->m_ConditionComboBox1->hide();
	ui->m_ConditionComboBox2->hide();
	ui->m_ConditionComboBox3->hide();
	ui->m_ConditionComboBox4->hide();
	ui->m_ConditionComboBox5->hide();

	ui->m_ConditionEdit1->hide();
	ui->m_ConditionEdit2->hide();
	ui->m_ConditionEdit3->hide();
	ui->m_ConditionEdit4->hide();
	ui->m_ConditionEdit5->hide();

	ui->m_ConditionFrame2->hide();
	ui->m_ConditionFrame3->hide();
	ui->m_ConditionFrame4->hide();
	ui->m_ConditionFrame5->hide();
}

void InfoQueryDialog::setupSignals()
{
	connect(ui->m_ConditionType1,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType2,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType3,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType4,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType5,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
}

void InfoQueryDialog::showConditionWidget(QString conditionType)
{
//	if(conditionType == tr("����") || conditionType == tr("���֤��")
//		|| conditionType == tr("���º�") || conditionType == tr("ְ��ְ��")
//		|| conditionType == tr("������ְ") || conditionType == tr("����"))
//		{
		if(sender()->objectName() == "m_ConditionType1")
		{
			ui->m_ConditionEdit1->show();
			ui->m_ConditionComboBox1->hide();
		}
		else if(sender()->objectName() == "m_ConditionType2")
		{
			ui->m_ConditionEdit2->show();
			ui->m_ConditionComboBox2->hide();
		}
		else if(sender()->objectName() == "m_ConditionType3")
		{
			ui->m_ConditionEdit3->show();
			ui->m_ConditionComboBox3->hide();
		}
		else if(sender()->objectName() == "m_ConditionType4")
		{
			ui->m_ConditionEdit4->show();
			ui->m_ConditionComboBox4->hide();
		}
		else if(sender()->objectName() == "m_ConditionType5")
		{
			ui->m_ConditionEdit5->show();
			ui->m_ConditionComboBox5->hide();
		}
//	}
//	else
//	{
//		if(sender()->objectName() == "m_ConditionType1")
//		{
//			ui->m_ConditionEdit1->hide();
//			ui->m_ConditionComboBox1->show();
//		}
//		else if(sender()->objectName() == "m_ConditionType2")
//		{
//			ui->m_ConditionEdit2->hide();
//			ui->m_ConditionComboBox2->show();
//		}
//		else if(sender()->objectName() == "m_ConditionType3")
//		{
//			ui->m_ConditionEdit3->hide();
//			ui->m_ConditionComboBox3->show();
//		}
//		else if(sender()->objectName() == "m_ConditionType4")
//		{
//			ui->m_ConditionEdit4->hide();
//			ui->m_ConditionComboBox4->show();
//		}
//		else if(sender()->objectName() == "m_ConditionType5")
//		{
//			ui->m_ConditionEdit5->hide();
//			ui->m_ConditionComboBox5->show();
//		}
//	}
}
