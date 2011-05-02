#ifndef INFOQUERYDIALOG_H
#define INFOQUERYDIALOG_H

#include "childdialogbase.h"
#include <QSqlQueryModel>
#include <QAction>
#include "teachersinfotable.h"

namespace Ui {
    class InfoQueryDialog;
}

class InfoQueryDialog : public ChildDialogBase
{
    Q_OBJECT

public:
	explicit InfoQueryDialog(QDialog *parent = 0);
    ~InfoQueryDialog();

private:
    Ui::InfoQueryDialog *ui;
	QSqlQueryModel* m_Model;

	QAction* m_DeleteAction;
	QAction* m_DetailAction;
	QList <QAction*> m_Actions;

	TeacherInfo *m_TeacherInfo;

	void setupWidgets();
	void setupSignals();
	void setTeachersInfo(TeacherInfo &teacherInfo);

private slots:
	void showConditionWidget(QString conditionType);
	void onQueryButton();
	void onDeleteAction();
	void onDetailAction();
};

#endif // INFOQUERYDIALOG_H
