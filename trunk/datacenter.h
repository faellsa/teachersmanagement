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
	  DataCenter�����캯��
		hostName:���ݿ��Ip��������
		tcpPort:���ݿ��TCP�˿�
		dbName:���ݿ���
		username:�û���
		password:����
		driverType:ʹ���������ݿ�driver
		throws:������ݿ�����ʧ�ܣ��׳�DatabaseExcetion
	  */
	DataCenter(const QString &hostName,int tcpPort,
			   const QString &dbName,
			   const QString &username,
			   const QString& password,
			   const QString& driverType = "QODBC");

	/*
	  isOpen:�������ݿ��Ƿ�������
		  return:����򿪷���true,���򷵻�false
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
