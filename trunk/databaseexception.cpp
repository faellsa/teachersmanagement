#include "databaseexception.h"

DatabaseException::DatabaseException(const QString &errorMsg, const QSqlDatabase &dataBase)
	: m_ErrorMsg(errorMsg), m_Database(&dataBase)
{
}
