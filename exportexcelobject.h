// Copyright (c) 2010 Joel Gao <joel_gao@sina.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////

#ifndef EXPORTEXCELOBJECT_H
#define EXPORTEXCELOBJECT_H

#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>

class EEO_Field
{
public:
    EEO_Field(const int ic, const QString &sf, const QString &st):
            iCol(ic),sFieldName(sf),sFieldType(st){};

    int     iCol;
    QString sFieldName;
    QString sFieldType;
};

class ExportExcelObject : public QObject
{
    Q_OBJECT
public:
    ExportExcelObject(const QString &filepath, const QString &sheettitle,
					  QTableView *tableview):m_ExcelFilePath(filepath),
					  m_SheetName(sheettitle), m_TableView(tableview){};

    ~ExportExcelObject() {QSqlDatabase::removeDatabase("excelexport");};

public:
	void setOutputFilePath(const QString &spath) {m_ExcelFilePath = spath;};
	void setOutputSheetTitle(const QString &ssheet) {m_SheetName = ssheet;};
	void setTableView(QTableView *tableview) {m_TableView = tableview;};

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)
		 {m_FieldList << new EEO_Field(iCol, fieldname, fieldtype);};

    void removeAllFields()
		 {while (!m_FieldList.isEmpty()) delete m_FieldList.takeFirst();};

    int export2Excel();

signals:
    void exportedRowCount(int row);

private:
	QString m_ExcelFilePath;
	QString m_SheetName;
	QTableView *m_TableView;
	QList<EEO_Field *> m_FieldList;
};

#endif // EXPORTEXCELOBJECT_H
