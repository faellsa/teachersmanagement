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
	void onPoliticsStatus(QString politicsStatus);
	void onGraduateTrain(QString graduateTrain);
};

#endif // ADDTEACHERINFODIALOG_H
