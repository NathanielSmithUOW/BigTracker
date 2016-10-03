#include "database.h"
#include "login.h"

// Connect To Database
// Purpose: Connects to the database
// Input: Void
// Output: bool True for success
bool connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("103.29.85.127");
    db.setPort(3306);
    db.setUserName("bugsy");
    db.setPassword("bug1234");
    db.setDatabaseName("BugTracker");
    db.open();
    if(!db.isOpen())
    {
        qCritical() <<  db.lastError().text();
    }
    return db.isOpen();

}
// Close Database
// Purpose: Closes connection to the database
// Input: Void
// Output: void
void closeDatabase()
{
   QSqlDatabase::database().close();
   QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
// Check Login
// Purpose: Checks user credentials against the Database, can use either email or username
// Input: String identifier = either email or username, String password
// Output: bool True for success
bool checkLogin(QVariant identifier, QVariant password)
{

    QSqlQuery query;
    if(identifier.toString().indexOf('@') > 0)
    {
        query.prepare("SELECT COUNT(*) FROM USER WHERE USER.Email_Address = ? && USER.password = ?");
    }
    else
    {
        query.prepare("SELECT COUNT(*) FROM USER WHERE USER.Username = ? && USER.password = ?");
    }
    query.addBindValue(identifier);
    query.addBindValue(password);
    query.exec();
    while(query.next())
    {
       return query.value(0).toBool();
    }
    return false;
}
// Check User Exists
// Purpose: Checks user against the Database, can use either email or username
// Input: String identifier = either email or username
// Output: bool True for Exists already
bool checkUserExists(QVariant identifier)
{
    QSqlQuery query;
    if(identifier.toString().indexOf('@') > 0)
    {
        query.prepare("SELECT COUNT(*) FROM USER WHERE USER.Email_Address = ?");
    }
    else
    {
        query.prepare("SELECT COUNT(*) FROM USER WHERE USER.Username = ?");
    }
    query.addBindValue(identifier);
    query.exec();
    while(query.next())
    {
       return query.value(0).toBool();
    }
    return false;
}
// Get user from ID
// Purpose: Gets user information from the Database
// Input: User ID int
// Output: User object POINTER, NULL If not FOUND
User* getUserFromID(int id)
{
    QSqlQuery query;
    User *u;
    query.prepare("SELECT * FROM USER WHERE USER.ID = ?");
    query.addBindValue(id);
    query.exec();
    while(query.next())
    {
       u = new User( query.value(1).toString(),
                     query.value(2).toString(),
                     query.value(3).toString(),
                     query.value(4).toString(),
                     query.value(5).toString(),
                     query.value(6).toString(),
                     query.value(7).toInt(),
                     query.value(8).toString(),
                     query.value(11).toString()
                     );

                 u->setID(query.value(0).toInt());
                 u->setMemberSince(query.value(9).toDate());
                 u->setLastLoggedIn(query.value(10).toDate());
                 u->setStatus(query.value(12).toBool());
           return u;
    }
    return NULL;
}
// Get user from Username
// Purpose: Gets user information from the Database
// Input: Username String
// Output: User object POINTER, NULL If not FOUND
User* getUserFromUsername(QVariant Username)
{
    QSqlQuery query;
    User *u;
    query.prepare("SELECT * FROM USER WHERE USER.Username = ?");
    query.addBindValue(Username);
    query.exec();
    while(query.next())
    {
        u = new User( query.value(1).toString(),
                      query.value(2).toString(),
                      query.value(3).toString(),
                      query.value(4).toString(),
                      query.value(5).toString(),
                      query.value(6).toString(),
                      query.value(7).toInt(),
                      query.value(8).toString(),
                      query.value(11).toString()
                      );
                  u->setID(query.value(0).toInt());
                  u->setMemberSince(query.value(9).toDate());
                  u->setLastLoggedIn(query.value(10).toDate());
                  u->setStatus(query.value(12).toBool());
           return u;
    }
    return NULL;
}
// Get user from Email
// Purpose: Gets user information from the Database
// Input: User Email String
// Output: User object POINTER, NULL If not FOUND
User* getUserFromEmail(QVariant Email)
{
    QSqlQuery query;
    User *u;
    query.prepare("SELECT * FROM USER WHERE USER.Email_Address = ?");
    query.addBindValue(Email);
    query.exec();
    while(query.next())
    {
        u = new User( query.value(1).toString(),
                      query.value(2).toString(),
                      query.value(3).toString(),
                      query.value(4).toString(),
                      query.value(5).toString(),
                      query.value(6).toString(),
                      query.value(7).toInt(),
                      query.value(8).toString(),
                      query.value(11).toString()
                      );
                  u->setID(query.value(0).toInt());
                  u->setMemberSince(query.value(9).toDate());
                  u->setLastLoggedIn(query.value(10).toDate());
                  u->setStatus(query.value(12).toBool());
           return u;
    }
    return NULL;
}
// Add new User
// Purpose: Adds user information to the database
// Input: User Object
// Output: bool True if successful
// bool addNewUser(User &u)
// {
//     QSqlQuery query;
//     query.prepare("INSERT INTO USER (First_Name, Family_Name, Username, Email_Address, Password, Gender, Reputation, Role, ProfilePicture)"
//                   "VALUES (?,?,?,?,?,?,?,?,?)");
//     query.addBindValue(u.getFirstName());
//     query.addBindValue(u.getLastName());
//     query.addBindValue(u.getUserName());
//     query.addBindValue(u.getEmail());
//     query.addBindValue(u.getPassword());
//     query.addBindValue(u.getGender());
//     query.addBindValue(u.getReputation());
//     query.addBindValue(u.getRole());
//     query.addBindValue(u.getProfilePicture());
//     bool ok =  query.exec();
//     if(!ok)
//     {
//         qCritical() << query.lastError().text();
//     }
//     return ok;
// }
bool addNewUser(User &u)
{
    QSqlQuery query;
    query.prepare("INSERT INTO USER (First_Name, Family_Name, Username, Email_Address, Password, Gender, Reputation, Role, MemberSince,ProfilePicture,Status)"
                  "VALUES (?,?,?,?,?,?,?,?,?,?,?)");
    query.addBindValue(u.getFirstName());
    query.addBindValue(u.getLastName());
    query.addBindValue(u.getUserName());
    query.addBindValue(u.getEmail());
    query.addBindValue(u.getPassword());
    query.addBindValue(u.getGender());
    query.addBindValue(u.getReputation());
    query.addBindValue(u.getRole());
    query.addBindValue(u.getMemberSince());
    query.addBindValue(u.getProfilePicture());
    query.addBindValue(u.getStatus());
    bool ok =  query.exec();
    if(!ok)
    {
        qCritical() << query.lastError().text();
    }
    return ok;
}
// Update User
// Purpose: Updates user information to the database
// Input: User Object
// Output: bool True if successful
bool updateUser(User &u)
{
    QSqlQuery query;
    query.prepare("UPDATE USER SET First_Name = ?, Family_Name = ?, Email_Address = ?, Gender = ?, Password = ?, Reputation = ?, Role = ?, ProfilePicture = ? WHERE ID = ?");
    query.addBindValue(u.getFirstName());
    query.addBindValue(u.getLastName());
    query.addBindValue(u.getEmail());
    query.addBindValue(u.getGender());
    query.addBindValue(u.getPassword());
    query.addBindValue(u.getReputation());
    query.addBindValue(u.getRole());
    query.addBindValue(u.getProfilePicture());
    query.addBindValue(u.getID());
    bool ok =  query.exec();
    if(!ok)
    {
        qDebug() << query.lastError().text();
    }
    return ok;
}
// Get Bug From ID
// Purpose: gets Bug Information from database
// Input: int ID
// Output: Bug Object POINTER, NULL if not found
Bug* getBugFromID(int id)
{
    QSqlQuery query;
    Bug *b;
    query.prepare("SELECT * FROM BUG WHERE BUG.ID = ?");
    query.addBindValue(id);
    query.exec();
    while(query.next())
    {
       b = new Bug( query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString(),
                    query.value(4).toDouble(),
                    query.value(5).toString(),
                    query.value(6).toString(),
                    query.value(7).toString(),
                    query.value(8).toString(),
                    query.value(9).toString(),
                    query.value(10).toString(),
                    query.value(11).toString(),
                    query.value(13).toString()
                     );
                 b->setID(query.value(0).toInt());
                 b->setAssignedTo(query.value(12).toString());
                 b->setSubmitted(query.value(14).toDate());
           return b;
    }
    return NULL;
}
// Add New Bug
// Purpose: Adds Bug Information to database
// Input: Bug Object
// Output: bool, True if successful
bool addNewBug(Bug& b)
{
    QSqlQuery query;
    query.prepare("INSERT INTO BUG (Title, Status, Application, Version, Description, Platform, Component, Priority, Severity, Walkthrough, History, AssignedTo, IdentifiedBy)"
                  "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)");
    query.addBindValue(b.getTitle());
    query.addBindValue(b.getStatus());
    query.addBindValue(b.getApplication());
    query.addBindValue(b.getVersion());
    query.addBindValue(b.getDescription());
    query.addBindValue(b.getPlatform());
    query.addBindValue(b.getComponent());
    query.addBindValue(b.getPriority());
    query.addBindValue(b.getSeverity());
    query.addBindValue(b.getWalkthrough());
    query.addBindValue(b.getHistory());
    query.addBindValue(b.getAssignedTo());
    query.addBindValue(b.getIdentifiedBy());
    bool ok =  query.exec();
    if(!ok)
    {
        qCritical() << query.lastError().text();
    }
    return ok;
}
// Update Existing Bug
// Purpose: Updates Bug Information to database
// Input: Bug Object
// Output: bool, True if successful
bool updateBug(Bug& b)
{
    QSqlQuery query;
    query.prepare("UPDATE BUG SET Title = ?, Status = ?, Application = ?, Version = ?, Description = ?,  Platform = ?, Component = ?, Priority = ?, Severity = ?, Walkthrough = ?, History = ?, AssignedTo = ? WHERE ID = ?");
    query.addBindValue(b.getTitle());
    query.addBindValue(b.getStatus());
    query.addBindValue(b.getApplication());
    query.addBindValue(b.getVersion());
    query.addBindValue(b.getDescription());
    query.addBindValue(b.getPlatform());
    query.addBindValue(b.getComponent());
    query.addBindValue(b.getPriority());
    query.addBindValue(b.getSeverity());
    query.addBindValue(b.getWalkthrough());
    query.addBindValue(b.getHistory());
    query.addBindValue(b.getAssignedTo());
    query.addBindValue(b.getID());
    bool ok =  query.exec();
    if(!ok)
    {
        qCritical() << query.lastError().text();
    }
    return ok;
}
QList<QString> getNotifications(User &u, bool all)
{
    QList<QString> list;

    QSqlQuery query;
    if(all)
    {
         query.prepare("SELECT Notification FROM NOTIFICATIONS WHERE NOTIFICATIONS.UserID = ?");
         query.addBindValue(u.getID());
    }
    else
    {
         query.prepare("SELECT Notification FROM NOTIFICATIONS WHERE NOTIFICATIONS.UserID = ? AND NOTIFICATIONS.Date > ?");
         query.addBindValue(u.getID());
         query.addBindValue(u.getLastLoggedIn());

    }
    query.exec();
    while(query.next())
    {
       list.append(query.value(0).toString());
    }
    return list;
}

QList<QString> getSubscriptions(User &u)
{
    QList<QString> list;

    QSqlQuery query;
         query.prepare("SELECT BugID FROM SUBSCRIPTIONS WHERE SUBSCRIPTIONS.UserID = ?");
         query.addBindValue(u.getID());

    query.exec();
    while(query.next())
    {
       Bug *bug;
       bug=getBugFromID(query.value(0).toInt());
       list.append("Bug ID: " + query.value(0).toString() + " - " + bug->getTitle());
    }
    return list;
}

QList<QString> getSubscribers(Bug &b)
{
    QList<QString> list;

    QSqlQuery query;
         query.prepare("SELECT UserID FROM SUBSCRIPTIONS WHERE SUBSCRIPTIONS.BugID = ?");
         query.addBindValue(b.getID());

    query.exec();
    while(query.next())
    {
       list.append(query.value(0).toString());
    }
    return list;
}
