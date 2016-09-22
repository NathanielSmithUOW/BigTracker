#include "user.h"

User::User()
{
    this->ID = -1;
    this->firstName = "";
    this->lastName = "";
    this->userName = "";
    this->emailAddress = "";
    this->password = "";
    this->gender = ' ';
    this->reputation = 0;
    this->role = "";
    this->profilePicture = "";
    this->memberSince = QDate::currentDate();
}
User::User(QString firstName, QString lastName, QString userName, QString emailAddress, QString password, QChar gender, int reputation, QString role, QString profilePicture)
{
    this->ID = -1;
    this->firstName = firstName;
    this->lastName = lastName;
    this->userName = userName;
    this->emailAddress = emailAddress;
    this->password = password;
    this->gender = gender;
    this->reputation = reputation;
    this->role = role;
    this->profilePicture = profilePicture;
    this->memberSince = QDate::currentDate();
}
int User::getID()
{
    return this->ID;
}

QString User::getFirstName()
{
    return (this->firstName);
}
QString User::getLastName()
{
    return (this->lastName);
}
QString User::getUserName()
{
    return this->userName;
}

QString User::getEmail()
{
    return this->emailAddress;
}

QString User::getPassword()
{
    return this->password;
}

QString User::getRole()
{
    return this->role;
}

QChar User::getGender()
{
    return this->gender;
}

int User::getReputation()
{
    return this->reputation;
}

QDate User::getMemberSince()
{
    return this->memberSince;
}
QString User::getProfilePicture()
{
    return this->profilePicture;
}

void User::setFirstName(QString name)
{
    this->firstName = name;
}
void User::setLastName(QString name)
{
    this->lastName = name;
}
void User::setEmail(QString email)
{
    this->emailAddress = email;
}

void User::setPassword(QString password)
{
    this->password = password;
}

void User::setRole(QString role)
{
    this->role = role;
}

void User::setReputation(int repuation)
{
    this->reputation = repuation;
}
void User::setProfilePicture(QString profilePicture)
{
    this->profilePicture = profilePicture;
}
void User::setID(int id)
{
    this->ID = id;
}

void User::setMemberSince(QDate memberSince)
{
    this->memberSince = memberSince;
}