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

        if(user->getRole() == "System Administrator")
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
        this->ui->main_bugTable->setItem(this->ui->main_bugTable->rowCount() - 1, 8, new QTableWidgetItem(b->getSubmitted().toString()));
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
    Editprofile *editprofile = new Editprofile(this, getUserFromID(1), user);
    editprofile->show();
}
