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
										 "人事号 varchar(8) not null,"
										 "姓名 varchar(MAX),"
										 "性别 varchar(MAX),"
										 "民族 varchar(MAX),"
										 "籍贯 varchar(MAX),"
										 "身份证号 varchar(MAX),"
										 "出生年月 varchar(MAX),"
										 "政治面貌 varchar(MAX),"
										 "入党时间 varchar(MAX),"
										 "所在专业 varchar(MAX),"
										 "类别 varchar(MAX),"										 
										 "职称 varchar(MAX),"
										 "职称晋升时间 varchar(MAX),"
										 "职级 varchar(MAX),"
										 //"职级晋升时间 varchar(MAX),"
										 "任现职时间 varchar(MAX),"
										 "学术兼职情况 varchar(MAX),"
										 "获人才计划情况 varchar(MAX),"
										 "荣誉称号 varchar(MAX),"
										 "行政兼职 varchar(MAX),"
										 "其他兼职 varchar(MAX),"
										 "研究生培养 varchar(MAX),"
										 "任博导时间 varchar(MAX),"
										 "学士学位取得时间 varchar(MAX),"
										 "硕士学位取得时间 varchar(MAX),"
										 "博士学位取得时间 varchar(MAX),"
										 "最初工作时间 varchar(MAX),"
										 "最初工作单位 varchar(MAX),"
										 "到本院时间 varchar(MAX),"
										 "出国及回国情况 varchar(MAX),"
										 "退休时间 varchar(MAX),"
										 "电子邮箱 varchar(MAX),"
										 "办公电话 varchar(MAX),"
										 "移动电话 varchar(MAX),"
										 "PRIMARY KEY(人事号))");
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

		teacherInfo->name = record.value(QObject::tr("姓名")).toString();
		teacherInfo->sex = record.value(QObject::tr("性别")).toString();
		teacherInfo->nationality = record.value(QObject::tr("民族")).toString();
		teacherInfo->origin = record.value(QObject::tr("籍贯")).toString();
		teacherInfo->id = record.value(QObject::tr("身份证号")).toString();
		teacherInfo->birthday = record.value(QObject::tr("出生年月")).toString();
		teacherInfo->politicsStatus = record.value(QObject::tr("政治面貌")).toString();
		teacherInfo->partyTime = record.value(QObject::tr("入党时间")).toString();
		teacherInfo->department = record.value(QObject::tr("所在专业")).toString();
		teacherInfo->category = record.value(QObject::tr("类别")).toString();
		teacherInfo->personnelNo = record.value(QObject::tr("人事号")).toString();
		teacherInfo->title = record.value(QObject::tr("职称")).toString();
		teacherInfo->titleTime = record.value(QObject::tr("职称时间")).toString();
		teacherInfo->rank = record.value(QObject::tr("职级")).toString();
		//teacherInfo->rankTime = record.value(QObject::tr("职级时间")).toString();
		teacherInfo->currentPositionTime = record.value(QObject::tr("任现职时间")).toString();
		teacherInfo->academicParttime = record.value(QObject::tr("学术兼职情况")).toString();
		teacherInfo->personnelPlan = record.value(QObject::tr("获人才计划情况")).toString();
		teacherInfo->honour = record.value(QObject::tr("荣誉称号")).toString();
		teacherInfo->administrationParttime = record.value(QObject::tr("行政兼职")).toString();
		teacherInfo->otherParttime = record.value(QObject::tr("其他兼职")).toString();
		teacherInfo->graduateTrain = record.value(QObject::tr("研究生培养")).toString();
		teacherInfo->teacherTime = record.value(QObject::tr("任博导时间")).toString();
		teacherInfo->bachelorTime = record.value(QObject::tr("学士学位取得时间")).toString();
		teacherInfo->masterTime = record.value(QObject::tr("硕士学位取得时间")).toString();
		teacherInfo->doctorTime = record.value(QObject::tr("博士学位取得时间")).toString();
		teacherInfo->firstWorkTime = record.value(QObject::tr("最初工作时间")).toString();
		teacherInfo->firstWorkPlace = record.value(QObject::tr("最初工作单位")).toString();
		teacherInfo->whuTime = record.value(QObject::tr("到本院时间")).toString();
		teacherInfo->beAbroadExperience = record.value(QObject::tr("出国及回国情况")).toString();
		teacherInfo->retirementTime = record.value(QObject::tr("退休时间")).toString();
		teacherInfo->email = record.value(QObject::tr("电子邮箱")).toString();
		teacherInfo->officePhone = record.value(QObject::tr("办公电话")).toString();
		teacherInfo->mobilePhone = record.value(QObject::tr("移动电话")).toString();

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
