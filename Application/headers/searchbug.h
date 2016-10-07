#ifndef SEARCHBUG_H
#define SEARCHBUG_H

#include <QDialog>
#include "user.h"
#include "editprofile.h"
#include "database.h"
#include "viewprofile.h"

namespace Ui {
class SearchBug;
}

class SearchBug : public QDialog
{
    Q_OBJECT

public:
    explicit SearchBug(QString email, QWidget *parent = 0);
    ~SearchBug();

private slots:
    void on_searchbug_editProfilePushButton_clicked();

    void on_searchbug_viewProfilePushButton_clicked();

private:
    Ui::SearchBug *ui;
    int userID;
    Editprofile *edit;
    ViewProfile *view;
};

#endif // SEARCHBUG_H
