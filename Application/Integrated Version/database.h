#ifndef DATABASE_H
#define DATABASE_H

#include <QtSQL>
#include <QSqlDatabase>
#include <QApplication>
#include <iostream>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QGroupBox>
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
const int LOAD_BUG_DAYS = 30;


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
Bug* getBugFromTitle(QString);

bool addNewBug(Bug&);
bool updateBug(Bug&);

QList<User> searchUser(QGroupBox, bool);
QList<Bug*> searchBug(QGroupBox*, bool);

QList<QString> getNotifications(User &, bool);
bool addNotificationToUser(User &,QString);

QList<QString> getSubscriptions(User &u);
bool deleteSubscriptions(Bug &b, User &u);

QList<QString> getSubscribers(Bug &b);
bool addSubscriber(Bug &b, User &u);
bool deleteAllSubscribers(Bug &b);

QList<QString> getBugHistory(Bug &b);
bool addBugHistory(Bug &b, QString);

QList<QString> getBugComments(Bug &b);
bool addBugComment(Bug &b, User &u, QString);

QList<QString> getAttachments(Bug &b);
bool addAttachment(Bug &, QString);

QList<QString> getApplications();
bool addApplication(QString, double);
QList<double> getVersions(QString);

QList<QString> getComponents(QString);
bool addComponent(QString, QString);

QList<QString> getPlatforms();
bool addPlatform(QString);

QList<QString> getDevelopers();




#endif // DATABASE_H
