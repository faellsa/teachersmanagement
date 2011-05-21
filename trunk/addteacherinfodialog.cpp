#include "addteacherinfodialog.h"
#include "ui_addteacherinfodialog.h"
#include "datacenter.h"
#include <QMessageBox>

AddTeacherInfoDialog::AddTeacherInfoDialog(QDialog *parent) :
		ChildDialogBase(parent),
		ui(new Ui::AddTeacherInfoDialog)
{
    ui->setupUi(this);
	ui->m_RankTime->hide();
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

	connect(ui->m_Ok,SIGNAL(clicked()),this,SLOT(saveInfo()));

	connect(ui->m_PoliticsStatus,SIGNAL(currentIndexChanged(QString)),this,SLOT(onPoliticsStatus(QString)));
	connect(ui->m_GraduateTrain,SIGNAL(currentIndexChanged(QString)),this,SLOT(onGraduateTrain(QString)));
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

void AddTeacherInfoDialog::saveInfo()
{
	if(ui->m_Name->text().isEmpty() || ui->m_PersonnelNo->text().isEmpty())
	{
		QMessageBox::warning(this,tr("提示"),tr("姓名和人事号不能为空"));
		return;
	}
	TeacherInfo teacherInfo;
	teacherInfo.name = ui->m_Name->text();
	teacherInfo.sex = ui->m_Sex->currentText();
	teacherInfo.nationality = ui->m_Nationality->text();
	teacherInfo.origin = ui->m_Origin->text();
	teacherInfo.id = ui->m_ID->text();
	teacherInfo.birthday = ui->m_Birthday->date().toString("yyyy-M-d");
	teacherInfo.politicsStatus = ui->m_PoliticsStatus->currentText();

	if(teacherInfo.politicsStatus != tr("群众"))
		teacherInfo.partyTime = ui->m_PartyTime->date().toString("yyyy-M-d");
	else
		teacherInfo.partyTime = tr("无");

	teacherInfo.department = ui->m_Department->currentText();
	teacherInfo.category = ui->m_Category->currentText();
	teacherInfo.personnelNo = ui->m_PersonnelNo->text();
	teacherInfo.title = ui->m_Title->text();
	teacherInfo.titleTime = ui->m_TitleTime->date().toString("yyyy-M-d");
	teacherInfo.rank = ui->m_Rank->text();
	//teacherInfo.rankTime = ui->m_RankTime->date().toString("yyyy-M-d");
	teacherInfo.currentPositionTime = ui->m_CurrentPositionTime->date().toString("yyyy-M-d");
	teacherInfo.academicParttime = ui->m_AcademicPartTime->text();
	teacherInfo.personnelPlan = ui->m_PersonnelPlan->text();
	teacherInfo.honour = ui->m_Honour->text();
	teacherInfo.administrationParttime = ui->m_AdministrationParttime->text();
	teacherInfo.otherParttime = ui->m_OtherParttime->text();
	teacherInfo.graduateTrain = ui->m_GraduateTrain->currentText();

	if(teacherInfo.graduateTrain != tr("无"))
		teacherInfo.teacherTime = ui->m_TeacherTime->date().toString("yyyy-M-d");
	else
		teacherInfo.teacherTime = tr("无");

	teacherInfo.bachelorTime = ui->m_BachelorTime->date().toString("yyyy-M-d");
	teacherInfo.masterTime = ui->m_MasterTime->date().toString("yyyy-M-d");
	teacherInfo.doctorTime = ui->m_DoctorTime->date().toString("yyyy-M-d");
	teacherInfo.firstWorkTime = ui->m_FirstWorkTime->date().toString("yyyy-M-d");
	teacherInfo.firstWorkPlace = ui->m_FirstWorkPlace->text();
	teacherInfo.whuTime = ui->m_WhuTime->date().toString("yyyy-M-d");
	teacherInfo.beAbroadExperience = ui->m_BeAbroadExperience->toPlainText();
	teacherInfo.retirementTime = ui->m_RetirementTime->date().toString("yyyy-M-d");
	teacherInfo.email = ui->m_Email->text();
	teacherInfo.officePhone = ui->m_OfficePhone->text();
	teacherInfo.mobilePhone = ui->m_MobilePhone->text();

	DataCenter *dataCenter = DataCenter::instance();

	if(dataCenter->techersInfoTableInstance()->newTeacherInfo(teacherInfo))
	{
		QMessageBox::information(this,tr("成功"),tr("保存成功"));
	}
	else
	{
		QMessageBox::information(this,tr("失败"),tr("保存失败"));
	}
}

void AddTeacherInfoDialog::onPoliticsStatus(QString politicsStatus)
{
	if(politicsStatus == tr("群众"))
		ui->m_PartyTime->setVisible(false);
	else
		ui->m_PartyTime->setVisible(true);
}

void AddTeacherInfoDialog::onGraduateTrain(QString graduateTrain)
{
	if(graduateTrain == tr("无"))
		ui->m_TeacherTime->setVisible(false);
	else
		ui->m_TeacherTime->setVisible(true);
}
