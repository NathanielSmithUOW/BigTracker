#ifndef ADDBUG_H
#define ADDBUG_H

#include <QMainWindow>
//#include"database.h"
#include"user.h"
#include"bug.h"
#include"addbugcontroller.h"


namespace Ui {
class AddBug;
}

class AddBug : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddBug(QWidget *parent = 0);
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

private:
    Ui::AddBug *ui;

    User user;


};

#endif // ADDBUG_H
