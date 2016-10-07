#-------------------------------------------------
#
# Project created by QtCreator 2016-10-06T10:04:11
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewBug
TEMPLATE = app


SOURCES += main.cpp\
        viewbug.cpp \
    viewbugcontroller.cpp \
    users.cpp \
    bug.cpp \
    database.cpp

HEADERS  += viewbug.h \
    viewbugcontroller.h \
    users.h \
    bug.h \
    database.h

FORMS    += viewbug.ui
