#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagementdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_ChildDialogBase(NULL)
{
    ui->setupUi(this);
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

	m_HSplitter = new QSplitter(this);
	ui->m_MainLayout->addWidget(m_HSplitter);

	m_FunctionTree = new QTreeWidget(this);
	m_FunctionTree->setMaximumWidth(200);
	m_FunctionTree->setHeaderHidden(true);
	m_FunctionTree->setColumnCount(1);

	m_SystemManage = new QTreeWidgetItem(QStringList(tr("系统管理")));
	m_UserManagement = new QTreeWidgetItem(QStringList(tr("用户账户")), m_UserManagementType);
	m_SystemManage->addChild(m_UserManagement);

	m_InfoManage = new QTreeWidgetItem(QStringList(tr("教师信息管理")));
	m_AddTeacherInfo = new QTreeWidgetItem(QStringList(tr("增加记录")));
	m_DeleteTeacherInfo = new QTreeWidgetItem(QStringList(tr("删除记录")));
	m_ModifyTeacherInfo = new QTreeWidgetItem(QStringList(tr("信息修改")));
	m_InfoManage->addChild(m_AddTeacherInfo);
	m_InfoManage->addChild(m_DeleteTeacherInfo);
	m_InfoManage->addChild(m_ModifyTeacherInfo);

	m_InfoQuery = new QTreeWidgetItem(QStringList(tr("教师信息查询")));
	//m_Unknown = new QTreeWidgetItem(QStringList(tr("未知")));

	m_FunctionTree->insertTopLevelItem(0,m_SystemManage);
	m_FunctionTree->insertTopLevelItem(1,m_InfoManage);
	m_FunctionTree->insertTopLevelItem(2,m_InfoQuery);

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
}

void MainWindow::onFunctionTreeItemClick(QTreeWidgetItem *treeWidgetItem,int)
{
	ChildDialogBase *m_currentChildDialog = m_ChildDialogBase;

	if(treeWidgetItem->type() == m_UserManagementType)
		m_ChildDialogBase = new UserManagementDialog();

	if(m_currentChildDialog != m_ChildDialogBase && m_ChildDialogBase != NULL)
		m_DialogFactory->updateDialog(m_ChildDialogBase);

}
