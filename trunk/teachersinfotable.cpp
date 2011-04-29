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
										 "人事号 varchar(8) not null,"
										 "职称职级 varchar(MAX),"
										 "职称职级时间 varchar(MAX),"
										 "任现职时间 varchar(MAX),"
										 "学术兼职情况 varchar(MAX),"
										 "获人才计划情况 varchar(MAX),"
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
