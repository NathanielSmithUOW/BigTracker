#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtSql>
#include <QDebug>
#include "mainwindow.h"
#include "forgetpassword.h"
#include "register.h"
#include "database.h"
//#include "editprofile.h"      //test
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_logIn_loginPushButton_clicked();

    void on_logIn_registerPushButton_clicked();

    void on_logIn_forgetpwdPushButton_clicked();

private:
    Ui::Login *ui;
    MainWindow *main;
    void reset();
    ForgetPassword *forgetPassword;
    Register *newRegister;
};

#endif // MAINWINDOW_H
