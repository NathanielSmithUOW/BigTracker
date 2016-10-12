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
    explicit Editprofile(QWidget *parent = 0);
    Editprofile(QWidget *parent = 0, User *profile = NULL, User *user = NULL);
    ~Editprofile();
    //void setID(int id);

private slots:
    void on_editprofile_savePushButton_clicked();

    void on_editprofile_deletePushButton_clicked();

    void on_editprofile_pwdPushButton_clicked();

private:
    Ui::Editprofile *ui;
    User* profile;
    User* user;
    int bugID;
    ChangePassword *changePWD;
    void loadUser();
    void checkAllowEdit();
    QPixmap getProfilePicture();
    void uploadProfilePicture();
};

#endif // EDITPROFILE_H
