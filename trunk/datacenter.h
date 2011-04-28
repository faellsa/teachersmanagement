#ifndef DATACENTER_H
#define DATACENTER_H

#include <QString>
#include <QSqlDatabase>
#include <QObject>

class TeachersInfoTable;

class DataCenter
{
public:
	static DataCenter *instance(const QString &hostName = "127.0.0.1",
								int tcpPort = 1433,
								const QString &dbName = "TeachersManagement",
								const QString &username = "TeachersMagement",
								const QString &password = "123456",
								const QString &driverType = "QODBC");
	TeachersInfoTable *techersInfoTableInstance();

	QSqlDatabase getDatabase() const
	{
		return m_Database;
	}

private:
	/*
	  DataCenter：构造函数
		hostName:数据库的Ip或者域名
		tcpPort:数据库的TCP端口
		dbName:数据库名
		username:用户名
		password:密码
		driverType:使用哪种数据库driver
		throws:如果数据库连接失败，抛出DatabaseExcetion
	  */
	DataCenter(const QString &hostName,int tcpPort,
			   const QString &dbName,
			   const QString &username,
			   const QString& password,
			   const QString& driverType = "QODBC");

	/*
	  isOpen:测试数据库是否正常打开
		  return:如果打开返回true,否则返回false
	  */
	bool isOpen() const
	{
		return m_Database.isOpen();
	}

	QSqlDatabase m_Database;
	static DataCenter *m_DataCenter;
	static TeachersInfoTable *m_TeachersInfoTable;

};

#endif // DATACENTER_H
