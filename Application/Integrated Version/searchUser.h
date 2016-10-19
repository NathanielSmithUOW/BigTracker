#ifndef searchUser_H
#define searchUser_H

#include <QMainWindow>
#include "database.h"
#include "ui_searchUser.h"
#include "user.h"
#include "editprofile.h"
#include <QMessageBox>
#include <QVariant>
#include <QTableView>
#include <QStandardItemModel>
#include <string>

namespace Ui {
class searchUser;
}

class searchUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchUser(QWidget *parent = 0);
    searchUser(QWidget *parent = 0, User *u = NULL);
    ~searchUser();

private slots:
    void on_searchUser_searchBarLine_returnPressed();
    void on_searchUser_SearchButton_clicked();

    void on_searchUser_StatusBox_currentTextChanged(const QString &arg1);

    void on_searchUser_RoleBox_currentTextChanged(const QString &arg1);

    void on_searchUser_Table_doubleClicked(const QModelIndex &index);

private:
    Ui::searchUser *ui;
    User *user;
    QList<User*> userList;
    void populateTable(QList<User *>);
    void load_menu();
    void dofilterChanged();
};

#endif // searchUser_H
