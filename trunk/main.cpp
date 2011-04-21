#include <QtGui/QApplication>
#include "logindialog.h"
#include "QTextCodec"
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(   QTextCodec::codecForName("GB2312")   );

    QApplication a(argc, argv);
	LoginDialog loginDialog;
	loginDialog.show();

	QFile myfile(":/mystyle.qss");
	if(myfile.open(QFile::ReadOnly))
		qDebug()<<"right";
	a.setStyleSheet(myfile.readAll());
    return a.exec();
}
