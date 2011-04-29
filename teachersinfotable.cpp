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
										 "姓名 varchar(MAX) not null,"
										 "性别 varchar(MAX) not null,"
										 "民族 varchar(MAX) not null,"
										 "籍贯 varchar(MAX) not null,"
										 "身份证号 varchar(MAX) not null,"
										 "出生年月 varchar(MAX) not null,"
										 "政治面貌 varchar(MAX) not null,"
										 "入党时间 varchar(MAX) not null,"
										 "所在专业 varchar(MAX) not null,"
										 "类别 varchar(MAX) not null,"
										 "人事号 varchar(8) not null,"
										 "职称职级 varchar(MAX) not null,"
										 "职称职级时间 varchar(MAX) not null,"
										 "任现职时间 varchar(MAX) not null,"
										 "学术兼职情况 varchar(MAX) not null,"
										 "获人才计划情况 varchar(MAX) not null,"
										 "行政兼职 varchar(MAX) not null,"
										 "其他兼职 varchar(MAX) not null,"
										 "研究生培养 varchar(MAX) not null,"
										 "任博导时间 varchar(MAX) not null,"
										 "学士学位取得时间 varchar(MAX) not null,"
										 "硕士学位取得时间 varchar(MAX) not null,"
										 "博士学位取得时间 varchar(MAX) not null,"
										 "最初工作时间 varchar(MAX) not null,"
										 "最初工作单位 varchar(MAX) not null,"
										 "到本院时间 varchar(MAX) not null,"
										 "出国及回国情况 varchar(MAX) not null,"
										 "退休时间 varchar(MAX) not null,"
										 "电子邮箱 varchar(MAX) not null,"
										 "办公电话 varchar(MAX) not null,"
										 "移动电话 varchar(MAX) not null,"
										 "PRIMARY KEY(人事号))");
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
