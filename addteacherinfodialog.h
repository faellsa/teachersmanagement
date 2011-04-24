#ifndef ADDTEACHERINFODIALOG_H
#define ADDTEACHERINFODIALOG_H

#include "childdialogbase.h"

namespace Ui {
    class AddTeacherInfoDialog;
}

class AddTeacherInfoDialog : public ChildDialogBase
{
    Q_OBJECT

public:
	explicit AddTeacherInfoDialog(QDialog *parent = 0);
    ~AddTeacherInfoDialog();

private:
    Ui::AddTeacherInfoDialog *ui;
	void setupSignals();

private slots:
	void showPersonalInfoPage();
	void showPoliticalInfoPage();
	void showWorkInfoPage();
	void showPersonalExperiencePage();
	void showRemarkPage();
};

#endif // ADDTEACHERINFODIALOG_H
