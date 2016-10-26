#include "user.h"
#include "login.h"
#include "addbug.h"
#include "viewbug.h"
#include <QApplication>
#include <iostream>
#include <QtPlugin>

//Q_IMPORT_PLUGIN(qsqlmysql)

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Login w;
  w.show();


    return a.exec();
}

