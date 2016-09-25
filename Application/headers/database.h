#ifndef DATABASE_H
#define DATABASE_H

#include <QtSQL>
#include <QSqlDatabase>
#include <QApplication>
#include <iostream>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include "user.h"
#include "bug.h"

/*
// EXAMPLE CODE  //

    // ADD USER
        addNewUser(User("Bob", "Brown", "Bobby", "bobby123@email.com", "bob123", 'M', 0, "Reporter", ""));
    // GET USER
        User *u = getUserFromUsername("Bobby");
    // CHANGE ROLE AND UPDATE
         u->setRole("Triager");
        updateUser(*u);

    // NEW BUG, NEW Bug
        Bug b = Bug("Example Title", "NEW", "PhotoShop", 1.0, "Description here", "Platofrm here", "Component", "HIGH", "MAJOR", "","", "Bobby");
        addNewBug(b);
    // GET BUG
        Bug *nb = getBugFromID(1);
    // CHANGE VALUES AND update
         nb->setAssignedTo("Bobby");
        updateBug(*nb);
    // CHANGE OLDER Bug and add as new one
         nb->setPriority("LOW");
        addNewBug(*nb);
*/

bool connectToDatabase();
void closeDatabase();
bool checkLogin(QVariant, QVariant);
bool checkUserExists(QVariant);

User* getUserFromID(int);
User* getUserFromUsername(QVariant);
User* getUserFromEmail(QVariant);
bool addNewUser(User&);
bool updateUser(User&);

Bug* getBugFromID(int);
bool addNewBug(Bug&);
bool updateBug(Bug&);

QList<User> searchUser(QString, QList<QString>);

#endif // DATABASE_H
