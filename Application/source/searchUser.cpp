/*
    Write five function for search all return qurey directly


*/


#include "searchUser.h"
#include "database.h"
#include "user.h"
#include <QMessageBox>
#include <QVariant>
#include <QTableView>
#include <QStandardItemModel>
#include <string>

void searchUserFromFirstName(QVariant input, QSqlQuery *reuslt)
{
    QSqlQuery query;

    reuslt = new QSqlQuery;
    query.prepare("SELECT * FROM USER WHERE USER.firstName like ?");
    query.addBindValue(input);
    query.exec();

    if (!query.next())
    {
        return NULL;
    }

    result = query;
}

void searchUserFromLastName(QVariant input, QSqlQuery *reuslt)
{

    QSqlQuery query;

    reuslt = new QSqlQuery;
    query.prepare("SELECT * FROM USER WHERE USER.lastName like ?");
    query.addBindValue(input);
    query.exec();

    if (!query.next())
    {
        return NULL;
    }

    result = query;

}

void searchUserFromUserName(QVariant input, QSqlQuery *reuslt)
{
    QSqlQuery query;

    reuslt = new QSqlQuery;
    query.prepare("SELECT * FROM USER WHERE USER.Username like ?");
    query.addBindValue(input);
    query.exec();

    if (!query.next())
    {
        return NULL;
    }

    result = query;

}

void searchUserFromEmail(QVariant input, QSqlQuery *reuslt)
{

    QSqlQuery query;

    reuslt = new QSqlQuery;
    query.prepare("SELECT * FROM USER WHERE USER.emailAddress = ?");
    query.addBindValue(input);
    query.exec();

    if (!query.next())
    {
        return NULL;
    }

    result = query;

}

void searchUserFromID(QVariant input, QSqlQuery *reuslt)

{

    QSqlQuery query;

    reuslt = new QSqlQuery;
    query.prepare("SELECT * FROM USER WHERE USER.ID = ?");
    query.addBindValue(input);
    query.exec();

    if (!query.next())
    {
        return NULL;
    }

    result = query;
}


sWindow::sWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sWindow)
{
    ui->setupUi(this);
}

sWindow::~sWindow()
{
    delete ui;
}


void sWindow::on_pushButton_clicked()
{
    on_lineEdit_returnPressed();
}

void sWindow::on_lineEdit_returnPressed()
{
    QStandardItemModel  *model = new QStandardItemModel;        //use model

    model->setColumnCount(9);
    model->setHeaderData(0,  Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reputation"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Member Sinence"));


    ui->tableView->setModel(model);     //take into view
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (connectToDatabase())
    {
        int i = 0;
        QVariant input = ui->lineEdit->text();
        QSqlQuery *resultQuery;

        if (ui->Name->isChecked())
        {
            searchUserFromFirstName(input, resultQuery);

            if (resultQuery != NULL)
            {
                while (resultQuery->next())
                {
                    model->setItem(i, 0, new QStandardItem (resultQuery->value(0).toString()));
                    model->setItem(i, 1, new QStandardItem (resultQuery->value(1).toString()));
                    model->setItem(i, 2, new QStandardItem (resultQuery->value(2).toString()));
                    model->setItem(i, 3, new QStandardItem (resultQuery->value(3).toString()));
                    model->setItem(i, 4, new QStandardItem (resultQuery->value(4).toString()));
                    model->setItem(i, 5, new QStandardItem (resultQuery->value(6).toString()));
                    model->setItem(i, 6, new QStandardItem (resultQuery->value(7).toString()));
                    model->setItem(i, 7, new QStandardItem (resultQuery->value(8).toString()));
                    model->setItem(i, 8, new QStandardItem (resultQuery->value(9).toString()));

                    i++;
                }
            }

            searchUserFromLastName(input, resultQuery);
            if (resultQuery != NULL)
            {
                while (resultQuery->next())
                {
                    model->setItem(i, 0, new QStandardItem (resultQuery->value(0).toString()));
                    model->setItem(i, 1, new QStandardItem (resultQuery->value(1).toString()));
                    model->setItem(i, 2, new QStandardItem (resultQuery->value(2).toString()));
                    model->setItem(i, 3, new QStandardItem (resultQuery->value(3).toString()));
                    model->setItem(i, 4, new QStandardItem (resultQuery->value(4).toString()));
                    model->setItem(i, 5, new QStandardItem (resultQuery->value(6).toString()));
                    model->setItem(i, 6, new QStandardItem (resultQuery->value(7).toString()));
                    model->setItem(i, 7, new QStandardItem (resultQuery->value(8).toString()));
                    model->setItem(i, 8, new QStandardItem (resultQuery->value(9).toString()));

                    i++;
                }
            }

        }

        if (ui->UserName->isChecked())
        {
            searchUserFromUserName(input, resultQuery);

            if (resultQuery != NULL)
            {
                while (resultQuery->next())
                {
                    model->setItem(i, 0, new QStandardItem (resultQuery->value(0).toString()));
                    model->setItem(i, 1, new QStandardItem (resultQuery->value(1).toString()));
                    model->setItem(i, 2, new QStandardItem (resultQuery->value(2).toString()));
                    model->setItem(i, 3, new QStandardItem (resultQuery->value(3).toString()));
                    model->setItem(i, 4, new QStandardItem (resultQuery->value(4).toString()));
                    model->setItem(i, 5, new QStandardItem (resultQuery->value(6).toString()));
                    model->setItem(i, 6, new QStandardItem (resultQuery->value(7).toString()));
                    model->setItem(i, 7, new QStandardItem (resultQuery->value(8).toString()));
                    model->setItem(i, 8, new QStandardItem (resultQuery->value(9).toString()));

                    i++;
                }
            }
        }

        if (ui->Email->isChecked())
        {
            searchUserFromEmail(input, resultQuery);
            if (resultQuery != NULL)
            {
                while (resultQuery->next())
                {
                    model->setItem(i, 0, new QStandardItem (resultQuery->value(0).toString()));
                    model->setItem(i, 1, new QStandardItem (resultQuery->value(1).toString()));
                    model->setItem(i, 2, new QStandardItem (resultQuery->value(2).toString()));
                    model->setItem(i, 3, new QStandardItem (resultQuery->value(3).toString()));
                    model->setItem(i, 4, new QStandardItem (resultQuery->value(4).toString()));
                    model->setItem(i, 5, new QStandardItem (resultQuery->value(6).toString()));
                    model->setItem(i, 6, new QStandardItem (resultQuery->value(7).toString()));
                    model->setItem(i, 7, new QStandardItem (resultQuery->value(8).toString()));
                    model->setItem(i, 8, new QStandardItem (resultQuery->value(9).toString()));

                    i++;
                }

            }
        }

        if (ui->ID->isChecked())
        {
            searchUserFromID(input, resultQuery);
            if (resultQuery != NULL)
            {
                while (resultQuery->next())
                {
                    model->setItem(i, 0, new QStandardItem (resultQuery->value(0).toString()));
                    model->setItem(i, 1, new QStandardItem (resultQuery->value(1).toString()));
                    model->setItem(i, 2, new QStandardItem (resultQuery->value(2).toString()));
                    model->setItem(i, 3, new QStandardItem (resultQuery->value(3).toString()));
                    model->setItem(i, 4, new QStandardItem (resultQuery->value(4).toString()));
                    model->setItem(i, 5, new QStandardItem (resultQuery->value(6).toString()));
                    model->setItem(i, 6, new QStandardItem (resultQuery->value(7).toString()));
                    model->setItem(i, 7, new QStandardItem (resultQuery->value(8).toString()));
                    model->setItem(i, 8, new QStandardItem (resultQuery->value(9).toString()));

                    i++;
                }
            }
        }

        ui->tableView->show();

    }
    else
    {
        QMessageBox::warning(this, "Problem", "Connection problem!");
    }
}
