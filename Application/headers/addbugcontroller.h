#ifndef ADDBUGCONTROLLER_H
#define ADDBUGCONTROLLER_H


#include"database.h"
#include"bug.h"
#include"user.h"
#include"addbug.h"


class addBugController
{

private:
    User reporter;
    Database data;
    Bug newBug;


public:
    addBugController();
    void createBug(QString, QString, QString, double, QString, QString, QString,QString,QString, QString, QString, QString);
    void getBug(QString, QString, QString, double, QString, QString, QString,QString,QString, QString, QString, QString);

    void addBug(Bug&);
};

#endif // ADDBUGCONTROLLER_H
