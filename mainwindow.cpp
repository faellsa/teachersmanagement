#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagementdialog.h"
#include <QMessageBox>
#include "databaseexception.h"
//#include "personalinfodialog.h"
#include "addteacherinfodialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_ChildDialogBase(NULL)
{
    ui->setupUi(this);


	try{
		m_DataCenter = DataCenter::instance();
	}catch(DatabaseException& e)
	{
		QMessageBox::critical(this, tr("���ش���"), tr("�������ݿ����\n")+e.errorMsg());
		::exit(1);
	}

	setupWidgets();
	setupSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWidgets()
{
	resize(1000,700);

	ui->groupBox->setStyleSheet("background-image: url(:/image/title.png);"
								"border:rgb(103,207,255)");

	m_HSplitter = new QSplitter(this);
	ui->m_MainLayout->addWidget(m_HSplitter);

	m_FunctionTree = new QTreeWidget(this);
	m_FunctionTree->setMaximumWidth(200);
	m_FunctionTree->setHeaderHidden(true);
	m_FunctionTree->setColumnCount(1);

	m_SystemManage = new QTreeWidgetItem(QStringList(tr("ϵͳ����")));
	m_UserManagement = new QTreeWidgetItem(QStringList(tr("�û��˻�")), m_UserManagementType);
	m_SystemManage->addChild(m_UserManagement);

	m_InfoManage = new QTreeWidgetItem(QStringList(tr("��ʦ��Ϣ����")));
	m_AddTeacherInfo = new QTreeWidgetItem(QStringList(tr("���Ӽ�¼")),m_AddTeacherInfoType);

//	m_PersonalInfo = new QTreeWidgetItem(QStringList(tr("������Ϣ")),m_PersonalInfoType);
//	m_PoliticalInfo = new QTreeWidgetItem(QStringList(tr("������ò")));
//	m_WorkInfo = new QTreeWidgetItem(QStringList(tr("������Ϣ")));
//	m_PersonalExperience = new QTreeWidgetItem(QStringList(tr("���˾���")));
//	m_Remark = new QTreeWidgetItem(QStringList(tr("��ע")));

//	m_AddTeacherInfo->addChild(m_PersonalInfo);
//	m_AddTeacherInfo->addChild(m_PoliticalInfo);
//	m_AddTeacherInfo->addChild(m_WorkInfo);
//	m_AddTeacherInfo->addChild(m_PersonalExperience);
//	m_AddTeacherInfo->addChild(m_Remark);

	m_InfoQuery = new QTreeWidgetItem(QStringList(tr("��Ϣ��ѯ")));

	m_InfoManage->addChild(m_AddTeacherInfo);
	m_InfoManage->addChild(m_InfoQuery);

	m_FunctionTree->insertTopLevelItem(0,m_SystemManage);
	m_FunctionTree->insertTopLevelItem(1,m_InfoManage);

	m_DialogFactory = DialogFactory::instance();
	m_DialogFactory->setContentsMargins(0,0,0,0);

	m_HSplitter->addWidget(m_FunctionTree);
	m_HSplitter->addWidget(m_DialogFactory);
	m_HSplitter->setContentsMargins(0,0,0,0);
}

void MainWindow::setupSignals()
{
	connect(m_FunctionTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
			this,SLOT(onFunctionTreeItemClick(QTreeWidgetItem*,int)));

	connect(ui->m_Exit,SIGNAL(triggered()),this,SLOT(exit()));
}

void MainWindow::onFunctionTreeItemClick(QTreeWidgetItem *treeWidgetItem,int)
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	if(treeWidgetItem->type() == m_UserManagementType)
		m_ChildDialogBase = new UserManagementDialog();

	else if(treeWidgetItem->type() == m_PersonalInfoType)
		m_ChildDialogBase = new AddTeacherInfoDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);

}


void MainWindow::exit()
{
	QApplication::exit(0);
}

