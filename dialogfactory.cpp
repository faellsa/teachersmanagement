#include "dialogfactory.h"

DialogFactory *DialogFactory::m_DialogFactory = NULL;

DialogFactory::DialogFactory(QWidget *parent) :
	QFrame(parent)
	,m_MainLayout(new QHBoxLayout)
	,m_ChildDialog(new ChildDialogBase)
{
	setLayout(m_MainLayout);
	setContentsMargins(0,0,0,0);
	m_MainLayout->setContentsMargins(0,0,0,0);
}

DialogFactory* DialogFactory::instance()
{
	if(m_DialogFactory == NULL)
		m_DialogFactory = new DialogFactory;
	return m_DialogFactory;
}

void DialogFactory::updateDialog(ChildDialogBase *childDialog)
{
	delete m_ChildDialog;
	m_MainLayout->addWidget(childDialog);
	m_ChildDialog = childDialog;
}

