#include "accountmanage.h"
#include "QDebug"

AccountManage::AccountManage(const DataCenter &dataCenter)
{
	createTable();
	initializeTable();
	fetchDataFromDB();

}


bool AccountManage::authentication(const QString& userName,const QString& password)
{
		int userNameHash = 0,passwordHash = 0;
		userNameHash = hash(userName);
		passwordHash = hash(password);
		return (userNameHash == m_UserName)&&(passwordHash == m_PasswordHash);
}

int  AccountManage::hash(const QString& key)
{
	int hashcode = 0;
	int kelength = (int) key.length();
	int COUNT = (kelength >> 2) + ((kelength & 3) ? 1 : 0);
	int data[1024];
	memcpy(((char*) data) + 0, key.toLocal8Bit(), kelength);
	memset(((char*) data) + kelength, kelength, (COUNT << 2) - kelength);
	for (int n = 0; n < COUNT; n++)
	{
		hashcode += (data[n] << n);
	}
	return hashcode;
}

void AccountManage::createTable()
{
	QString createQuery("CREATE TABLE Account("
						"Id int NOT NULL,"
						"Username int NOT NULL,"
						"Password int NOT NULL,"
						"PRIMARY KEY(Id) )");
	QSqlQuery query;
	query.exec(createQuery);
}

void AccountManage::initializeTable()
{
	int password = hash("888888"); //³õÊ¼ÃÜÂë
	int  userName = hash("admin");
	QString insertSql("INSERT INTO Account VALUES(0,%1,%2)");
	insertSql = insertSql.arg(userName).arg(password);
	QSqlQuery query;
	query.exec(insertSql);
}

bool AccountManage::fetchDataFromDB()
{
	int  userName = hash("admin");
	QString selectQuery("SELECT * FROM Account WHERE Username = %1 ");
	selectQuery = selectQuery.arg(userName);
	QSqlQuery query;
	if(!query.exec(selectQuery))
	{
		return false;
	}
	if(!query.next())
	{
		return false;
	}
	QSqlRecord record = query.record();
	m_UserName = record.value("Username").toInt();
	m_PasswordHash = record.value("Password").toInt();

	return true;
}

bool AccountManage::setPassword(const QString& password)
{
	const int  passwordHash = hash(password);

	QString updateSql("Update ACCOUNT SET Password = %1");
	updateSql = updateSql.arg(passwordHash);

	QSqlQuery query;
	if(query.exec(updateSql))
	{
		m_PasswordHash = passwordHash;
		return true;
	}
	return false;
}
