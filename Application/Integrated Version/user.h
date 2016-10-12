#ifndef USER_H
#define USER_H

#include <string>
#include <QDate>
#include <sstream>

// EXAMPLE
// addNewUser(User("Bob", "Brown", "Bobby", "bobby123@email.com", "bob123", "Male", 0, "Reporter", ""));
class User
{
    private:
        int ID;
        QString firstName;
        QString lastName;
        QString userName;
        QString emailAddress;
        QString password;
        QString gender;
        int reputation;
        QString role;
        QDate memberSince;
        QDate lastLoggedIn;
        QString profilePicture;
        bool status;


    public:
        User();
        //EXAMPLE = User("Bob", "Brown", "Bobby", "bobby123@email.com", "bob123", 'M', 0, "Reporter", "/images/pic.jpg"));
        User(QString, QString, QString, QString, QString, QString, int, QString, QString);
        int getID();
        QString getFirstName();
        QString getLastName();
        QString getUserName();
        QString getEmail();
        QString getPassword();
        QString getRole();
        QString getGender();
        int getReputation();
        QDate getMemberSince();
        QDate getLastLoggedIn();
        QString getProfilePicture();
        bool getStatus();
        void setID(int);
        void setUserName(QString);
        void setFirstName(QString);
        void setLastName(QString);
        void setEmail(QString);
        void setPassword(QString);
        void setRole(QString);
        void setGender(QString);
        void setReputation(int);
        void setMemberSince(QDate);
        void setLastLoggedIn(QDate);
        void setProfilePicture(QString);
        void setStatus(bool);
};

#endif // USER_H
