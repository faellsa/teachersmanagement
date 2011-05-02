#ifndef ADDTEACHERINFODIALOG_H
#define ADDTEACHERINFODIALOG_H

#include "childdialogbase.h"
#include "teachersinfotable.h"

namespace Ui {
    class AddTeacherInfoDialog;
}

class AddTeacherInfoDialog : public ChildDialogBase
{
    Q_OBJECT

public:
	AddTeacherInfoDialog(QDialog *parent = 0);
	~AddTeacherInfoDialog();
	void setOnlyRead();
	void setTeachersInfo(TeacherInfo &teacherInfo);

private:
    Ui::AddTeacherInfoDialog *ui;
	void setupSignals();

private slots:
	void showPersonalInfoPage();
	void showPoliticalInfoPage();
	void showWorkInfoPage();
	void showPersonalExperiencePage();
	void showRemarkPage();
	void saveInfo();
};

#endif // ADDTEACHERINFODIALOG_H
