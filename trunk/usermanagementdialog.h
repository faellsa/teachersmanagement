#ifndef USERMANAGEMENTDIALOG_H
#define USERMANAGEMENTDIALOG_H

#include "childdialogbase.h"

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
};

#endif // USERMANAGEMENTDIALOG_H
