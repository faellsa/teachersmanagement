#include "timelabel.h"

#include <QTime>
#include <QDate>

TimeLabel::TimeLabel(QWidget* parent)
	: QLabel(parent)
{
	setDayOfTime();
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
	m_Timer.setInterval(1000);
	m_Timer.start();
}

void TimeLabel::timeUpdate()
{
	setText( QDate::currentDate().toString("yyyy.MM.dd ") + tr("星期") + m_DayofTime +
			 " " + QTime::currentTime().toString() );
}

void TimeLabel::setDayOfTime()
{
	QDate date = QDate::currentDate();
	int dayofTime = date.dayOfWeek();
	switch(dayofTime)
	{
	case 1:
		m_DayofTime = tr("一");
		break;
	case 2:
		m_DayofTime = tr("二");
		break;
	case 3:
		m_DayofTime = tr("三");
		break;
	case 4:
		m_DayofTime = tr("四");
		break;
	case 5:
		m_DayofTime = tr("五");
		break;
	case 6:
		m_DayofTime = tr("六");
		break;
	case 7:
		m_DayofTime = tr("天");
		break;
	}
}
