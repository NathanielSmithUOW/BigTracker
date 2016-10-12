#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "bug.h"
#include "user.h"
#include "database.h"
#include "viewbug.h"
#include "addbug.h"
#include "editprofile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent, User * u);
    ~MainWindow();
      void populateTable(QList<Bug*>);

private slots:
    void on_main_SearchButton_clicked();
    void doViewBug();
    void doEditBug();
    void doNewUser();

    void on_main_bugTable_doubleClicked(const QModelIndex &index);
    void on_main_filterStatusBox_activated(const QString &arg1);
    void on_main_filterApplicationBox_activated(const QString &arg1);
    void on_main_filterDeveloperBox_activated(const QString &arg1);

    void on_main_addBugButton_clicked();

    void on_main_editProfileButton_clicked();

private:
    Ui::MainWindow *ui;
    User *user;
    QList<Bug*> bugList;
    QWidget *login;
    //EditProfile *editProfile;
    ViewBug *viewBug;


    void loadMenus();
    void dofilterChanged();
};

#endif // MAINWINDOW_H
