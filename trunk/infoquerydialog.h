#ifndef INFOQUERYDIALOG_H
#define INFOQUERYDIALOG_H

#include "childdialogbase.h"

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

	void setupWidgets();
};

#endif // INFOQUERYDIALOG_H
