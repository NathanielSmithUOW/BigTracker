#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T14:59:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BugTracker
TEMPLATE = app
RC_FILE = bugtracker.rc

SOURCES += main.cpp\
        database.cpp \
        user.cpp \
        bug.cpp \
        mainwindow.cpp \
        login.cpp \
        changepassword.cpp \
        forgetpassword.cpp \
        register.cpp \
        addbug.cpp \
        viewbug.cpp \
        editprofile.cpp \
        searchUser.cpp \
    report.cpp

HEADERS  += \
        database.h \
        user.h \
        bug.h \
        mainwindow.h \
        login.h \
        changepassword.h \
        forgetpassword.h \
        register.h \
        addbug.h \
        viewbug.h \
        editprofile.h \
        searchUser.h \
    report.h

FORMS    += \
    mainwindow.ui \
    login.ui \
    changepassword.ui \
    forgetpassword.ui \
    register.ui \
    addbug.ui \
    viewbug.ui \
    editprofile.ui \
    searchUser.ui \
    report.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysql
else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysql

INCLUDEPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/include'
DEPENDPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/include'

RESOURCES += \
    resources.qrc

SUBDIRS += \
    ../../Desktop/qftp/qftp.pro

DISTFILES += \
    ReadMe.txt \
    DropTable.sql \
    UserTable.sql

CONFIG += static
CONFIG += c++11
static {

    CONFIG += static
    QTPLUGIN += qsqlmysql
    DEFINES += STATIC
    message("Static build.")
}
