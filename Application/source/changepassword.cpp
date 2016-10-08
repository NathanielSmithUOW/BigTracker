#include "changepassword.h"
#include "ui_changepassword.h"
#include <QMessageBox>

ChangePassword::ChangePassword(const int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Change password");
    User *u;
    ID=id;
    if(connectToDatabase())
    {
        u = getUserFromID(ID);
        ui->changePassword_usernameDataLabel->setText(u->getUserName());
    }
    closeDatabase();
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_changePassword_savePushButton_clicked()
{
    QString oldPassword = ui->changePassword_oldPwdLineEdit->text();
    QString newPassword = ui->changePassword_newPwdLineEdit->text();
    QString verifyPassword = ui->changePassword_verifyLineEdit->text();

    if(newPassword!=verifyPassword)
    {
        QMessageBox::warning(this,"Waring","The passwords are not matched.");
    }
    else
    {
        User *u;
        if(connectToDatabase())
        {
            u = getUserFromID(ID);
            if(oldPassword!=u->getPassword())
            {
                QMessageBox::warning(this,"Waring","The password is wrong.");
            }
            else
            {
                u->setPassword(newPassword);
                if(updateUser(*u))
                {
                    //hide();
                    //qDebug()<<"changed";
                    QMessageBox::about(this,"Change password","Your password changed successfully");
                }
            }
        }
        closeDatabase();
    }
}
