#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include "datacenter.h"

class DataCenter;

class AccountManage : public QObject
{
	friend class DataCenter;
private:
	int m_UserName;
	int  m_PasswordHash;

	AccountManage(const DataCenter &dataCenter);
	int  hash(const QString& key);
	void createTable();
	bool fetchDataFromDB();
	void initializeTable();
	//QSqlDatabase m_Database;

public:
	bool authentication(const QString& userName,const QString& password);
	bool setPassword(const QString& password);

};

#endif // ACCOUNTMANAGE_H
