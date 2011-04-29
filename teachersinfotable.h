#ifndef TEACHERSINFOTABLE_H
#define TEACHERSINFOTABLE_H

#include <QSqlDatabase>

class DataCenter;

struct TeacherInfo
{
	QString name;
	QString sex;
	QString nationality;
	QString origin;
	QString id;
	QString birthday;
	QString politicsStatus;
	QString partyTime;
	QString department;
	QString category;
	QString personnelNo;
	QString titleAndRank;
	QString titleTime;
	QString currentPositionTime;
	QString academicParttime;
	QString personnelPlan;
	QString administrationParttime;
	QString otherParttime;
	QString graduateTrain;
	QString teacherTime;
	QString bachelorTime;
	QString masterTime;
	QString doctorTime;
	QString firstWorkTime;
	QString firstWorkPlace;
	QString whuTime;
	QString beAbroadExperience;
	QString retirementTime;
	QString email;
	QString officePhone;
	QString mobilePhone;
};

class TeachersInfoTable
{
public:
	TeachersInfoTable(const DataCenter& dataCenter);

private:
	void createTable();
	bool newTeacherInfo(const TeacherInfo &teacherInfo);
	QSqlDatabase m_Database;
};

#endif // TEACHERSINFOTABLE_H
