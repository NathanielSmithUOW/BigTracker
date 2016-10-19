#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include "database.h"
#include "user.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = 0);
    ChangePassword::ChangePassword(QWidget *parent = 0, User *u = NULL);
    ~ChangePassword();

private slots:
    void on_changePassword_savePushButton_clicked();

private:
    Ui::ChangePassword *ui;
    User *user;
};

#endif // CHANGEPASSWORD_H
