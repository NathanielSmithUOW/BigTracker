#include"viewbugcontroller.h"
#include<QMessageBox>
#include"qdebug.h"


viewBugController::viewBugController()
{
    id = 1;//temporary hard coded id to use for testing

}


//retrieves a bug from the database
Bug* viewBugController::getBug(){

    bool ok = data.connectToDatabase();

    //qDebug() << "after connection to database"; test to make sure its getting to this point

    if(ok){

    bug = data.getBugFromID(1);
    data.closeDatabase();

    //qDebug() << "In getBug" << ' ' << bug->getTitle() << endl; test to make sure it has retrieved a bug's attributes

    return bug;
    }else{
        QMessageBox msg;
        msg.setText("cannot connect to the database");

        return bug;
    }

}
