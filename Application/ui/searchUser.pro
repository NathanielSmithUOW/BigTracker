#-------------------------------------------------
#
# Project created by QtCreator 2016-10-14T21:58:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = s
TEMPLATE = app


SOURCES += main.cpp\
        searchUser.cpp \
    database.cpp \
    searchUser.cpp

HEADERS  += searchUser.h \
    database.h \
    bug.h \
    user.h

FORMS    += searchUser.ui
