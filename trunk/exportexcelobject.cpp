#include "exportexcelobject.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QVariant>

int ExportExcelObject::export2Excel()
{
	if(m_FieldList.size() <= 0)
    {
        qDebug() << "ExportExcelObject::export2Excel failed: No fields defined.";
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelexport");
    if(!db.isValid())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
        return -2;
    }
    // set the dsn string
    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
				  arg(m_ExcelFilePath).arg(m_ExcelFilePath);
    db.setDatabaseName(dsn);
    if(!db.open())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
        //QSqlDatabase::removeDatabase("excelexport");
        return -3;
    }

    QSqlQuery query(db);

    //drop the table if it's already exists
	QString s, sSql = QString("DROP TABLE [%1] (").arg(m_SheetName);
    query.exec(sSql);

    //create the table (sheet in Excel file)
	sSql = QString("CREATE TABLE [%1] (").arg(m_SheetName);
	for (int i = 0; i < m_FieldList.size(); i++)
    {
		s = QString("[%1] %2").arg(m_FieldList.at(i)->sFieldName).arg(m_FieldList.at(i)->sFieldType);
        sSql += s;
		if(i < m_FieldList.size() - 1)
            sSql += " , ";
    }

    sSql += ")";
    query.prepare(sSql);

    if(!query.exec())
    {
        qDebug() << "ExportExcelObject::export2Excel failed: Create Excel sheet failed.";
        //db.close();
        //QSqlDatabase::removeDatabase("excelexport");
        return -4;
    }

    //add all rows
	sSql = QString("INSERT INTO [%1] (").arg(m_SheetName);
	for (int i = 0; i < m_FieldList.size(); i++)
    {
		{
			sSql += m_FieldList.at(i)->sFieldName;
			if(i < m_FieldList.size() - 1)
				sSql += " , ";
		}
    }

    sSql += ") VALUES (";
	for (int i = 0; i < m_FieldList.size(); i++)
    {
		{
			sSql += QString(":data%1").arg(i);
			if(i < m_FieldList.size() - 1)
				sSql += " , ";
		}
    }
    sSql += ")";

	int r, iRet = 0;
	int i = 0;
	for(r = 0 ; r < m_TableView->model()->rowCount() ; r++)
	{
		query.prepare(sSql);
		for (int c = 0; c != m_TableView->model()->columnCount(); c++)
		{
			if(m_TableView->isColumnHidden(c) == false)
			{
				query.bindValue(QString(":data%1").arg(i), m_TableView->model()->data(m_TableView->model()->index(r, c)));
				i++;
			}
		}

		if(query.exec())
			iRet++;

		if(r % 10 == 0)
			emit exportedRowCount(r);
	}

    emit exportedRowCount(r);

    return iRet;
}
