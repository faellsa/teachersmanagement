#-------------------------------------------------
#
# Project created by QtCreator 2011-04-20T21:57:58
#
#-------------------------------------------------

QT       += core gui

TARGET = TeachersManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    childdialogbase.cpp \
    dialogfactory.cpp \
    usermanagementdialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    childdialogbase.h \
    dialogfactory.h \
    usermanagementdialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    usermanagementdialog.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    mystyle.qss
