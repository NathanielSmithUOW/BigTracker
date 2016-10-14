#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
    QPixmap picture(":/img/img/Software-Bugs.png");    //this one is the logo in the login window, how to create this kind of
                                                       //path you can see the video last time I shared section 3 video 11.
    int w=ui->logIn_picLabel->width();
    int h=ui->logIn_picLabel->height();
    ui->logIn_picLabel->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logIn_loginPushButton_clicked()
{
    QString email = ui->logIn_emailLineEdit->text();
    QString password = ui->logIn_pwdLineEdit->text();
    if(connectToDatabase())
    {
        if(checkLogin(email,password))
        {
            hide();
            mainScreen = new SearchBug(email, this);
            mainScreen ->show();
        }
        else
        {
            QMessageBox::warning(this,"warning","email or password is wrong!");
        }
        closeDatabase();
    }
}

void MainWindow::on_logIn_registerPushButton_clicked()
{
    newRegister = new Register (this);
    newRegister -> show();
}

void MainWindow::on_logIn_forgetpwdPushButton_clicked()
{
    forgetPassword = new ForgetPassword (this);
    forgetPassword -> show();
}
