#ifndef PERSONALINFODIALOG_H
#define PERSONALINFODIALOG_H

#include "childdialogbase.h"

namespace Ui {
    class PersonalInfoDialog;
}

class PersonalInfoDialog : public ChildDialogBase
{
    Q_OBJECT

public:
	explicit PersonalInfoDialog(QDialog *parent = 0);
    ~PersonalInfoDialog();

private:
    Ui::PersonalInfoDialog *ui;
};

#endif // PERSONALINFODIALOG_H
