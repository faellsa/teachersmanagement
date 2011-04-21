#ifndef CHILDDIALOGBASE_H
#define CHILDDIALOGBASE_H

#include <QDialog>

class ChildDialogBase : public QDialog
{
public:
	explicit ChildDialogBase(QDialog *parent = 0);
	virtual ~ChildDialogBase(){}

};

#endif // CHILDDIALOGBASE_H
