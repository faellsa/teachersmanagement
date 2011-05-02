#include "addteacherinfodialog.h"
#include "ui_addteacherinfodialog.h"
#include "datacenter.h"
#include <QMessageBox>

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

	connect(ui->m_Ok,SIGNAL(clicked()),this,SLOT(saveInfo()));
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
	TeacherInfo teacherInfo;
	teacherInfo.name = ui->m_Name->text();
	teacherInfo.sex = ui->m_Sex->currentText();
	teacherInfo.nationality = ui->m_Nationality->text();
	teacherInfo.origin = ui->m_Origin->text();
	teacherInfo.id = ui->m_ID->text();
	teacherInfo.birthday = ui->m_Birthday->date().toString("yyyy/M");
	teacherInfo.politicsStatus = ui->m_PoliticsStatus->currentText();
	teacherInfo.partyTime = ui->m_PartyTime->date().toString("yyyy/M");
	teacherInfo.department = ui->m_Department->currentText();
	teacherInfo.category = ui->m_Category->currentText();
	teacherInfo.personnelNo = ui->m_PersonnelNo->text();
	teacherInfo.titleAndRank = ui->m_TitleAndRank->text();
	teacherInfo.titleTime = ui->m_TitleTime->date().toString("yyyy/M");
	teacherInfo.currentPositionTime = ui->m_CurrentPositionTime->date().toString("yyyy/M");
	teacherInfo.academicParttime = ui->m_AcademicPartTime->text();
	teacherInfo.personnelPlan = ui->m_PersonnelPlan->text();
	teacherInfo.administrationParttime = ui->m_AdministrationParttime->text();
	teacherInfo.otherParttime = ui->m_OtherParttime->text();
	teacherInfo.graduateTrain = ui->m_GraduateTrain->currentText();
	teacherInfo.teacherTime = ui->m_TeacherTime->date().toString("yyyy/M");
	teacherInfo.bachelorTime = ui->m_BachelorTime->date().toString("yyyy/M");
	teacherInfo.masterTime = ui->m_MasterTime->date().toString("yyyy/M");
	teacherInfo.doctorTime = ui->m_DoctorTime->date().toString("yyyy/M");
	teacherInfo.firstWorkTime = ui->m_FirstWorkTime->date().toString("yyyy/M");
	teacherInfo.firstWorkPlace = ui->m_FirstWorkPlace->text();
	teacherInfo.whuTime = ui->m_WhuTime->date().toString("yyyy/M");
	teacherInfo.beAbroadExperience = ui->m_BeAbroadExperience->toPlainText();
	teacherInfo.retirementTime = ui->m_RetirementTime->date().toString("yyyy/M");
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

void AddTeacherInfoDialog::setTeachersInfo(TeacherInfo &teacherInfo)
{
	ui->m_Name->setText(teacherInfo.name);
	teacherInfo.sex == "男" ?
			ui->m_Sex->setCurrentIndex(0):ui->m_Sex->setCurrentIndex(1);
	ui->m_Nationality->setText(teacherInfo.nationality);
	ui->m_Origin->setText(teacherInfo.origin);
	ui->m_ID->setText(teacherInfo.id);
	ui->m_Birthday->setDate(QDate::fromString(teacherInfo.birthday,QString("yyyy/M")));


	//teacherInfo.politicsStatus = ui->m_PoliticsStatus->currentText();


	ui->m_PartyTime->setDate(QDate::fromString(teacherInfo.partyTime,QString("yyyy/M")));


	//teacherInfo.department = ui->m_Department->currentText();


	//teacherInfo.category = ui->m_Category->currentText();


	ui->m_PersonnelNo->setText(teacherInfo.personnelNo);
	ui->m_TitleAndRank->setText(teacherInfo.titleAndRank);
	ui->m_TitleTime->setDate(QDate::fromString(teacherInfo.titleTime,QString("yyyy/M")));
	ui->m_CurrentPositionTime->setDate(QDate::fromString(teacherInfo.currentPositionTime,QString("yyyy/M")));
	ui->m_AcademicPartTime->setText(teacherInfo.academicParttime);
	ui->m_PersonnelPlan->setText(teacherInfo.personnelPlan);
	ui->m_AdministrationParttime->setText(teacherInfo.administrationParttime);
	ui->m_OtherParttime->setText(teacherInfo.otherParttime);

	//teacherInfo.graduateTrain = ui->m_GraduateTrain->currentText();

	ui->m_TeacherTime->setDate(QDate::fromString(teacherInfo.teacherTime,QString("yyyy/M")));
	ui->m_BachelorTime->setDate(QDate::fromString(teacherInfo.bachelorTime,QString("yyyy/M")));
	ui->m_MasterTime->setDate(QDate::fromString(teacherInfo.masterTime,QString("yyyy/M")));
	ui->m_DoctorTime->setDate(QDate::fromString(teacherInfo.doctorTime,QString("yyyy/M")));
	ui->m_FirstWorkTime->setDate(QDate::fromString(teacherInfo.firstWorkTime,QString("yyyy/M")));
	ui->m_FirstWorkPlace->setText(teacherInfo.firstWorkPlace);
	ui->m_WhuTime->setDate(QDate::fromString(teacherInfo.whuTime,QString("yyyy/M")));
	ui->m_BeAbroadExperience->setText(teacherInfo.beAbroadExperience);
	ui->m_RetirementTime->setDate(QDate::fromString(teacherInfo.retirementTime,QString("yyyy/M")));
	ui->m_Email->setText(teacherInfo.email);
	ui->m_OfficePhone->setText(teacherInfo.officePhone);
	ui->m_MobilePhone->setText(teacherInfo.mobilePhone);
}
