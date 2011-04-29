#include "teachersinfotable.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "datacenter.h"
#include <QDebug>

TeachersInfoTable::TeachersInfoTable(const DataCenter& dataCenter)
	:m_Database(dataCenter.getDatabase())
{
	createTable();
}


void TeachersInfoTable::createTable()
{
	QSqlQuery query(m_Database);
	QString createTableSql = QObject::tr("CREATE TABLE TeachersInfo("
										 "���� varchar(MAX),"
										 "�Ա� varchar(MAX),"
										 "���� varchar(MAX),"
										 "���� varchar(MAX),"
										 "���֤�� varchar(MAX),"
										 "�������� varchar(MAX),"
										 "������ò varchar(MAX),"
										 "�뵳ʱ�� varchar(MAX),"
										 "����רҵ varchar(MAX),"
										 "��� varchar(MAX),"
										 "���º� varchar(8) not null,"
										 "ְ��ְ�� varchar(MAX),"
										 "ְ��ְ��ʱ�� varchar(MAX),"
										 "����ְʱ�� varchar(MAX),"
										 "ѧ����ְ��� varchar(MAX),"
										 "���˲żƻ���� varchar(MAX),"
										 "������ְ varchar(MAX),"
										 "������ְ varchar(MAX),"
										 "�о������� varchar(MAX),"
										 "�β���ʱ�� varchar(MAX),"
										 "ѧʿѧλȡ��ʱ�� varchar(MAX),"
										 "˶ʿѧλȡ��ʱ�� varchar(MAX),"
										 "��ʿѧλȡ��ʱ�� varchar(MAX),"
										 "�������ʱ�� varchar(MAX),"
										 "���������λ varchar(MAX),"
										 "����Ժʱ�� varchar(MAX),"
										 "�������ع���� varchar(MAX),"
										 "����ʱ�� varchar(MAX),"
										 "�������� varchar(MAX),"
										 "�칫�绰 varchar(MAX),"
										 "�ƶ��绰 varchar(MAX),"
										 "PRIMARY KEY(���º�))");
	if(!query.exec(createTableSql))
	{
		qDebug()<<"create failed.";
	}
}

bool TeachersInfoTable::newTeacherInfo(const TeacherInfo &teacherInfo)
{
	QString insertSql = QString("INSERT INTO TeachersInfo VALUES("
								"'%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',"
								"'%11','%12','%13','%14','%15','%16','%17','%18','%19',"
								"'%20','%21','%22','%23','%24','%25','%26','%27','%28',"
								"'%29','%30','%31')")
			.arg(teacherInfo.name)
			.arg(teacherInfo.name)
			.arg(teacherInfo.sex)
			.arg(teacherInfo.nationality)
			.arg(teacherInfo.origin)
			.arg(teacherInfo.id)
			.arg(teacherInfo.birthday)
			.arg(teacherInfo.politicsStatus)
			.arg(teacherInfo.partyTime)
			.arg(teacherInfo.department)
			.arg(teacherInfo.category)
			.arg(teacherInfo.personnelNo)
			.arg(teacherInfo.titleAndRank)
			.arg(teacherInfo.titleTime)
			.arg(teacherInfo.currentPositionTime)
			.arg(teacherInfo.academicParttime)
			.arg(teacherInfo.personnelPlan)
			.arg(teacherInfo.administrationParttime)
			.arg(teacherInfo.otherParttime)
			.arg(teacherInfo.graduateTrain)
			.arg(teacherInfo.bachelorTime)
			.arg(teacherInfo.masterTime)
			.arg(teacherInfo.doctorTime)
			.arg(teacherInfo.firstWorkTime)
			.arg(teacherInfo.firstWorkPlace)
			.arg(teacherInfo.whuTime)
			.arg(teacherInfo.beAbroadExperience)
			.arg(teacherInfo.retirementTime)
			.arg(teacherInfo.email)
			.arg(teacherInfo.officePhone)
			.arg(teacherInfo.mobilePhone);


	QSqlQuery sqlQuery(m_Database);
	if(!sqlQuery.exec(insertSql))
	{
		qDebug()<<m_Database.lastError();
		return false;
	}
	return true;
}
