#include "infoquerydialog.h"
#include "ui_infoquerydialog.h"
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include "addteacherinfodialog.h"
#include "dialogfactory.h"
#include <QSqlQuery>
#include <QSqlRecord>

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
	ui->m_TeacherInfoTab->hide();

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

	m_Model = new QSqlQueryModel(ui->m_QueryResult);
	ui->m_QueryResult->setModel(m_Model);
	m_Model->setQuery(tr("SELECT ���º�,����,����רҵ,��� from TeachersInfo WHERE 1 = 2"));

	m_DetailAction = new QAction(tr("����"), this);
	m_DeleteAction = new QAction(tr("ɾ��"),this);
	m_Actions.append(m_DetailAction);
	m_Actions.append(m_DeleteAction);

	ui->m_QueryResult->setContextMenuPolicy(Qt::ActionsContextMenu);
	ui->m_QueryResult->addActions(m_Actions);

	ui->m_QueryResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->m_QueryResult->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->m_QueryResult->setSelectionMode(QAbstractItemView::SingleSelection);
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

	connect(ui->m_Query,SIGNAL(clicked()),this,SLOT(onQueryButton()));
	connect(m_DeleteAction,SIGNAL(triggered()),this,SLOT(onDeleteAction()));
	connect(m_DetailAction,SIGNAL(triggered()),this,SLOT(onDetailAction()));
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

void InfoQueryDialog::onQueryButton()
{
	QString queryCondition;
	queryCondition.append(tr("SELECT ���º�,����,����רҵ,��� from TeachersInfo WHERE "));

	if(ui->m_ConditionType1->isVisible())
	{
		QString condition1 = ui->m_ConditionEdit1->text();
		if(condition1 == NULL)
		{
			QMessageBox::information(this,tr("��ʾ"),tr("��ѯ��������Ϊ�ա�"));
			return;
		}
		queryCondition.append(ui->m_ConditionType1->currentText() + " = " + condition1);
	}

	if(ui->m_ConditionType2->isVisible())
	{
		QString condition2 = ui->m_ConditionEdit2->text();
		if(condition2 == NULL)
		{
			QMessageBox::information(this,tr("��ʾ"),tr("��ѯ��������Ϊ�ա�"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType2->currentText() + " = " + condition2);
	}

	if(ui->m_ConditionType3->isVisible())
	{
		QString condition3 = ui->m_ConditionEdit3->text();
		if(condition3 == NULL)
		{
			QMessageBox::information(this,tr("��ʾ"),tr("��ѯ��������Ϊ�ա�"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType3->currentText() + " = " + condition3);
	}

	if(ui->m_ConditionType4->isVisible())
	{
		QString condition4 = ui->m_ConditionEdit4->text();
		if(condition4 == NULL)
		{
			QMessageBox::information(this,tr("��ʾ"),tr("��ѯ��������Ϊ�ա�"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType4->currentText() + " = " + condition4);
	}

	if(ui->m_ConditionType5->isVisible())
	{
		QString condition5 = ui->m_ConditionEdit5->text();
		if(condition5 == NULL)
		{
			QMessageBox::information(this,tr("��ʾ"),tr("��ѯ��������Ϊ�ա�"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType5->currentText() + " = " + condition5);
	}

	m_Model->setQuery(queryCondition);

}

void InfoQueryDialog::onDetailAction()
{
	int row = ui->m_QueryResult->currentIndex().row();
	QModelIndex index = ui->m_QueryResult->model()->index(row,0);
	qDebug()<<"data:"<<index.data().toString();

	QString personnelNo = index.data().toString();

	QString selectSql = tr("SELECT ���º� from TeachersInfo WHERE ���º� = ") + personnelNo;

	QSqlQuery sqlQuery;
	if(!sqlQuery.exec(selectSql))
	{
		//		qDebug()<<m_Database.lastError();
		//		return false;
	}


	m_TeacherInfo = new TeacherInfo;
	QSqlRecord record = sqlQuery.record();

	while(sqlQuery.next())
	{
		m_TeacherInfo->name = record.value(tr("����")).toString();
		m_TeacherInfo->sex = record.value(tr("�Ա�")).toString();
		m_TeacherInfo->nationality = record.value(tr("����")).toString();
		m_TeacherInfo->origin = record.value(tr("����")).toString();
		m_TeacherInfo->id = record.value(tr("���֤��")).toString();
		m_TeacherInfo->birthday = record.value(tr("��������")).toString();
		m_TeacherInfo->politicsStatus = record.value(tr("������ò")).toString();
		m_TeacherInfo->partyTime = record.value(tr("�뵳ʱ��")).toString();
		m_TeacherInfo->department = record.value(tr("����רҵ")).toString();
		m_TeacherInfo->category = record.value(tr("���")).toString();
		m_TeacherInfo->personnelNo = record.value(tr("���º�")).toString();
		m_TeacherInfo->titleAndRank = record.value(tr("ְ��ְ��")).toString();
		m_TeacherInfo->titleTime = record.value(tr("ְ��ְ��ʱ��")).toString();
		m_TeacherInfo->currentPositionTime = record.value(tr("����ְʱ��")).toString();
		m_TeacherInfo->academicParttime = record.value(tr("ѧ����ְ���")).toString();
		m_TeacherInfo->personnelPlan = record.value(tr("���˲żƻ����")).toString();
		m_TeacherInfo->administrationParttime = record.value(tr("������ְ")).toString();
		m_TeacherInfo->otherParttime = record.value(tr("������ְ")).toString();
		m_TeacherInfo->graduateTrain = record.value(tr("�о�������")).toString();
		m_TeacherInfo->teacherTime = record.value(tr("�β���ʱ��")).toString();
		m_TeacherInfo->bachelorTime = record.value(tr("ѧʿѧλȡ��ʱ��")).toString();
		m_TeacherInfo->masterTime = record.value(tr("˶ʿѧλȡ��ʱ��")).toString();
		m_TeacherInfo->doctorTime = record.value(tr("��ʿѧλȡ��ʱ��")).toString();
		m_TeacherInfo->firstWorkTime = record.value(tr("�������ʱ��")).toString();
		m_TeacherInfo->firstWorkPlace = record.value(tr("���������λ")).toString();
		m_TeacherInfo->whuTime = record.value(tr("����Ժʱ��")).toString();
		m_TeacherInfo->beAbroadExperience = record.value(tr("�������ع����")).toString();
		m_TeacherInfo->retirementTime = record.value(tr("����ʱ��")).toString();
		m_TeacherInfo->email = record.value(tr("��������")).toString();
		m_TeacherInfo->officePhone = record.value(tr("�칫�绰")).toString();
		m_TeacherInfo->mobilePhone = record.value(tr("�ƶ��绰")).toString();
	}

	if(sqlQuery.next())
	{
		QMessageBox::warning(this,tr("������"),tr("�����˵����º���ͬ"));
	}

	ui->m_TeacherInfoTab->show();
	setTeachersInfo(*m_TeacherInfo);
}

void InfoQueryDialog::onDeleteAction()
{

}

void InfoQueryDialog::setTeachersInfo(TeacherInfo &teacherInfo)
{
	ui->m_Name->setText(teacherInfo.name);
	teacherInfo.sex == "��" ?
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


