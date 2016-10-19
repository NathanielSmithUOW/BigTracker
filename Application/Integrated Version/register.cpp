#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPluginLoader>


Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle("Register");
}

Register::~Register()
{
    delete ui;
}


void Register::on_register_guestPushButton_clicked()
{
    hide();
    main = new MainWindow(this, NULL);
    main->show();
}

void Register::on_register_registerPushButton_clicked()
{
    QString lastName = ui->register_lnameLineEdit->text();
    QString firstName = ui->register_fnameLineEdit->text();
    QString email = ui->register_emailLineEdit->text();
    QString username = ui->register_usernameLineEdit->text();
    QString password = ui->register_pwdLineEdit->text();
    QString verifyPwd = ui->register_verifypwdLineEdit->text();

    if(password==verifyPwd)
    {
        QMessageBox::about(this,"Register","The new account created!");

            if(checkUserExists(email))
            {
                QMessageBox::warning(this, "warning", "The user already exists");
            }
            else
            {
                User *newUser = new User();
                newUser->setFirstName(firstName);
                newUser->setLastName(lastName);
                newUser->setUserName(username);
                newUser->setEmail(email);
                newUser->setPassword(password);
                newUser->setRole("Reporter");
                if(addNewUser(*newUser))
                {
                    qDebug()<<"Inserted";
                    hide();
                    main = new MainWindow(this, newUser);
                    main->show();
                    addNotificationToUser(*newUser, "Welcome to BugTracker");
                }
            }

        close();
    }
    else
    {
        QMessageBox::warning(this,"Waring","The passwords are not matched.");
    }
}
