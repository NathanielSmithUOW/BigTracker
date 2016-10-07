#ifndef VIEWBUGCONTROLLER_H
#define VIEWBUGCONTROLLER_H


#include "bug.h"
#include "database.h"
#include "users.h"

class viewBugController
{

private:
    Database data;
    User user;
    Bug *bug;
    int id;

public:
    viewBugController();
    Bug* getBug();
    //~viewBugController();
};

#endif // VIEWBUGCONTROLLER_H
