#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

#include <QFrame>
#include "childdialogbase.h"
#include "QHBoxLayout"

class DialogFactory : public QFrame
{
    Q_OBJECT	

public:
	static DialogFactory *instance();
	void updateDialog(ChildDialogBase *chileWindow);

private:
	DialogFactory(QWidget *parent = 0);
	QHBoxLayout *m_MainLayout;
	ChildDialogBase *m_ChildDialog;
	static DialogFactory *m_DialogFactory;

signals:

public slots:

};

#endif // DIALOGFACTORY_H
