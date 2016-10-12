#ifndef ADDBUG_H
#define ADDBUG_H

#include <QMainWindow>
#include"database.h"
#include"user.h"
#include "mainwindow.h"
#include"bug.h"


namespace Ui {
class AddBug;
}

class AddBug : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddBug(QWidget *parent = 0);
    AddBug(QWidget *parent, User * u);
    ~AddBug();
    User add(QString,QString,QString,double,QString,QString,QString,QString,QString);
    void showOptions();
    void hideOptions();
    void reset();

private slots:
       void on_addBug_uploadFileButton_clicked();
       void on_addBug_RemoveFileButton_clicked();
       void on_addBug_cancelButton_clicked();
       void on_addBug_SubmitButton_clicked();
       void on_addBug_OptionsButton_toggled(bool checked);

       void on_addBug_ApplicationQCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::AddBug *ui;
    User *user;
    void loadLists();


};

#endif // ADDBUG_H
