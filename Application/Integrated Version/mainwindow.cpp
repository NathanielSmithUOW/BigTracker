#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent, User *u) : ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    user = u;

    this->login = parent;
    populateTable(searchBug(this->ui->main_searchBugGroupBox, true));
    this->ui->main_NotificationsGroupBox->hide();
    this->ui->main_addBugButton->hide();
    this->ui->main_editProfileButton->hide();

    ui->actionHelp->connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(doLoadBug()));

    loadMenus();
}
void MainWindow::doViewBug()
{
    int bugID = ui->main_bugTable->selectionModel()->selectedRows(0).value(0).data().toInt();
    viewBug = new ViewBug(this, getBugFromID(bugID), user);
    viewBug->show();
}
void MainWindow::doEditBug()
{
    int bugID = ui->main_bugTable->selectionModel()->selectedRows(0).value(0).data().toInt();
    viewBug = new ViewBug(this, getBugFromID(bugID), user);
    viewBug->show();
}
void MainWindow::doNewUser()
{

}
void MainWindow::doLoadBug()
{
    struct comment
    {
        QString userID;
        QDateTime dateSubmitted;
        QString commentText;
        comment(QString u, QDateTime d, QString c)
        {
            userID = u;
            dateSubmitted = d;
            commentText = c;
        }

    };

    QFile *file = new QFile("C:/Users/njs10/Desktop/BugReports.xml");
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug() << "Error opening";
    return;
    }
    QXmlStreamReader xml(file);

    //we’re going to loop over the entire xml document
    //using QXmlStreamReader’s atEnd() method, in addition to
    //its hasError() method
    xml.readNext();
    int count = 0;
    QStringList ccList;
    QList<comment> commentList;
    QList<comment> attachmentList;

    QList<QPair<QString,QStringList> > ccBigList;
    QList<QPair<QString, QList<comment> > > commentBigList;
    QList<QPair<QString, QList<comment> > > attachmentBigList;
    while(!xml.atEnd() && !xml.hasError())
    {

            QXmlStreamReader::TokenType token = xml.readNext();
        QString id, title, desc, product, comp, platform, status, severity, priority, username, dev;

        QDateTime date, commentDate;

            if(token == QXmlStreamReader::StartDocument)
            {
            continue;
            }
            //what we’re looking for is that start of a valid element
            if(token == QXmlStreamReader::StartElement)
            {
                if(xml.name() == "bug")
                {
                    xml.readNext();
                    while(xml.name() != "bug")
                    {
                        if(xml.name() == "short_desc")
                            desc = xml.readElementText();

                        if(xml.name() == "bug_id")
                            id = xml.readElementText();

                       if(xml.name() == "product")
                             product = xml.readElementText();

                        if(xml.name() == "component")
                            comp = xml.readElementText();

                        if(xml.name() == "op_sys")
                             platform = xml.readElementText();

                        if(xml.name() == "bug_status")
                             status = xml.readElementText();

                        if(xml.name() == "bug_severity")
                            severity = xml.readElementText();

                        if(xml.name() == "priority")
                        {
                            priority;
                            QString str= xml.readElementText();
                            if(str == "--" || str == "P1")
                                priority = "LOW";
                            else if(str == "P2" || str == "P3")
                                priority = "MEDIUM";
                            else
                                priority = "HIGH";

                        }
                        if(xml.name() == "cc")
                           ccList.append(xml.readElementText());

                        if(xml.name() == "reporter")
                            username = xml.readElementText();


                        if(xml.name() == "assigned_to")
                            dev = xml.readElementText();

                        if(xml.name() == "creation_ts")
                        {
                            QStringList dateList = xml.readElementText().split(' ');
                            date = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                        }

                        if(xml.name() == "long_desc")
                        {
                            QString username, commentText;
                            QDateTime commentDate;
                            xml.readNext();
                            while(xml.name() != "long_desc")
                            {
                                if(xml.name() == "bug_when")
                                {
                                    QStringList dateList = xml.readElementText().split(' ');
                                    commentDate = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                                }
                               if(xml.name() == "who")
                                   username = xml.readElementText();

                               if(xml.name() == "thetext")
                                   commentText = xml.readElementText();


                               xml.readNext();
                            }
                            commentList.append(comment(username, commentDate, commentText));
                        }
                        if(xml.name() == "attachment")
                        {
                            QString attacher, path;
                            QDateTime attachmentDate;
                            xml.readNext();
                            while(xml.name() != "attachment")
                            {
                                if(xml.name() == "date")
                                {
                                    QStringList dateList = xml.readElementText().split(' ');
                                    attachmentDate = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                                }
                               if(xml.name() == "attacher")
                                   attacher = xml.readElementText();

                               if(xml.name() == "filename")
                                   path = xml.readElementText();


                               xml.readNext();
                            }
                           attachmentList.append(comment(attacher, attachmentDate, path));
                        }
                        xml.readNext();

                    }


                    //srand(time(NULL));
                   title = product + "_" + id;
                   Bug b(title, status, product, 1.0, desc, platform, comp, priority, severity, " ", username);
                    b.setAssignedTo(dev);
                    b.setSubmitted(date);

                    //b.setID(id.toInt());
                    if(addNewBug(b))
                    {



                        qDebug() << count;
                       //ccList.clear();
                       count++;
                    }
            }

       }
    }
    if(xml.hasError())
      {
          qDebug() << xml.errorString();
      }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadMenus()
{

    ui->main_bugTable->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* ViewBugAction = new QAction("View Bug");
    ui->main_bugTable->connect(ViewBugAction, SIGNAL(triggered()), this, SLOT(doViewBug()));
    ui->main_bugTable->addAction(ViewBugAction);

    QList<QString> appList = getApplications();
    this->ui->main_filterApplicationBox->addItems(appList);

    QList<QString> developerList = getDevelopers();
    this->ui->main_filterDeveloperBox->addItems(developerList);

    this->ui->main_menuNew->setEnabled(false);

    if(user != NULL)
    {
        this->ui->main_RegisterLabel->hide();
        QList<QString> notificationList = getNotifications(*user, false);
        this->ui->main_notificationList->addItems(notificationList);
        user->setLastLoggedIn(QDate::currentDate());

        this->ui->main_NotificationsGroupBox->show();
        this->ui->main_menuNew->setEnabled(true);

        QAction* NewBugAction = new QAction("Bug");
        ui->main_menuNew->addAction(NewBugAction);
        ui->main_menuNew->connect(NewBugAction, SIGNAL(triggered()), this, SLOT(on_main_addBugButton_clicked()));

        this->ui->main_addBugButton->show();
        this->ui->main_editProfileButton->show();

        ui->main_menuNew->addAction(NewBugAction);
        ui->main_menuNew->connect(NewBugAction, SIGNAL(triggered()), this, SLOT(on_main_addBugButton_clicked()));
        this->ui->actionEdit_Profile->connect(this->ui->actionEdit_Profile, SIGNAL(triggered()), this, SLOT(on_main_editProfileButton_clicked()));

        if(user->getRole() == "System Administrator" || user->getRole() == "Triager")
        {
            QAction* EditBugAction = new QAction("Edit Bug");
            ui->main_bugTable->addAction(EditBugAction);
            ui->main_bugTable->connect(EditBugAction, SIGNAL(triggered()), this, SLOT(doEditBug()));

            QAction* NewUserAction = new QAction("User");
            ui->main_menuNew->addAction(NewUserAction);
            ui->main_menuNew->connect(NewUserAction, SIGNAL(triggered()), this, SLOT(doNewUser()));
        }
    }
    else
    {
        this->ui->actionEdit_Profile->setText("Register");

    }


}
void MainWindow::populateTable(QList<Bug*> list)
{
    this->ui->main_bugTable->clearContents();
    this->ui->main_bugTable->setRowCount(0);
    this->bugList = list;
    for(Bug *b : list)
    {
        this->ui->main_bugTable->insertRow(this->ui->main_bugTable->rowCount());
        this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(b->getID())) );
        this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 1, new QTableWidgetItem(b->getTitle()));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 2, new QTableWidgetItem(b->getApplication()));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(b->getVersion())));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 4, new QTableWidgetItem(b->getDescription()));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 5, new QTableWidgetItem(b->getStatus()));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 6, new QTableWidgetItem(b->getPriority()));
         this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 7, new QTableWidgetItem(b->getSeverity()));
        this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 8, new QTableWidgetItem(b->getSubmitted().toString("yyyy-MM-dd hh:mm:ss")));
        this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 9, new QTableWidgetItem(b->getAssignedTo()));
    }
    this->ui->main_bugTable->repaint();



}

void MainWindow::on_main_SearchButton_clicked()
{
    if(this->ui->main_searchLineEdit->text().isEmpty())
    {
       populateTable(searchBug(this->ui->main_searchBugGroupBox, true));
    }
    else
    {
        populateTable(searchBug(this->ui->main_searchBugGroupBox, false));
    }

}

void MainWindow::on_main_bugTable_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
         doViewBug();
}


void MainWindow::dofilterChanged()
{
    int row = ui->main_bugTable->rowCount();
    QVariant status = this->ui->main_filterStatusBox->currentText();
    QVariant application = this->ui->main_filterApplicationBox->currentText();
    QVariant developer = this->ui->main_filterDeveloperBox->currentText();
    for (int i = 0; i < row ; ++i)
    {
        ui->main_bugTable->showRow(i);
        if(status != QVariant(this->ui->main_bugTable->item(i, 5)->text()) && status != "ANY")
        {
            ui->main_bugTable->hideRow(i);
        }
        if(application != QVariant(this->ui->main_bugTable->item(i, 2)->text()) && application != "ALL")
        {
            ui->main_bugTable->hideRow(i);
        }
        if(developer != QVariant(this->ui->main_bugTable->item(i, 9)->text()) && developer != "ANY")
        {
            ui->main_bugTable->hideRow(i);
        }
    }
}

void MainWindow::on_main_filterStatusBox_activated(const QString &arg1)
{
    if(!arg1.isEmpty())
    dofilterChanged();
}

void MainWindow::on_main_filterApplicationBox_activated(const QString &arg1)
{
    if(!arg1.isEmpty())
    dofilterChanged();
}

void MainWindow::on_main_filterDeveloperBox_activated(const QString &arg1)
{
    if(!arg1.isEmpty())
    dofilterChanged();
}

void MainWindow::on_main_addBugButton_clicked()
{
    AddBug *addBug = new AddBug(this, user);
    addBug->show();
}

void MainWindow::on_main_editProfileButton_clicked()
{
    Editprofile *editprofile = new Editprofile(this, user, user);
    editprofile->show();
}

void MainWindow::on_main_searchUsers_clicked()
{
    searchUser *searchProfile = new searchUser(this, user);
    searchProfile->show();

}
/*
std::ifstream fin;
fin.open("C:/Users/njs10/Desktop/users.txt");
int count = 0;
while(!fin.eof())
{
    std::string firstName, lastName, userName, email, password;
    QString role;


    fin >> firstName;
    fin >> lastName;
    fin >> userName;
    fin >> password;
    email = userName + "@uowmail.edu.au";
    if(count % 50 == 1)
        role = "Reviewer";
    else if(count %199 == 1)
        role ="Developer";
    else if(count % 249 == 1)
        role = "Triager";
    else
        role = "Reporter";

    int rep = (count * count * 33) % 100;

    User u(QString::fromStdString(firstName), QString::fromStdString(lastName), QString::fromStdString(userName), QString::fromStdString(email), QString::fromStdString(password), "M", rep, role, " ");
    addNewUser(u);
    count++;

}

struct comment
{
    QString userID;
    QDateTime dateSubmitted;
    QString commentText;
    comment(QString u, QDateTime d, QString c)
    {
        userID = u;
        dateSubmitted = d;
        commentText = c;
    }

};

QFile *file = new QFile("C:/Users/njs10/Desktop/BugReports.xml");
if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
qDebug() << "Error opening";
return;
}
QXmlStreamReader xml(file);

//we’re going to loop over the entire xml document
//using QXmlStreamReader’s atEnd() method, in addition to
//its hasError() method
xml.readNext();
int count = 0;
QStringList ccList;
QList<comment> commentList;
QList<comment> attachmentList;

QList<QPair<QString,QStringList> > ccBigList;
QList<QPair<QString, QList<comment> > > commentBigList;
QList<QPair<QString, QList<comment> > > attachmentBigList;
while(!xml.atEnd() && !xml.hasError())
{

        QXmlStreamReader::TokenType token = xml.readNext();
    QString id, title, desc, product, comp, platform, status, severity, priority, username, dev;

    QDateTime date, commentDate;

        if(token == QXmlStreamReader::StartDocument)
        {
        continue;
        }
        //what we’re looking for is that start of a valid element
        if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "bug")
            {
                xml.readNext();
                while(xml.name() != "bug")
                {
                    if(xml.name() == "short_desc")
                        desc = xml.readElementText();

                    if(xml.name() == "bug_id")
                        id = xml.readElementText();

                   if(xml.name() == "product")
                         product = xml.readElementText();

                    if(xml.name() == "component")
                        comp = xml.readElementText();

                    if(xml.name() == "op_sys")
                         platform = xml.readElementText();

                    if(xml.name() == "bug_status")
                         status = xml.readElementText();

                    if(xml.name() == "bug_severity")
                        severity = xml.readElementText();

                    if(xml.name() == "priority")
                    {
                        priority;
                        QString str= xml.readElementText();
                        if(str == "--" || str == "P1")
                            priority = "LOW";
                        else if(str == "P2" || str == "P3")
                            priority = "MEDIUM";
                        else
                            priority = "HIGH";

                    }
                    if(xml.name() == "cc")
                       ccList.append(xml.readElementText());

                    if(xml.name() == "reporter")
                        username = xml.readElementText();


                    if(xml.name() == "assigned_to")
                        dev = xml.readElementText();

                    if(xml.name() == "creation_ts")
                    {
                        QStringList dateList = xml.readElementText().split(' ');
                        date = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                    }

                    if(xml.name() == "long_desc")
                    {
                        QString username, commentText;
                        QDateTime commentDate;
                        xml.readNext();
                        while(xml.name() != "long_desc")
                        {
                            if(xml.name() == "bug_when")
                            {
                                QStringList dateList = xml.readElementText().split(' ');
                                commentDate = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                            }
                           if(xml.name() == "who")
                               username = xml.readElementText();

                           if(xml.name() == "thetext")
                               commentText = xml.readElementText();


                           xml.readNext();
                        }
                        commentList.append(comment(username, commentDate, commentText));
                    }
                    if(xml.name() == "attachment")
                    {
                        QString attacher, path;
                        QDateTime attachmentDate;
                        xml.readNext();
                        while(xml.name() != "attachment")
                        {
                            if(xml.name() == "date")
                            {
                                QStringList dateList = xml.readElementText().split(' ');
                                attachmentDate = QDateTime::fromString((dateList.value(0) + " " + dateList.value(1)), "yyyy-MM-dd hh:mm:ss");
                            }
                           if(xml.name() == "attacher")
                               attacher = xml.readElementText();

                           if(xml.name() == "filename")
                               path = xml.readElementText();


                           xml.readNext();
                        }
                       attachmentList.append(comment(attacher, attachmentDate, path));
                    }
                    xml.readNext();

                }


                //srand(time(NULL));
               title = product + "_" + id;
               Bug b(title, status, product, 1.0, desc, platform, comp, priority, severity, " ", username);
                b.setAssignedTo(dev);
                b.setSubmitted(date);

                //b.setID(id.toInt());
                if(addNewBug(b))
                {
                   // for(QString cc : ccList)
                   // {
                   //     Bug *nb = getBugFromTitle(title);
                   //     User *us = getUserFromUsername(cc);
                   //     if(nb != NULL && us != NULL)
                   //     {
                   //             //addSubscriber(*nb, *us);
                   //
                   //     }
                   // }
                    ccBigList.append(QPair<QString, QStringList>(title, ccList));
                   commentBigList.append(QPair<QString, QList<comment> >(title, commentList));
                    attachmentBigList.append(QPair<QString, QList<comment> >(title, attachmentList));

                   // for(comment cc : commentList)
                   // {
                   //     Bug *nb = getBugFromTitle(title);
                   //     User *us = getUserFromUsername(cc.userID);
                   //     if(nb != NULL && us != NULL)
                   //     {
                   //             addBugComment(*nb, *us, cc.commentText, cc.dateSubmitted);
                   //
                   //     }
                   // }
                   // for(comment attach : attachmentList)
                   // {
                   //     Bug *nb = getBugFromTitle(title);
                   //     if(nb != NULL)
                   //     {
                   //             addAttachment(*nb, attach.userID, attach.commentText,attach.dateSubmitted);
                   //
                   //     }
                   // }

                    qDebug() << count;
                   //ccList.clear();
                   count++;
                }
        }

   }
}
if(xml.hasError())
  {
      qDebug() << xml.errorString();
  }
count = 0;

QString ccfilename="ccData.txt";
QFile ccfile( ccfilename );

    QTextStream ccstream( &ccfile );



qDebug() << "Adding cc list";
for(QPair<QString, QStringList> pair : ccBigList)
{
    QString title = pair.first;
    for(QString cc : pair.second)
    {
        Bug *nb = getBugFromTitle(title);
        User *us = getUserFromUsername(cc);
        if(nb != NULL && us != NULL)
        {
            //addSubscriber(*nb, *us);
            ccstream << title << "," << cc << endl;
        }

    }
    count++;
    qDebug() << "CC : " << count;
}
QString commentfilename="commentData.txt";
QFile commentfile( commentfilename );

    QTextStream commentstream( &commentfile );

count = 0;
qDebug() << " Now adding comments";
for(QPair<QString, QList<comment>> pair : commentBigList)
{
    QString title = pair.first;
    for(comment cc : pair.second)
     {
        Bug *nb = getBugFromTitle(title);
        User *us = getUserFromUsername(cc.userID);
        if(nb != NULL && us != NULL)
        {
               // addBugComment(*nb, *us, cc.commentText, cc.dateSubmitted);
                commentstream << title << "," << cc.userID << "," << cc.commentText << "," << cc.dateSubmitted.toString("yyyy-MM-dd hh:mm:ss") << endl;
        }
     }
    count++;
    qDebug() << "Comment : " << count;
}

QString attachfilename="attachData.txt";
QFile attachfile( attachfilename );

    QTextStream attachstream( &attachfile );
count = 0;
qDebug() << " Now adding attachment";
for(QPair<QString, QList<comment>> pair : attachmentBigList)
{
    QString title = pair.first;
    for(comment attach : pair.second)
     {
         Bug *nb = getBugFromTitle(title);
         if(nb != NULL)
         {
             //addAttachment(*nb, attach.userID, attach.commentText,attach.dateSubmitted);
             attachstream << title << "," << attach.userID << "," << attach.commentText << "," << attach.dateSubmitted.toString("yyyy-MM-dd hh:mm:ss") << endl;
        }
     }
    count++;
    qDebug() << "attachment : " << count;
}
qDebug() << " done";
*/

