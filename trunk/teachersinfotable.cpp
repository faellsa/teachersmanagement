#include "teachersinfotable.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "datacenter.h"
#include <QDebug>
#include <QVector>
#include <QVariant>

TeachersInfoTable::TeachersInfoTable(const DataCenter& dataCenter)
	:m_Database(dataCenter.getDatabase())
{
	createTable();
}


void TeachersInfoTable::createTable()
{
	QSqlQuery query(m_Database);
	QString createTableSql = QObject::tr("CREATE TABLE TeachersInfo("
										 "���º� varchar(8) not null,"
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
										 "ְ�� varchar(MAX),"
										 "ְ�ƽ���ʱ�� varchar(MAX),"
										 "ְ�� varchar(MAX),"
										 //"ְ������ʱ�� varchar(MAX),"
										 "����ְʱ�� varchar(MAX),"
										 "ѧ����ְ��� varchar(MAX),"
										 "���˲żƻ���� varchar(MAX),"
										 "�����ƺ� varchar(MAX),"
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
								"'%29','%30','%31','%32','%33')")
			.arg(teacherInfo.personnelNo)
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
			.arg(teacherInfo.title)
			.arg(teacherInfo.titleTime)
			.arg(teacherInfo.rank)
			//.arg(teacherInfo.rankTime)
			.arg(teacherInfo.currentPositionTime)
			.arg(teacherInfo.academicParttime)
			.arg(teacherInfo.personnelPlan)
			.arg(teacherInfo.honour)
			.arg(teacherInfo.administrationParttime)
			.arg(teacherInfo.otherParttime)
			.arg(teacherInfo.graduateTrain)
			.arg(teacherInfo.teacherTime)
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

bool TeachersInfoTable::queryTeacherInfo(QString conditionType, QString conditionValue, QVector<TeacherInfo *> &teacherInfoList)
{
	QString querySql = "SELECT * from TeachersInfo WHERE " + conditionType + " = '" + conditionValue + "'";

	QSqlQuery sqlQuery;
	if(!sqlQuery.exec(querySql))
	{
		qDebug()<<"Query failed : "<<m_Database.lastError();
		return false;
	}

	while(sqlQuery.next())
	{
		QSqlRecord record = sqlQuery.record();

		TeacherInfo *teacherInfo = new TeacherInfo;

		teacherInfo->name = record.value(QObject::tr("����")).toString();
		teacherInfo->sex = record.value(QObject::tr("�Ա�")).toString();
		teacherInfo->nationality = record.value(QObject::tr("����")).toString();
		teacherInfo->origin = record.value(QObject::tr("����")).toString();
		teacherInfo->id = record.value(QObject::tr("���֤��")).toString();
		teacherInfo->birthday = record.value(QObject::tr("��������")).toString();
		teacherInfo->politicsStatus = record.value(QObject::tr("������ò")).toString();
		teacherInfo->partyTime = record.value(QObject::tr("�뵳ʱ��")).toString();
		teacherInfo->department = record.value(QObject::tr("����רҵ")).toString();
		teacherInfo->category = record.value(QObject::tr("���")).toString();
		teacherInfo->personnelNo = record.value(QObject::tr("���º�")).toString();
		teacherInfo->title = record.value(QObject::tr("ְ��")).toString();
		teacherInfo->titleTime = record.value(QObject::tr("ְ��ʱ��")).toString();
		teacherInfo->rank = record.value(QObject::tr("ְ��")).toString();
		//teacherInfo->rankTime = record.value(QObject::tr("ְ��ʱ��")).toString();
		teacherInfo->currentPositionTime = record.value(QObject::tr("����ְʱ��")).toString();
		teacherInfo->academicParttime = record.value(QObject::tr("ѧ����ְ���")).toString();
		teacherInfo->personnelPlan = record.value(QObject::tr("���˲żƻ����")).toString();
		teacherInfo->honour = record.value(QObject::tr("�����ƺ�")).toString();
		teacherInfo->administrationParttime = record.value(QObject::tr("������ְ")).toString();
		teacherInfo->otherParttime = record.value(QObject::tr("������ְ")).toString();
		teacherInfo->graduateTrain = record.value(QObject::tr("�о�������")).toString();
		teacherInfo->teacherTime = record.value(QObject::tr("�β���ʱ��")).toString();
		teacherInfo->bachelorTime = record.value(QObject::tr("ѧʿѧλȡ��ʱ��")).toString();
		teacherInfo->masterTime = record.value(QObject::tr("˶ʿѧλȡ��ʱ��")).toString();
		teacherInfo->doctorTime = record.value(QObject::tr("��ʿѧλȡ��ʱ��")).toString();
		teacherInfo->firstWorkTime = record.value(QObject::tr("�������ʱ��")).toString();
		teacherInfo->firstWorkPlace = record.value(QObject::tr("���������λ")).toString();
		teacherInfo->whuTime = record.value(QObject::tr("����Ժʱ��")).toString();
		teacherInfo->beAbroadExperience = record.value(QObject::tr("�������ع����")).toString();
		teacherInfo->retirementTime = record.value(QObject::tr("����ʱ��")).toString();
		teacherInfo->email = record.value(QObject::tr("��������")).toString();
		teacherInfo->officePhone = record.value(QObject::tr("�칫�绰")).toString();
		teacherInfo->mobilePhone = record.value(QObject::tr("�ƶ��绰")).toString();

		teacherInfoList.push_back(teacherInfo);
	}

	return true;
}

bool TeachersInfoTable::deleteTeacherInfo(QString conditionType, QString conditionValue)
{
	QString deleteSql = "DELETE FROM TeachersInfo WHERE " + conditionType + " = '" + conditionValue + "'";

	QSqlQuery sqlQuery(m_Database);
	if(!sqlQuery.exec(deleteSql))
	{
		qDebug()<<m_Database.lastError();
		return false;
	}
	return true;
}
