#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T13:36:15
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddBug
TEMPLATE = app


SOURCES += main.cpp\
        addbug.cpp \
    bug.cpp \
    database.cpp \
    user.cpp \
    addbugcontroller.cpp

HEADERS  += addbug.h \
    bug.h \
    database.h \
    user.h \
    addbugcontroller.h

FORMS    += addbug.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../opt/local/lib/mysql55/mysql/release/ -lmysqlclient.18
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../opt/local/lib/mysql55/mysql/debug/ -lmysqlclient.18
else:unix: LIBS += -L$$PWD/../../../../../opt/local/lib/mysql55/mysql/ -lmysqlclient.18

INCLUDEPATH += $$PWD/../../../../../opt/local/lib/mysql55/mysql
DEPENDPATH += $$PWD/../../../../../opt/local/lib/mysql55/mysql
