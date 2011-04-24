#include "personalinfodialog.h"
#include "ui_personalinfodialog.h"

PersonalInfoDialog::PersonalInfoDialog(QDialog *parent) :
	ChildDialogBase(parent),
    ui(new Ui::PersonalInfoDialog)
{
    ui->setupUi(this);
}

PersonalInfoDialog::~PersonalInfoDialog()
{
    delete ui;
}
