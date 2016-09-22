#ifndef USER_H
#define USER_H

#include <string>
#include <QDate>
#include <sstream>

// EXAMPLE
// addNewUser(User("Bob", "Brown", "Bobby", "bobby123@email.com", "bob123", 'M', 0, "Reporter", ""));
class User
{
    private:
        int ID;
        QString firstName;
        QString lastName;
        QString userName;
        QString emailAddress;
        QString password;
        QChar gender;
        int reputation;
        QString role;
        QDate memberSince;
        QString profilePicture;


    public:
        User();
        //EXAMPLE = User("Bob", "Brown", "Bobby", "bobby123@email.com", "bob123", 'M', 0, "Reporter", "/images/pic.jpg"));
        User(QString, QString, QString, QString, QString, QChar, int, QString, QString);
        int getID();
        QString getFirstName();
        QString getLastName();
        QString getUserName();
        QString getEmail();
        QString getPassword();
        QString getRole();
        QChar getGender();
        int getReputation();
        QDate getMemberSince();
        QString getProfilePicture();
        void setID(int);
        void setFirstName(QString);
        void setLastName(QString);
        void setEmail(QString);
        void setPassword(QString);
        void setRole(QString);
        void setReputation(int);
        void setMemberSince(QDate);
        void setProfilePicture(QString);
};

#endif // USER_H
