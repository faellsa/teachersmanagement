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
										 "���� varchar(MAX) not null,"
										 "�Ա� varchar(MAX) not null,"
										 "���� varchar(MAX) not null,"
										 "���� varchar(MAX) not null,"
										 "���֤�� varchar(MAX) not null,"
										 "�������� varchar(MAX) not null,"
										 "������ò varchar(MAX) not null,"
										 "�뵳ʱ�� varchar(MAX) not null,"
										 "����רҵ varchar(MAX) not null,"
										 "��� varchar(MAX) not null,"
										 "���º� varchar(8) not null,"
										 "ְ��ְ�� varchar(MAX) not null,"
										 "ְ��ְ��ʱ�� varchar(MAX) not null,"
										 "����ְʱ�� varchar(MAX) not null,"
										 "ѧ����ְ��� varchar(MAX) not null,"
										 "���˲żƻ���� varchar(MAX) not null,"
										 "������ְ varchar(MAX) not null,"
										 "������ְ varchar(MAX) not null,"
										 "�о������� varchar(MAX) not null,"
										 "�β���ʱ�� varchar(MAX) not null,"
										 "ѧʿѧλȡ��ʱ�� varchar(MAX) not null,"
										 "˶ʿѧλȡ��ʱ�� varchar(MAX) not null,"
										 "��ʿѧλȡ��ʱ�� varchar(MAX) not null,"
										 "�������ʱ�� varchar(MAX) not null,"
										 "���������λ varchar(MAX) not null,"
										 "����Ժʱ�� varchar(MAX) not null,"
										 "�������ع���� varchar(MAX) not null,"
										 "����ʱ�� varchar(MAX) not null,"
										 "�������� varchar(MAX) not null,"
										 "�칫�绰 varchar(MAX) not null,"
										 "�ƶ��绰 varchar(MAX) not null,"
										 "PRIMARY KEY(���º�))");
	if(!query.exec(createTableSql))
	{
		qDebug()<<"create failed.";
	}
}

bool TeachersInfoTable::newTeacherInfo(const TeacherInfo &teacherInfo)
{
	QString insertSql = "INSERT INTO TeachersInfo VALUES("
			"'%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15',"
			"'%16','%17','%18','%19','%20','%2'1,'%22','%23','%24','%25','%26',"
			"'%27','%28','%29','%30','%31')";

	insertSql.arg(teacherInfo.name)
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
