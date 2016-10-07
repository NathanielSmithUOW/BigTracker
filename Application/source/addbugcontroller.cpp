#include "addbugcontroller.h"


addBugController::addBugController()
{

}

//creates a bug and stores it to the database
void addBugController::createBug(QString title, QString status, QString application, double version, QString description, QString platform, QString component, QString priority, QString severity, QString walkthrough, QString history, QString identifiedBy)
{

newBug=Bug(title,status,application,version,description,platform,component,priority,severity,walkthrough,history,identifiedBy);
addBug(newBug);
}

//method to store new bug via database controller class and communicate with user on whether their bug was successfully entered
void addBugController::addBug(Bug& b)
{
    QMessageBox msgBox;

    bool ok = data.connectToDatabase();
    if(ok){


    bool bugAdded = data.addNewBug(b);
    if(bugAdded){

        msgBox.setText(b.getTitle() + " has been received, your bug ID number is " + b.getID() + " thank you");

         msgBox.exec();
    }
    }else{
        msgBox.setText("cannot connect to database");
    }

}

