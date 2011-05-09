/*
  author:DH,2010.3.17,email:xtlz10629@gmail.com
	  ��̬��ʾ��ǰʱ���һ��Label��ʱ����ʽΪ��2010.3.17 20:17:12
	  history:
  */

#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QLabel>
#include <QTimer>
#include <QString>


class TimeLabel : public QLabel
{
	Q_OBJECT
public:
	TimeLabel(QWidget* parent = NULL);
private slots:
	void timeUpdate();
private:
	QTimer m_Timer;
	void setDayOfTime();
	QString m_DayofTime;
};

#endif // TIMELABEL_H
