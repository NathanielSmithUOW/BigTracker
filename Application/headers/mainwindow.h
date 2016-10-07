#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include "forgetpassword.h"
#include "register.h"
#include "database.h"
#include "searchbug.h"
//#include "editprofile.h"      //test
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_logIn_loginPushButton_clicked();

    void on_logIn_registerPushButton_clicked();

    void on_logIn_forgetpwdPushButton_clicked();

private:
    Ui::MainWindow *ui;
    ForgetPassword *forgetPassword;
    Register *newRegister;
    SearchBug *mainScreen;
};

#endif // MAINWINDOW_H
