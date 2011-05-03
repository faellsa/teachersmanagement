#-------------------------------------------------
#
# Project created by QtCreator 2011-04-20T21:57:58
#
#-------------------------------------------------

QT       += core gui\
			sql

TARGET = TeachersManagement
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    childdialogbase.cpp \
    dialogfactory.cpp \
    usermanagementdialog.cpp \
    datacenter.cpp \
    databaseexception.cpp \
    personalinfodialog.cpp \
    addteacherinfodialog.cpp \
    infoquerydialog.cpp \
    teachersinfotable.cpp \
    exportexcelobject.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    childdialogbase.h \
    dialogfactory.h \
    usermanagementdialog.h \
    datacenter.h \
    databaseexception.h \
    personalinfodialog.h \
    addteacherinfodialog.h \
    infoquerydialog.h \
    teachersinfotable.h \
    exportexcelobject.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    usermanagementdialog.ui \
    personalinfodialog.ui \
    addteacherinfodialog.ui \
    infoquerydialog.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    mystyle.qss
