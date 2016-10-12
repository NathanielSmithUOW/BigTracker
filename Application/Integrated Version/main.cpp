#include "user.h"
#include "login.h"
#include "addbug.h"
#include "viewbug.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    bool ok = connectToDatabase();
    if(!ok)
    {
        std::cout << "Error connecting to database" << std::endl;
        //return 0;
    }
    QApplication a(argc, argv);
    Login w;
   w.show();

    return a.exec();
}

