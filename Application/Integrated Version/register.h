#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include "database.h"
#include "user.h"
#include "mainwindow.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    Register(QWidget *parent = 0, bool addUser = false);
    ~Register();

private slots:

    void on_register_guestPushButton_clicked();

    void on_register_registerPushButton_clicked();

private:
    Ui::Register *ui;
     MainWindow *main;
};

#endif // REGISTER_H
