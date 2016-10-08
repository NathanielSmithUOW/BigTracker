#include "editprofile.h"
#include "ui_editprofile.h"
#include <QDebug>
#include <QList>
#include <QMessageBox>
Editprofile::Editprofile(const int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editprofile)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit profile");
    User *u;
    ID=id;
    if(connectToDatabase())
    {
        u = getUserFromID(ID);
        ui->editprofile_usernameLineEdit->setText(u->getUserName());
        ui->editprofile_fnameLineEdit->setText(u->getFirstName());
        ui->editprofile_lnameLineEdit->setText(u->getLastName());
        ui->editprofile_emailLineEdit->setText(u->getEmail());
        if(u->getGender()=="M")
        {
                ui->editprofile_maleCheckBox->setChecked(true);
        }
        if(u->getGender()=="F")
        {
                ui->editprofile_femaleCheckBox->setChecked(true);
        }
        ui->editprofile_memberSinceLabel->setText(u->getMemberSince().toString("dd/MM/yyyy"));
        ui->editprofile_roleDataLabel->setText(u->getRole());
        int reputation=u->getReputation();
        QString UserReputation = QString::number(reputation,10);
        ui->editprofile_reputationDataLabel->setText(UserReputation);
        bool status=u->getStatus();
        qDebug()<<u->getStatus();
        if(status)
        {
            ui->editprofile_statusDataLabel->setText("Enabled");
        }
        else
        {
            ui->editprofile_statusDataLabel->setText("Disabled");
        }
        ui->editprofile_subscribeListWidget->addItems(getSubscriptions(*u));
    }
    closeDatabase();
}

Editprofile::~Editprofile()
{
    delete ui;
}

void Editprofile::on_editprofile_savePushButton_clicked()
{
    User *u;
    if(connectToDatabase())
    {
        u=getUserFromID(ID);
        if(ui->editprofile_maleCheckBox->isChecked())
        {
            u->setGender("M");
        }
        if(ui->editprofile_femaleCheckBox->isChecked())
        {
            u->setGender("F");
        }
        QString lastName = ui->editprofile_lnameLineEdit->text();
        QString firstName = ui->editprofile_fnameLineEdit->text();
        QString email = ui->editprofile_emailLineEdit->text();
        QString username = ui->editprofile_usernameLineEdit->text();

        u->setFirstName(firstName);
        u->setLastName(lastName);
        u->setEmail(email);
        u->setUserName(username);
        if(updateUser(*u)&&deleteSubscriptions(bugID))
        {
            qDebug()<<"updated";
            QMessageBox::about(this, "Edit profile","Edit successfully");
        }
    }
    closeDatabase();
}

void Editprofile::on_editprofile_deletePushButton_clicked()
{
    QString deletedItem;
    deletedItem = ui->editprofile_subscribeListWidget->currentItem()->text();
    QStringList myList = deletedItem.split(" ");
    bugID = myList[0].toInt();
    delete ui->editprofile_subscribeListWidget->currentItem();
}

void Editprofile::on_editprofile_pwdPushButton_clicked()
{
    changePWD = new ChangePassword (ID, this);
    changePWD->show();
}
