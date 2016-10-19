#include "changepassword.h"
#include "ui_changepassword.h"
#include <QMessageBox>

ChangePassword::ChangePassword(QWidget *parent) :QDialog(parent), ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Change password");



}
ChangePassword::ChangePassword(QWidget *parent, User *u) :QDialog(parent), ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Change password");
    user = u;
    ui->changePassword_usernameDataLabel->setText(u->getUserName());


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
        if(oldPassword!=user->getPassword())
        {
            QMessageBox::warning(this,"Waring","The password is wrong.");
        }
        else
        {
           user->setPassword(newPassword);
            if(updateUser(*user))
            {

                QMessageBox::about(this,"Change password","Your password changed successfully");
                close();
                QString message = "You changed your password at";
                message += QDate::currentDate().toString();
                addNotificationToUser(*user, message);
            }
        }
    }
}
