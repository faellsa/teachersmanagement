#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QScrollArea>
#include "dialogfactory.h"
#include "datacenter.h"
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	QSplitter *m_HSplitter;
	DialogFactory *m_DialogFactory;

	QTreeWidget *m_FunctionTree;
	QTreeWidgetItem *m_SystemManage;
	QTreeWidgetItem *m_InfoManage;

	QTreeWidgetItem *m_UserManagement;
	QTreeWidgetItem *m_AddTeacherInfo;
	QTreeWidgetItem *m_InfoQuery;

//	QTreeWidgetItem *m_PersonalInfo;
//	QTreeWidgetItem *m_PoliticalInfo;
//	QTreeWidgetItem *m_WorkInfo;
//	QTreeWidgetItem *m_PersonalExperience;
//	QTreeWidgetItem *m_Remark;

	void setupWidgets();
	void setupSignals();

	ChildDialogBase *m_ChildDialogBase;

	const static int m_UserManagementType = 1001;
	const static int m_AddTeacherInfoType = 1002;
	const static int m_InfoQueryType = 1003;

	DataCenter *m_DataCenter;

	QSystemTrayIcon *m_TrayIcon;

private slots:
	void onFunctionTreeItemClick(QTreeWidgetItem *treeWidgetItem,int);
	void exit();
	void onTrayIconActived(QSystemTrayIcon::ActivationReason activationReason);

protected:
	void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
