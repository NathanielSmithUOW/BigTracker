#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include "database.h"
#include "user.h"
#include "searchbug.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:

    void on_register_guestPushButton_clicked();

    void on_register_registerPushButton_clicked();

private:
    Ui::Register *ui;
    SearchBug *mainscreen;        //this one is the main screen(search the bug), maybe you need to change.
};

#endif // REGISTER_H
