#include "usermanagementdialog.h"
#include "ui_usermanagementdialog.h"

UserManagementDialog::UserManagementDialog(QDialog *parent) :
	ChildDialogBase(parent),
    ui(new Ui::UserManagementDialog)
{
    ui->setupUi(this);
}

UserManagementDialog::~UserManagementDialog()
{
    delete ui;
}
