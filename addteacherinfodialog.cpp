#include "addteacherinfodialog.h"
#include "ui_addteacherinfodialog.h"

AddTeacherInfoDialog::AddTeacherInfoDialog(QDialog *parent) :
	ChildDialogBase(parent),
    ui(new Ui::AddTeacherInfoDialog)
{
    ui->setupUi(this);
	setupSignals();
}

AddTeacherInfoDialog::~AddTeacherInfoDialog()
{
    delete ui;
}

void AddTeacherInfoDialog::setupSignals()
{
	connect(ui->m_Page1Next,SIGNAL(clicked()),this,SLOT(showPoliticalInfoPage()));

	connect(ui->m_Page2Pre,SIGNAL(clicked()),this,SLOT(showPersonalInfoPage()));
	connect(ui->m_Page2Next,SIGNAL(clicked()),this,SLOT(showWorkInfoPage()));

	connect(ui->m_Page3Pre,SIGNAL(clicked()),this,SLOT(showPoliticalInfoPage()));
	connect(ui->m_Page3Next,SIGNAL(clicked()),this,SLOT(showPersonalExperiencePage()));

	connect(ui->m_Page4Pre,SIGNAL(clicked()),this,SLOT(showWorkInfoPage()));
	connect(ui->m_Page4Next,SIGNAL(clicked()),this,SLOT(showRemarkPage()));

	connect(ui->m_Page5Pre,SIGNAL(clicked()),this,SLOT(showPersonalExperiencePage()));
}

void AddTeacherInfoDialog::showPersonalInfoPage()
{
	ui->tabWidget->setCurrentIndex(0);
}

void AddTeacherInfoDialog::showPoliticalInfoPage()
{
	ui->tabWidget->setCurrentIndex(1);
}

void AddTeacherInfoDialog::showWorkInfoPage()
{
	ui->tabWidget->setCurrentIndex(2);
}

void AddTeacherInfoDialog::showPersonalExperiencePage()
{
	ui->tabWidget->setCurrentIndex(3);
}

void AddTeacherInfoDialog::showRemarkPage()
{
	ui->tabWidget->setCurrentIndex(4);
}
