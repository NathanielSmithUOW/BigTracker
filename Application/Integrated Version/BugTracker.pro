#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T14:59:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BugTracker
TEMPLATE = app


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
    editprofile.cpp

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
        editprofile.h

FORMS    += \
    mainwindow.ui \
    login.ui \
    changepassword.ui \
    forgetpassword.ui \
    register.ui \
    addbug.ui \
    viewbug.ui \
    editprofile.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysqld
else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/lib/' -llibmysql

INCLUDEPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/include'
DEPENDPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server 5.7/include'

RESOURCES += \
    resources.qrc
