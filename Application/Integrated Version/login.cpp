#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "user.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
    QPixmap picture(":/img/login.png");    //this one is the logo in the login window, how to create this kind of
                                                        //path you can see the video last time I shared section 3 video 11.
     int w=ui->logIn_picLabel->width();
     int h=ui->logIn_picLabel->height();
     ui->logIn_picLabel->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));

     QString error;
     bool ok = connectToDatabase(error);
     if(!ok)
     {
         QMessageBox::warning(this, "Error", error);
         //return 0;
     }

}

Login::~Login()
{
    delete ui;
}
void Login::reset()
{
    ui->logIn_emailLineEdit->clear();
    ui->logIn_pwdLineEdit->clear();
}

void Login::on_logIn_loginPushButton_clicked()
{
    QString identifier = ui->logIn_emailLineEdit->text();
    QString password = ui->logIn_pwdLineEdit->text();
    if(checkLogin(identifier,password))
    {
        User *u;
        if(identifier.indexOf('@') > 0)
        {
            u = getUserFromEmail(identifier);
        }
        else
        {
            u = getUserFromUsername(identifier);
        }
        main = new MainWindow(this, u);
        main->show();
        close();
    }
    else
    {
        QMessageBox::warning(this,"warning","email or password is wrong!");
    }

}

void Login::on_logIn_registerPushButton_clicked()
{
    hide();
    newRegister = new Register (this, false);
    newRegister -> show();
}

void Login::on_logIn_forgetpwdPushButton_clicked()
{
    forgetPassword = new ForgetPassword (this);
    forgetPassword -> show();
}

void Login::on_logIn_pwdLineEdit_returnPressed()
{
    on_logIn_loginPushButton_clicked();
}
