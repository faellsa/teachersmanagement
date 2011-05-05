#include <QtGui/QApplication>
#include "logindialog.h"
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <QPluginLoader>

int main(int argc, char *argv[])
{
	QApplication::addLibraryPath("./plugins");
	QTextCodec::setCodecForTr(   QTextCodec::codecForName("GB2312")   );

    QApplication a(argc, argv);
	LoginDialog loginDialog;
	loginDialog.show();

	QFile myfile(":/mystyle.qss");
	if(myfile.open(QFile::ReadOnly))
	{
		a.setStyleSheet(myfile.readAll());
	}
    return a.exec();
}
