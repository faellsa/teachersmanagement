#include "datacenter.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include "databaseexception.h"
#include "teachersinfotable.h"
#include "accountmanage.h"

DataCenter *DataCenter::m_DataCenter = NULL;
TeachersInfoTable *DataCenter::m_TeachersInfoTable = NULL;
AccountManage *DataCenter::m_AccountManage = NULL;

DataCenter::DataCenter(const QString &hostName,int tcpPort,
					   const QString &dbName,
					   const QString &username,
					   const QString& password,
					   const QString& driverType)
						   : m_Database(QSqlDatabase::addDatabase(driverType))
{
	m_Database.setHostName(hostName);
	m_Database.setDatabaseName(dbName);
	m_Database.setPort(tcpPort);
	m_Database.setUserName(username);
	m_Database.setPassword(password);
	if(!m_Database.open())
	{
		qDebug()<<m_Database.lastError();
		throw DatabaseException(m_Database.lastError().text(), m_Database);
	}
}

DataCenter *DataCenter::instance(const QString &hostName,
							int tcpPort,
							const QString &dbName,
							const QString &username,
							const QString &password ,
							const QString &driverType)
{
	if(m_DataCenter == NULL)
		m_DataCenter = new DataCenter(hostName,tcpPort,
									  dbName,username,
									  password,driverType);
		return m_DataCenter;
}

TeachersInfoTable *DataCenter::techersInfoTableInstance()
{
	if(m_TeachersInfoTable == NULL)
		m_TeachersInfoTable = new TeachersInfoTable(*this);

	return m_TeachersInfoTable;
}

AccountManage* DataCenter::accountManageInstance()
{
	if(m_AccountManage == NULL)
		m_AccountManage = new AccountManage(*this);
	return m_AccountManage;
}
