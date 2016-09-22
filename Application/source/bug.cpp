#include "bug.h"

Bug::Bug()
{
    this->ID = -1;
    this->title = "";
    this->status = "";
    this->application = "";
    this->version = 0.0;
    this->description = "";
    this->platform = "";
    this->component = "";
    this->priority = "";
    this->severity = "";
    this->walkthrough = "";
    this->history = "";
    this->assignedTo = "";
    this->identifiedBy = "";
    this->submitted = QDate::currentDate();
}
Bug::Bug(QString title, QString status, QString application, double version, QString description, QString platform, QString component, QString priority, QString severity, QString walkthrough, QString history, QString identifiedBy)
{
    this->ID = -1;
    this->title = title;
    this->status = status;
    this->application = application;
    this->version = version;
    this->description = description;
    this->platform = platform;
    this->component = component;
    this->priority = priority;
    this->severity = severity;
    this->walkthrough = walkthrough;
    this->history = history;
    this->assignedTo = nullptr;
    this->identifiedBy = identifiedBy;
    this->submitted = QDate::currentDate();
}
int Bug::getID()
{
    return this->ID;
}

QString Bug::getTitle()
{
    return this->title;
}
QString Bug::getStatus()
{
    return this->status;
}
QString Bug::getApplication()
{
    return this->application;
}
double Bug::getVersion()
{
    return this->version;
}
QString Bug::getDescription()
{
    return this->description;
}
QString Bug::getPlatform()
{
    return this->platform;
}
QString Bug::getComponent()
{
    return this->component;
}
QString Bug::getPriority()
{
    return this->priority;
}
QString Bug::getSeverity()
{
    return this->severity;
}
QString Bug::getWalkthrough()
{
    return this->walkthrough;
}
QString Bug::getHistory()
{
    return this->history;
}
QString Bug::getAssignedTo()
{
    return this->assignedTo;
}
QString Bug::getIdentifiedBy()
{
    return this->identifiedBy;
}
QDate Bug::getSubmitted()
{
    return submitted;
}
void Bug::setStatus(QString status)
{
    this->status = status;
}
void Bug::setPriority(QString priority)
{
    this->priority = priority;
}
void Bug::setSeverity(QString severity)
{
    this->severity = severity;
}
void Bug::setAssignedTo(QString assignedTo)
{
    this->assignedTo = assignedTo;
}
void Bug::setHistory(QString history)
{
    this->history = history;
}
void Bug::setID(int id)
{
    this->ID = id;
}
void Bug::setSubmitted(QDate submitted)
{
    this->submitted = submitted;
}
