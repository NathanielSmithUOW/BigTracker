#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T20:34:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app


SOURCES += main.cpp\
    forgetpassword.cpp \
    search.cpp \
    mainwindow.cpp \
    register.cpp \
    database.cpp \
    user.cpp \
    bug.cpp \
    editprofile.cpp \
    searchbug.cpp \
    changepassword.cpp \
    viewprofile.cpp

HEADERS  += mainwindow.h \
    forgetpassword.h \
    search.h \
    register.h \
    database.h \
    user.h \
    bug.h \
    editprofile.h \
    searchbug.h \
    changepassword.h \
    viewprofile.h

FORMS    += mainwindow.ui \
    forgetpassword.ui \
    search.ui \
    register.ui \
    editprofile.ui \
    searchbug.ui \
    changepassword.ui \
    viewprofile.ui

RESOURCES += \
    resource.qrc
