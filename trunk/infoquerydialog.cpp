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
#include <datacenter.h>
#include <QVector>
#include <QFileDialog>
#include "exportexcelobject.h"
#include <QProgressDialog>
#include <QCheckBox>

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
	m_Model->setQuery(tr("SELECT * from TeachersInfo WHERE 1 = 2"));
	isShowDetail(ui->m_ShowDetail->checkState());

	m_EditAction = new QAction(tr("编辑"), this);
	m_DeleteAction = new QAction(tr("删除"),this);
	m_Actions.append(m_EditAction);
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
	connect(m_EditAction,SIGNAL(triggered()),this,SLOT(onDetailAction()));

	connect(ui->m_Page1Next,SIGNAL(clicked()),this,SLOT(showPoliticalInfoPage()));

	connect(ui->m_Page2Pre,SIGNAL(clicked()),this,SLOT(showPersonalInfoPage()));
	connect(ui->m_Page2Next,SIGNAL(clicked()),this,SLOT(showWorkInfoPage()));

	connect(ui->m_Page3Pre,SIGNAL(clicked()),this,SLOT(showPoliticalInfoPage()));
	connect(ui->m_Page3Next,SIGNAL(clicked()),this,SLOT(showPersonalExperiencePage()));

	connect(ui->m_Page4Pre,SIGNAL(clicked()),this,SLOT(showWorkInfoPage()));
	connect(ui->m_Page4Next,SIGNAL(clicked()),this,SLOT(showRemarkPage()));

	connect(ui->m_Page5Pre,SIGNAL(clicked()),this,SLOT(showPersonalExperiencePage()));

	connect(ui->m_Ok,SIGNAL(clicked()),this,SLOT(onOkButton()));

	connect(ui->m_ExportExcel,SIGNAL(clicked()),this,SLOT(onExportExcel()));
	connect(ui->m_ShowDetail,SIGNAL(stateChanged(int)),this,SLOT(isShowDetail(int)));
}

void InfoQueryDialog::showConditionWidget(QString conditionType)
{
	//	if(conditionType == tr("姓名") || conditionType == tr("身份证号")
	//		|| conditionType == tr("人事号") || conditionType == tr("职称职级")
	//		|| conditionType == tr("行政兼职") || conditionType == tr("民族"))
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
	queryCondition.append(tr("SELECT * from TeachersInfo WHERE "));
	isShowDetail(ui->m_ShowDetail->checkState());

	if(ui->m_ConditionType1->isVisible())
	{
		QString condition1 = ui->m_ConditionEdit1->text();
		if(condition1 == NULL)
		{
			QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
			return;
		}
		queryCondition.append(ui->m_ConditionType1->currentText() + " = '" + condition1 + "'");
	}

	if(ui->m_ConditionType2->isVisible())
	{
		QString condition2 = ui->m_ConditionEdit2->text();
		if(condition2 == NULL)
		{
			QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType2->currentText() + " = '" + condition2 + "'");
	}

	if(ui->m_ConditionType3->isVisible())
	{
		QString condition3 = ui->m_ConditionEdit3->text();
		if(condition3 == NULL)
		{
			QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType3->currentText() + " = '" + condition3+ "'");
	}

	if(ui->m_ConditionType4->isVisible())
	{
		QString condition4 = ui->m_ConditionEdit4->text();
		if(condition4 == NULL)
		{
			QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType4->currentText() + " = '" + condition4 + "'");
	}

	if(ui->m_ConditionType5->isVisible())
	{
		QString condition5 = ui->m_ConditionEdit5->text();
		if(condition5 == NULL)
		{
			QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
			return;
		}
		queryCondition.append(" AND " + ui->m_ConditionType5->currentText() + " = '" + condition5 + "'");
	}

	m_Model->setQuery(queryCondition);

}

void InfoQueryDialog::onDetailAction()
{
	int row = ui->m_QueryResult->currentIndex().row();

	int column = 0;
	for(column = 0; column != 31; column++)
	{
		if(m_Model->headerData(column,Qt::Horizontal).toString().compare(tr("人事号")) == 0)
			break;
	}

	QModelIndex index = ui->m_QueryResult->model()->index(row,column);

	m_PersonnelNo = index.data().toString();

	TeachersInfoTable *teacherInfoTable = DataCenter::instance()->techersInfoTableInstance();

	QVector<TeacherInfo *> teacherInfoList;
	if(!teacherInfoTable->queryTeacherInfo(tr("人事号"),m_PersonnelNo,teacherInfoList))
	{
		QMessageBox::warning(this,tr("错误"),tr("获取详情失败"));
		return;
	}

	ui->m_TeacherInfoTab->show();
	ui->m_QueryFrame->hide();

	TeacherInfo *teacherInfo = teacherInfoList[0];
	if(teacherInfo != NULL)
	{
		setTeachersInfo(*teacherInfo);
	}
}

void InfoQueryDialog::onDeleteAction()
{
	int row = ui->m_QueryResult->currentIndex().row();

	QModelIndex index = ui->m_QueryResult->model()->index(row,0);

	m_PersonnelNo = index.data().toString();

	TeachersInfoTable *teacherInfoTable = DataCenter::instance()->techersInfoTableInstance();

	if(!teacherInfoTable->deleteTeacherInfo(tr("人事号"),m_PersonnelNo))
	{
		QMessageBox::warning(this,tr("错误"),tr("删除失败"));
		return;
	}
	else
	{
		onQueryButton();
	}
}

void InfoQueryDialog::setTeachersInfo(TeacherInfo &teacherInfo)
{
	ui->m_Name->setText(teacherInfo.name);
	ui->m_Sex->setCurrentIndex(ui->m_Sex->findText(teacherInfo.sex));
	ui->m_Nationality->setText(teacherInfo.nationality);
	ui->m_Origin->setText(teacherInfo.origin);
	ui->m_ID->setText(teacherInfo.id);
	ui->m_Birthday->setDate(QDate::fromString(teacherInfo.birthday,QString("yyyy/M")));
	ui->m_PoliticsStatus->setCurrentIndex(ui->m_PoliticsStatus->findText(teacherInfo.politicsStatus));
	ui->m_PartyTime->setDate(QDate::fromString(teacherInfo.partyTime,QString("yyyy/M")));
	ui->m_Department->setCurrentIndex(ui->m_Department->findText(teacherInfo.department));
	ui->m_Category->setCurrentIndex(ui->m_Category->findText(teacherInfo.category));
	ui->m_PersonnelNo->setText(teacherInfo.personnelNo);
	ui->m_TitleAndRank->setText(teacherInfo.titleAndRank);
	ui->m_TitleTime->setDate(QDate::fromString(teacherInfo.titleTime,QString("yyyy/M")));
	ui->m_CurrentPositionTime->setDate(QDate::fromString(teacherInfo.currentPositionTime,QString("yyyy/M")));
	ui->m_AcademicPartTime->setText(teacherInfo.academicParttime);
	ui->m_PersonnelPlan->setText(teacherInfo.personnelPlan);
	ui->m_AdministrationParttime->setText(teacherInfo.administrationParttime);
	ui->m_OtherParttime->setText(teacherInfo.otherParttime);
	ui->m_GraduateTrain->setCurrentIndex(ui->m_GraduateTrain->findText(teacherInfo.graduateTrain));
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

void InfoQueryDialog::showPersonalInfoPage()
{
	ui->m_TeacherInfoTab->setCurrentIndex(0);
}

void InfoQueryDialog::showPoliticalInfoPage()
{
	ui->m_TeacherInfoTab->setCurrentIndex(1);
}

void InfoQueryDialog::showWorkInfoPage()
{
	ui->m_TeacherInfoTab->setCurrentIndex(2);
}

void InfoQueryDialog::showPersonalExperiencePage()
{
	ui->m_TeacherInfoTab->setCurrentIndex(3);
}

void InfoQueryDialog::showRemarkPage()
{
	ui->m_TeacherInfoTab->setCurrentIndex(4);
}

void InfoQueryDialog::onOkButton()
{
	ui->m_TeacherInfoTab->hide();
	ui->m_TeacherInfoTab->setCurrentIndex(0);
	ui->m_QueryFrame->show();

	if(DataCenter::instance()->techersInfoTableInstance()->deleteTeacherInfo(tr("人事号"),m_PersonnelNo))
	{
		TeacherInfo *teacherInfo = new TeacherInfo;
		teacherInfo->name = ui->m_Name->text();
		teacherInfo->sex = ui->m_Sex->currentText();
		teacherInfo->nationality = ui->m_Nationality->text();
		teacherInfo->origin = ui->m_Origin->text();
		teacherInfo->id = ui->m_ID->text();
		teacherInfo->birthday = ui->m_Birthday->date().toString("yyyy/M");
		teacherInfo->politicsStatus = ui->m_PoliticsStatus->currentText();
		teacherInfo->partyTime = ui->m_PartyTime->date().toString("yyyy/M");
		teacherInfo->department = ui->m_Department->currentText();
		teacherInfo->category = ui->m_Category->currentText();
		teacherInfo->personnelNo = ui->m_PersonnelNo->text();
		teacherInfo->titleAndRank = ui->m_TitleAndRank->text();
		teacherInfo->titleTime = ui->m_TitleTime->date().toString("yyyy/M");
		teacherInfo->currentPositionTime = ui->m_CurrentPositionTime->date().toString("yyyy/M");
		teacherInfo->academicParttime = ui->m_AcademicPartTime->text();
		teacherInfo->personnelPlan = ui->m_PersonnelPlan->text();
		teacherInfo->administrationParttime = ui->m_AdministrationParttime->text();
		teacherInfo->otherParttime = ui->m_OtherParttime->text();
		teacherInfo->graduateTrain = ui->m_GraduateTrain->currentText();
		teacherInfo->teacherTime = ui->m_TeacherTime->date().toString("yyyy/M");
		teacherInfo->bachelorTime = ui->m_BachelorTime->date().toString("yyyy/M");
		teacherInfo->masterTime = ui->m_MasterTime->date().toString("yyyy/M");
		teacherInfo->doctorTime = ui->m_DoctorTime->date().toString("yyyy/M");
		teacherInfo->firstWorkTime = ui->m_FirstWorkTime->date().toString("yyyy/M");
		teacherInfo->firstWorkPlace = ui->m_FirstWorkPlace->text();
		teacherInfo->whuTime = ui->m_WhuTime->date().toString("yyyy/M");
		teacherInfo->beAbroadExperience = ui->m_BeAbroadExperience->toPlainText();
		teacherInfo->retirementTime = ui->m_RetirementTime->date().toString("yyyy/M");
		teacherInfo->email = ui->m_Email->text();
		teacherInfo->officePhone = ui->m_OfficePhone->text();
		teacherInfo->mobilePhone = ui->m_MobilePhone->text();

		if(DataCenter::instance()->techersInfoTableInstance()->newTeacherInfo(*teacherInfo))
			QMessageBox::information(this,tr("成功"),tr("修改成功"));
	}

}

void InfoQueryDialog::onExportExcel()
{
	QString filePath = QFileDialog::getSaveFileName(this, tr("请选择要导出的excel文件路径"), "", tr("Excel 文件(*.xls)"));

	if(filePath == "")
		return;

	ExportExcelObject *exportExcelObject = new ExportExcelObject(filePath, tr("教职工信息表"), ui->m_QueryResult);
	exportExcelObject->addField(0, tr("姓名"), "varchar(20)");
	exportExcelObject->addField(1, tr("性别"), "varchar(10)");
	exportExcelObject->addField(2, tr("民族")," varchar(20)");
	exportExcelObject->addField(3, tr("籍贯"),"varchar(20)");
	exportExcelObject->addField(4, tr("身份证号"),"varchar(20)");
	exportExcelObject->addField(5, tr("出生年月"),"varchar(20)");
	exportExcelObject->addField(6, tr("政治面貌"),"varchar(20)");
	exportExcelObject->addField(7, tr("入党时间"),"varchar(20)");
	exportExcelObject->addField(8, tr("所在专业"),"varchar(30)");
	exportExcelObject->addField(9, tr("类别"),"varchar(20)");
	exportExcelObject->addField(10 ,tr("人事号"),"varchar(8)");
	exportExcelObject->addField(11, tr("职称职级"),"varchar(30)");
	exportExcelObject->addField(12, tr("职称职级晋升时间"),"varchar(20)");
	exportExcelObject->addField(13, tr("任现职时间"),"varchar(50)");
	exportExcelObject->addField(14, tr("学术兼职情况"),"varchar(50)");
	exportExcelObject->addField(15, tr("获人才计划情况"),"varchar(50)");
	exportExcelObject->addField(16, tr("行政兼职"), "varchar(50)");
	exportExcelObject->addField(17, tr("其他兼职"), "varchar(50)");
	exportExcelObject->addField(18, tr("研究生培养"),"varchar(50)");
	exportExcelObject->addField(19, tr("任博导时间"),"varchar(20)");
	exportExcelObject->addField(20, tr("学士学位取得时间"),"varchar(20)");
	exportExcelObject->addField(21, tr("硕士学位取得时间"),"varchar(20)");
	exportExcelObject->addField(22, tr("博士学位取得时间"),"varchar(20)");
	exportExcelObject->addField(23, tr("最初工作时间"),"varchar(20)");
	exportExcelObject->addField(24, tr("最初工作单位"),"varchar(20)");
	exportExcelObject->addField(25 ,tr("到本院工作时间"),"varchar(20)");
	exportExcelObject->addField(26, tr("出国及回国情况"),"varchar(200)");
	exportExcelObject->addField(27, tr("退休时间"),"varchar(20)");
	exportExcelObject->addField(28, tr("电子邮箱"),"varchar(20)");
	exportExcelObject->addField(29, tr("办公电话"),"varchar(20)");
	exportExcelObject->addField(30, tr("移动电话"),"varchar(20)");

	QProgressDialog progressDialog;
	progressDialog.setRange(0, m_Model->rowCount());
	connect(exportExcelObject, SIGNAL(exportedRowCount(int)), &progressDialog, SLOT(setValue(int)));
	progressDialog.show();

	int ret = exportExcelObject->export2Excel();

	if(ret > 0)
	{
		QMessageBox::information(this, tr("消息"), tr("Excel文档导出成功！"));
	}
	else
	{
		QMessageBox::critical(this, tr("错误"), tr("Excel文档导出失败！"));
	}

	delete exportExcelObject;
}

void InfoQueryDialog::isShowDetail(int checkeState)
{
	if(checkeState == Qt::Checked)
	{
		for(int i = 0; i != 31; i++)
		{
			ui->m_QueryResult->setColumnHidden(i,false);
		}
	}
	else if(checkeState == Qt::Unchecked)
	{
		for(int i = 0; i != 31; i++)
		{
			ui->m_QueryResult->setColumnHidden(i,true);
		}

		ui->m_QueryResult->setColumnHidden(0,false);
		ui->m_QueryResult->setColumnHidden(8,false);
		ui->m_QueryResult->setColumnHidden(10,false);
		ui->m_QueryResult->setColumnHidden(11,false);
	}
}
