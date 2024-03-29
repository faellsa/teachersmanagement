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
#include <QMap>
#include <QPalette>

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
	ui->m_ConditionComboBox6->hide();
	ui->m_ConditionComboBox7->hide();
	ui->m_ConditionComboBox8->hide();

	ui->m_ConditionEdit1->hide();
	ui->m_ConditionEdit2->hide();
	ui->m_ConditionEdit3->hide();
	ui->m_ConditionEdit4->hide();
	ui->m_ConditionEdit5->hide();
	ui->m_ConditionEdit6->hide();
	ui->m_ConditionEdit7->hide();
	ui->m_ConditionEdit8->hide();

	ui->m_ConditionFrame2->hide();
	ui->m_ConditionFrame3->hide();
	ui->m_ConditionFrame4->hide();
	ui->m_ConditionFrame5->hide();
	ui->m_ConditionFrame6->hide();
	ui->m_ConditionFrame7->hide();
	ui->m_ConditionFrame8->hide();

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

	ui->m_RankTime->hide();

	QPalette pal;
	pal.setColor(QPalette::AlternateBase,QColor(225,255,255));
	ui->m_QueryResult->setAlternatingRowColors(true);
	ui->m_QueryResult->setPalette(pal);
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
	connect(ui->m_ConditionType6,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType7,SIGNAL(currentIndexChanged(QString)),
			this,SLOT(showConditionWidget(QString)));
	connect(ui->m_ConditionType8,SIGNAL(currentIndexChanged(QString)),
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

	connect(ui->m_PoliticsStatus,SIGNAL(currentIndexChanged(QString)),this,SLOT(onPoliticsStatus(QString)));

	connect(ui->m_PoliticsStatus,SIGNAL(currentIndexChanged(QString)),this,SLOT(onPoliticsStatus(QString)));
	connect(ui->m_GraduateTrain,SIGNAL(currentIndexChanged(QString)),this,SLOT(onGraduateTrain(QString)));
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
	else if(sender()->objectName() == "m_ConditionType6")
	{
		ui->m_ConditionEdit6->show();
		ui->m_ConditionComboBox6->hide();
	}
	else if(sender()->objectName() == "m_ConditionType7")
	{
		ui->m_ConditionEdit7->show();
		ui->m_ConditionComboBox7->hide();
	}
	else if(sender()->objectName() == "m_ConditionType8")
	{
		ui->m_ConditionEdit8->show();
		ui->m_ConditionComboBox8->hide();
	}
}

void InfoQueryDialog::onQueryButton()
{
	QString queryCondition = NULL;
	queryCondition.append(tr("SELECT * from TeachersInfo WHERE "));
	isShowDetail(ui->m_ShowDetail->checkState());
	bool isAnd = false;

	QMap<QComboBox *,QLineEdit *> frameToLineEdit;
	frameToLineEdit.insert(ui->m_ConditionType1,ui->m_ConditionEdit1);
	frameToLineEdit.insert(ui->m_ConditionType2,ui->m_ConditionEdit2);
	frameToLineEdit.insert(ui->m_ConditionType3,ui->m_ConditionEdit3);
	frameToLineEdit.insert(ui->m_ConditionType4,ui->m_ConditionEdit4);
	frameToLineEdit.insert(ui->m_ConditionType5,ui->m_ConditionEdit5);
	frameToLineEdit.insert(ui->m_ConditionType6,ui->m_ConditionEdit6);
	frameToLineEdit.insert(ui->m_ConditionType7,ui->m_ConditionEdit7);
	frameToLineEdit.insert(ui->m_ConditionType8,ui->m_ConditionEdit8);

	QMap<QComboBox *,QLineEdit *>::const_iterator it = frameToLineEdit.begin();
	for(;it != frameToLineEdit.end(); it++)
	{
		if(it.key()->isVisible())
		{

			QString condition = it.value()->text();
			if(condition == NULL)
			{
				QMessageBox::information(this,tr("提示"),tr("查询条件不能为空。"));
				return;
			}

			if(isAnd == true)
				queryCondition.append(" AND ");

			queryCondition.append(it.key()->currentText() + " = '" + condition + "'");
			isAnd = true;
		}
	}

	m_Model->setQuery(queryCondition);

}

void InfoQueryDialog::onDetailAction()
{
	int row = ui->m_QueryResult->currentIndex().row();

	int column = 0;
	for(column = 0; column != attributeNum; column++)
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

	int column;
	for(column = 0; column != attributeNum; column++)
	{
		if(m_Model->headerData(column,Qt::Horizontal).toString().compare(tr("人事号")) == 0)
			break;
	}

	QModelIndex index = ui->m_QueryResult->model()->index(row,column);

	m_PersonnelNo = index.data().toString();

	TeachersInfoTable *teacherInfoTable = DataCenter::instance()->techersInfoTableInstance();

	if(!teacherInfoTable->deleteTeacherInfo(tr("人事号"),m_PersonnelNo))
	{
		QMessageBox::warning(this,tr("错误"),tr("删除失败"));
		return;
	}
	else
	{
		QMessageBox::information(this,tr("成功"),tr("删除成功"));
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
	ui->m_Birthday->setDate(QDate::fromString(teacherInfo.birthday,QString("yyyy-M-d")));
	ui->m_PoliticsStatus->setCurrentIndex(ui->m_PoliticsStatus->findText(teacherInfo.politicsStatus));

	if(teacherInfo.partyTime == tr("无"))
		ui->m_PartyTime->hide();
	else
		ui->m_PartyTime->setDate(QDate::fromString(teacherInfo.partyTime,QString("yyyy-M-d")));

	ui->m_Department->setCurrentIndex(ui->m_Department->findText(teacherInfo.department));
	ui->m_Category->setCurrentIndex(ui->m_Category->findText(teacherInfo.category));
	ui->m_PersonnelNo->setText(teacherInfo.personnelNo);
	ui->m_Title->setText(teacherInfo.title);
	ui->m_TitleTime->setDate(QDate::fromString(teacherInfo.titleTime,QString("yyyy-M-d")));
	ui->m_Rank->setText(teacherInfo.rank);
	//	ui->m_RankTime->setDate(QDate::fromString(teacherInfo.rankTime,QString("yyyy-M-d")));
	ui->m_CurrentPositionTime->setDate(QDate::fromString(teacherInfo.currentPositionTime,QString("yyyy-M-d")));
	ui->m_AcademicPartTime->setText(teacherInfo.academicParttime);
	ui->m_PersonnelPlan->setText(teacherInfo.personnelPlan);
	ui->m_Honour->setText(teacherInfo.honour);
	ui->m_AdministrationParttime->setText(teacherInfo.administrationParttime);
	ui->m_OtherParttime->setText(teacherInfo.otherParttime);
	ui->m_GraduateTrain->setCurrentIndex(ui->m_GraduateTrain->findText(teacherInfo.graduateTrain));

	if(teacherInfo.teacherTime == tr("无"))
		ui->m_TeacherTime->hide();
	else
		ui->m_TeacherTime->setDate(QDate::fromString(teacherInfo.teacherTime,QString("yyyy-M-d")));

	ui->m_BachelorTime->setDate(QDate::fromString(teacherInfo.bachelorTime,QString("yyyy-M-d")));
	ui->m_MasterTime->setDate(QDate::fromString(teacherInfo.masterTime,QString("yyyy-M-d")));
	ui->m_DoctorTime->setDate(QDate::fromString(teacherInfo.doctorTime,QString("yyyy-M-d")));
	ui->m_FirstWorkTime->setDate(QDate::fromString(teacherInfo.firstWorkTime,QString("yyyy-M-d")));
	ui->m_FirstWorkPlace->setText(teacherInfo.firstWorkPlace);
	ui->m_WhuTime->setDate(QDate::fromString(teacherInfo.whuTime,QString("yyyy-M-d")));
	ui->m_BeAbroadExperience->setText(teacherInfo.beAbroadExperience);
	ui->m_RetirementTime->setDate(QDate::fromString(teacherInfo.retirementTime,QString("yyyy-M-d")));
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
	if(ui->m_Name->text().isEmpty() || ui->m_PersonnelNo->text().isEmpty())
	{
		QMessageBox::warning(this,tr("提示"),tr("姓名和人事号不能为空"));
		return;
	}

	if(ui->m_PersonnelNo->text().size() != 8)
	{
		QMessageBox::warning(this,tr("提示"),tr("人事号需为8位"));
		return;
	}

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
		teacherInfo->birthday = ui->m_Birthday->date().toString("yyyy-M-d");
		teacherInfo->politicsStatus = ui->m_PoliticsStatus->currentText();

		if(teacherInfo->politicsStatus != tr("群众"))
			teacherInfo->partyTime = ui->m_PartyTime->date().toString("yyyy-M-d");
		else
			teacherInfo->partyTime = tr("无");

		teacherInfo->department = ui->m_Department->currentText();
		teacherInfo->category = ui->m_Category->currentText();
		teacherInfo->personnelNo = ui->m_PersonnelNo->text();
		teacherInfo->title = ui->m_Title->text();
		teacherInfo->titleTime = ui->m_TitleTime->date().toString("yyyy-M-d");
		teacherInfo->rank = ui->m_Rank->text();
		//		teacherInfo->rankTime = ui->m_RankTime->date().toString("yyyy-M-d");
		teacherInfo->currentPositionTime = ui->m_CurrentPositionTime->date().toString("yyyy-M-d");
		teacherInfo->academicParttime = ui->m_AcademicPartTime->text();
		teacherInfo->personnelPlan = ui->m_PersonnelPlan->text();
		teacherInfo->honour = ui->m_Honour->text();
		teacherInfo->administrationParttime = ui->m_AdministrationParttime->text();
		teacherInfo->otherParttime = ui->m_OtherParttime->text();
		teacherInfo->graduateTrain = ui->m_GraduateTrain->currentText();

		if(teacherInfo->graduateTrain != tr("无"))
			teacherInfo->teacherTime = ui->m_TeacherTime->date().toString("yyyy-M-d");
		else
			teacherInfo->teacherTime = tr("无");

		teacherInfo->bachelorTime = ui->m_BachelorTime->date().toString("yyyy-M-d");
		teacherInfo->masterTime = ui->m_MasterTime->date().toString("yyyy-M-d");
		teacherInfo->doctorTime = ui->m_DoctorTime->date().toString("yyyy-M-d");
		teacherInfo->firstWorkTime = ui->m_FirstWorkTime->date().toString("yyyy-M-d");
		teacherInfo->firstWorkPlace = ui->m_FirstWorkPlace->text();
		teacherInfo->whuTime = ui->m_WhuTime->date().toString("yyyy-M-d");
		teacherInfo->beAbroadExperience = ui->m_BeAbroadExperience->toPlainText();
		teacherInfo->retirementTime = ui->m_RetirementTime->date().toString("yyyy-M-d");
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
	if(ui->m_ShowDetail->checkState() == Qt::Checked)
	{
		exportExcelObject->addField(0, tr("人事号"), "varchar(10)");
		exportExcelObject->addField(1, tr("姓名"), "varchar(20)");
		exportExcelObject->addField(2, tr("性别"), "varchar(10)");
		exportExcelObject->addField(3, tr("民族"), " varchar(20)");
		exportExcelObject->addField(4, tr("籍贯"), "varchar(20)");
		exportExcelObject->addField(5, tr("身份证号"), "varchar(20)");
		exportExcelObject->addField(6, tr("出生年月"), "varchar(20)");
		exportExcelObject->addField(7, tr("政治面貌"), "varchar(20)");
		exportExcelObject->addField(8, tr("入党时间"), "varchar(20)");
		exportExcelObject->addField(9, tr("所在专业"), "varchar(30)");
		exportExcelObject->addField(10, tr("类别"), "varchar(20)");
		exportExcelObject->addField(11, tr("职称"), "varchar(30)");
		exportExcelObject->addField(12, tr("职称晋升时间"), "varchar(20)");
		exportExcelObject->addField(13, tr("职级"), "varchar(30)");
		//	exportExcelObject->addField(14, tr("职级晋升时间"),"varchar(20)");
		exportExcelObject->addField(14, tr("任现职时间"), "varchar(20)");
		exportExcelObject->addField(15, tr("学术兼职情况"), "varchar(100)");
		exportExcelObject->addField(16, tr("获人才计划情况"), "varchar(100)");
		exportExcelObject->addField(17, tr("荣誉称号"), "varchar(100)");
		exportExcelObject->addField(18, tr("行政兼职"), "varchar(50)");
		exportExcelObject->addField(19, tr("其他兼职"), "varchar(50)");
		exportExcelObject->addField(20, tr("研究生培养"), "varchar(50)");
		exportExcelObject->addField(21, tr("任博导时间"), "varchar(20)");
		exportExcelObject->addField(22, tr("学士学位取得时间"), "varchar(20)");
		exportExcelObject->addField(23, tr("硕士学位取得时间"), "varchar(20)");
		exportExcelObject->addField(24, tr("博士学位取得时间"), "varchar(20)");
		exportExcelObject->addField(25, tr("最初工作时间"), "varchar(20)");
		exportExcelObject->addField(26, tr("最初工作单位"), "varchar(50)");
		exportExcelObject->addField(27, tr("到本院工作时间"), "varchar(20)");
		exportExcelObject->addField(28, tr("出国及回国情况"), "varchar(200)");
		exportExcelObject->addField(29, tr("退休时间"), "varchar(20)");
		exportExcelObject->addField(30, tr("电子邮箱"), "varchar(20)");
		exportExcelObject->addField(31, tr("办公电话"), "varchar(20)");
		exportExcelObject->addField(32, tr("移动电话"), "varchar(20)");
	}
	else
	{
		exportExcelObject->addField(0 ,tr("人事号"),"varchar(8)");
		exportExcelObject->addField(1, tr("姓名"), "varchar(20)");
		exportExcelObject->addField(2, tr("出生年月"),"varchar(20)");
		exportExcelObject->addField(3, tr("所在专业"),"varchar(30)");
		exportExcelObject->addField(4, tr("职称"),"varchar(30)");
		exportExcelObject->addField(5, tr("任现职时间"),"varchar(20)");
	}

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
		qDebug()<<"ret:"<<ret;
		QMessageBox::critical(this, tr("错误"), tr("Excel文档导出失败！"));
	}

	delete exportExcelObject;
}

void InfoQueryDialog::isShowDetail(int checkeState)
{
	if(checkeState == Qt::Checked)
	{
		for(int i = 0; i != attributeNum; i++)
		{
			ui->m_QueryResult->setColumnHidden(i,false);
		}
	}
	else if(checkeState == Qt::Unchecked)
	{
		for(int i = 0; i != attributeNum; i++)
		{
			ui->m_QueryResult->setColumnHidden(i,true);
		}

		ui->m_QueryResult->setColumnHidden(0,false);
		ui->m_QueryResult->setColumnHidden(1,false);
		ui->m_QueryResult->setColumnHidden(6,false);
		ui->m_QueryResult->setColumnHidden(9,false);
		ui->m_QueryResult->setColumnHidden(11,false);
		ui->m_QueryResult->setColumnHidden(14,false);
	}
}

void InfoQueryDialog::onPoliticsStatus(QString politicsStatus)
{
	if(politicsStatus == tr("群众"))
		ui->m_PartyTime->setVisible(false);
	else
		ui->m_PartyTime->setVisible(true);
}

void InfoQueryDialog::onGraduateTrain(QString graduateTrain)
{
	if(graduateTrain == tr("无"))
		ui->m_TeacherTime->setVisible(false);
	else
		ui->m_TeacherTime->setVisible(true);
}
