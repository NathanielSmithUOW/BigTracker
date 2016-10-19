#ifndef BUG_H
#define BUG_H

#include<QDate>
#include <QList>
class Bug
{
    private:
        int ID;
        QString title;
        QString status;
        QString application;
        double version;
        QString description;
        QString platform;
        QString component;
        QString priority;
        QString severity;
        QString walkthrough;
        QString assignedTo;
        QString identifiedBy;
        QDateTime submitted;

    public:
        Bug();
        Bug(QString, QString, QString, double, QString, QString, QString,QString,QString, QString, QString);
        int getID();
        QString getTitle();
        QString getStatus();
        QString getApplication();
        double getVersion();
        QString getDescription();
        QString getPlatform();
        QString getComponent();
        QString getPriority();
        QString getSeverity();
        QString getWalkthrough();
        QString getAssignedTo();
        QString getIdentifiedBy();
        QDateTime getSubmitted();
        void setStatus(QString);
        void setPriority(QString);
        void setSeverity(QString);
        void setAssignedTo(QString);
        void setHistory(QString);
        void setID(int);
        void setSubmitted(QDateTime);
};

#endif // BUG_H
