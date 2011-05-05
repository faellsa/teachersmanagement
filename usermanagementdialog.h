#ifndef USERMANAGEMENTDIALOG_H
#define USERMANAGEMENTDIALOG_H

#include "childdialogbase.h"
#include "datacenter.h"

namespace Ui {
    class UserManagementDialog;
}

class UserManagementDialog : public ChildDialogBase
{
    Q_OBJECT

public:
	explicit UserManagementDialog(QDialog *parent = 0);
    ~UserManagementDialog();

private:
    Ui::UserManagementDialog *ui;
	void setupSignals();
	DataCenter *m_DataCenter;
	AccountManage* m_accountManage;

private slots:
	void onOkForModify();
	void onCancel();
	void clearEdit();
};

#endif // USERMANAGEMENTDIALOG_H
