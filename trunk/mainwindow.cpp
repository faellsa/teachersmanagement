#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagementdialog.h"
#include <QMessageBox>
#include <QCloseEvent>
#include "databaseexception.h"
//#include "personalinfodialog.h"
#include "addteacherinfodialog.h"
#include "infoquerydialog.h"
#include "QMenuBar"
#include "QMenu"
#include "timelabel.h"

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		m_ChildDialogBase(NULL)
{
    ui->setupUi(this);

	try{
		m_DataCenter = DataCenter::instance();
		m_DataCenter->techersInfoTableInstance();
		m_DataCenter->accountManageInstance();
	}catch(DatabaseException& e)
	{
		QMessageBox::critical(this, tr("严重错误！"), tr("连接数据库出错！\n")+e.errorMsg());
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
	resize(1000,750);
	setWindowTitle(tr("生命科学学院教职工信息管理系统"));

	ui->groupBox->setStyleSheet("background-image: url(:/image/title.png);"
								"border:rgb(103,207,255)");

	m_HSplitter = new QSplitter(this);
	ui->m_MainLayout->addWidget(m_HSplitter);

	m_FunctionTree = new QTreeWidget(this);
	m_FunctionTree->setMaximumWidth(200);
	m_FunctionTree->setHeaderHidden(true);
	m_FunctionTree->setColumnCount(1);

	m_SystemManage = new QTreeWidgetItem(QStringList(tr("系统管理")));
	m_SystemManage->setFont(0,QFont("Times",12));
	m_SystemManage->setIcon(0,QIcon(":/image/folder_closed.gif"));
	m_UserManagement = new QTreeWidgetItem(QStringList(tr("用户账户")), m_UserManagementType);
	m_UserManagement->setFont(0,QFont(tr("Times"),11));
	m_UserManagement->setIcon(0,QIcon(":/image/tree_node.gif"));
	m_SystemManage->addChild(m_UserManagement);

	m_InfoManage = new QTreeWidgetItem(QStringList(tr("教师信息管理")));
	m_InfoManage->setFont(0,QFont("Times",12));
	m_InfoManage->setIcon(0,QIcon(":/image/folder_closed.gif"));
	m_AddTeacherInfo = new QTreeWidgetItem(QStringList(tr("增加记录")),m_AddTeacherInfoType);
	m_AddTeacherInfo->setFont(0,QFont(tr("Times"), 11));
	m_AddTeacherInfo->setIcon(0,QIcon(":/image/tree_node.gif"));

	//	m_PersonalInfo = new QTreeWidgetItem(QStringList(tr("个人信息")),m_PersonalInfoType);
	//	m_PoliticalInfo = new QTreeWidgetItem(QStringList(tr("政治面貌")));
	//	m_WorkInfo = new QTreeWidgetItem(QStringList(tr("工作信息")));
	//	m_PersonalExperience = new QTreeWidgetItem(QStringList(tr("个人经历")));
	//	m_Remark = new QTreeWidgetItem(QStringList(tr("备注")));

	//	m_AddTeacherInfo->addChild(m_PersonalInfo);
	//	m_AddTeacherInfo->addChild(m_PoliticalInfo);
	//	m_AddTeacherInfo->addChild(m_WorkInfo);
	//	m_AddTeacherInfo->addChild(m_PersonalExperience);
	//	m_AddTeacherInfo->addChild(m_Remark);

	m_InfoQuery = new QTreeWidgetItem(QStringList(tr("信息查询")),m_InfoQueryType);
	m_InfoQuery->setFont(0,QFont(tr("Times"), 11));
	m_InfoQuery->setIcon(0,QIcon(":/image/tree_node.gif"));

	m_InfoManage->addChild(m_AddTeacherInfo);
	m_InfoManage->addChild(m_InfoQuery);

	m_FunctionTree->insertTopLevelItem(0,m_SystemManage);
	m_FunctionTree->insertTopLevelItem(1,m_InfoManage);

	m_DialogFactory = DialogFactory::instance();
	m_DialogFactory->setContentsMargins(0,0,0,0);

	m_HSplitter->addWidget(m_FunctionTree);
	m_HSplitter->addWidget(m_DialogFactory);
	m_HSplitter->setContentsMargins(0,0,0,0);

	m_TrayIcon = new QSystemTrayIcon(QIcon(":/image/tray.ico"), this);
	m_TrayIcon->show();
	connect(m_TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this, SLOT(onTrayIconActived(QSystemTrayIcon::ActivationReason)) );

	QMenu* trayIconMenu = new QMenu(this);

	QAction* showWindowsAction = new QAction(tr("显示主窗口"), trayIconMenu);
	QAction* exitAction = new QAction(tr("退出"), trayIconMenu);
	connect(showWindowsAction, SIGNAL(triggered()), this, SLOT(showNormal()));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

	trayIconMenu->addAction(showWindowsAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(exitAction);
	m_TrayIcon->setContextMenu(trayIconMenu);

	m_TimeLabel = new TimeLabel(this);
	QWidget *empty = new QWidget;
	statusBar()->addWidget(empty,1);
	statusBar()->addWidget(m_TimeLabel);
}

void MainWindow::setupSignals()
{
	connect(m_FunctionTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
			this,SLOT(onFunctionTreeItemClick(QTreeWidgetItem*,int)));

	connect(ui->m_Exit,SIGNAL(triggered()),this,SLOT(exit()));

	connect(ui->m_AddAction,SIGNAL(triggered()),this,SLOT(onAddAction()));
	connect(ui->m_QueryAction,SIGNAL(triggered()),this,SLOT(onQueryAction()));
	connect(ui->m_UserManagement,SIGNAL(triggered()),this,SLOT(onUserManage()));
	connect(ui->m_About,SIGNAL(triggered()),this,SLOT(onAbout()));

	connect(m_FunctionTree,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(setOpenIcon(QTreeWidgetItem*)));
	connect(m_FunctionTree,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(setClosedIcon(QTreeWidgetItem*)));
}

void MainWindow::onFunctionTreeItemClick(QTreeWidgetItem *treeWidgetItem,int)
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	if(treeWidgetItem->type() == m_UserManagementType)
		m_ChildDialogBase = new UserManagementDialog();

	else if(treeWidgetItem->type() == m_AddTeacherInfoType)
		m_ChildDialogBase = new AddTeacherInfoDialog();

	else if(treeWidgetItem->type() == m_InfoQueryType)
		m_ChildDialogBase = new InfoQueryDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);

}


void MainWindow::exit()
{
	QApplication::exit(0);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if(m_TrayIcon->isVisible())
	{
		hide();
		m_TrayIcon->showMessage("", tr("系统已经最小化到托盘当中"));
		event->ignore();
	}
}

void MainWindow::onTrayIconActived(QSystemTrayIcon::ActivationReason activationReason)
{
	if(activationReason == QSystemTrayIcon::DoubleClick)
		showNormal();
}

void MainWindow::onAddAction()
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	m_ChildDialogBase = new AddTeacherInfoDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);

}

void MainWindow::onQueryAction()
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	m_ChildDialogBase = new InfoQueryDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);
}

void MainWindow::onUserManage()
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	m_ChildDialogBase = new UserManagementDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);

}

void MainWindow::onAbout()
{
	QMessageBox::information(this,tr("关于生命科学学院教职工信息管理系统"),tr("    生命科学学院教职工信息管理系统    "));
}

void  MainWindow::setOpenIcon(QTreeWidgetItem *treeWidgetItem)
{
	treeWidgetItem->setIcon(0,QIcon(":/image/folder_open.gif"));
}

void  MainWindow::setClosedIcon(QTreeWidgetItem *treeWidgetItem)
{
	treeWidgetItem->setIcon(0,QIcon(":/image/folder_closed.gif"));
}
