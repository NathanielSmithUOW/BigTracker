#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>
#include "database.h"
#include "user.h"
#include "changepassword.h"
namespace Ui {
class Editprofile;
}

class Editprofile : public QDialog
{
    Q_OBJECT

public:
    explicit Editprofile(const int id,QWidget *parent = 0);
    ~Editprofile();
    //void setID(int id);

private slots:
    void on_editprofile_savePushButton_clicked();

    void on_editprofile_deletePushButton_clicked();

    void on_editprofile_pwdPushButton_clicked();

private:
    Ui::Editprofile *ui;
    int ID;
    int bugID;
    ChangePassword *changePWD;
};

#endif // EDITPROFILE_H
