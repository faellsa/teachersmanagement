#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include <QSqlDatabase>


class DatabaseException
{
public:
	DatabaseException(const QString& errorMsg, const QSqlDatabase& dataBase);
	const QSqlDatabase* getDatabase() const {return m_Database;}
	virtual QString errorMsg() const { return m_ErrorMsg;}

private:
	const QSqlDatabase* m_Database;
	QString m_ErrorMsg;
};


#endif // DATABASEEXCEPTION_H
