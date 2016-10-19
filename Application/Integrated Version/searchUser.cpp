#include "searchUser.h"



searchUser::searchUser(QWidget *parent) :QMainWindow(parent), ui(new Ui::searchUser)
{
    ui->setupUi(this);
}
searchUser::searchUser(QWidget *parent, User *u) :QMainWindow(parent), ui(new Ui::searchUser)
{
    ui->setupUi(this);
    user = u;
    populateTable(searchUsers(this->ui->searchUser_SearchGroupBox, true));
}
searchUser::~searchUser()
{
    delete ui;
}

void searchUser::on_searchUser_searchBarLine_returnPressed()
{
    on_searchUser_SearchButton_clicked();
}

void searchUser::on_searchUser_SearchButton_clicked()
{
    if(ui->searchUser_searchBarLine->text().isEmpty())
    {
        populateTable(searchUsers(ui->searchUser_SearchGroupBox, true));
    }
    else
    {
        populateTable(searchUsers(ui->searchUser_SearchGroupBox, false));
    }
}
void searchUser::populateTable(QList<User *> list)
{
    this->ui->searchUser_Table->clearContents();
    this->ui->searchUser_Table->setRowCount(0);
    this->userList = list;
    for(User *u : list)
    {
        this->ui->searchUser_Table->insertRow(this->ui->searchUser_Table->rowCount());
        this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(u->getID())) );
        this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 1, new QTableWidgetItem(u->getUserName()));
         this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 2, new QTableWidgetItem(u->getFirstName()));
         this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 3, new QTableWidgetItem(u->getLastName()));
         this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 4, new QTableWidgetItem(u->getEmail()));
        this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 5, new QTableWidgetItem(u->getRole()));
        if(u->getStatus())
            this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 6, new QTableWidgetItem("Enabled"));
        else
            this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 6, new QTableWidgetItem("Disabled"));
         this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 7, new QTableWidgetItem(QString::number(u->getReputation())));

         this->ui->searchUser_Table->setItem(this->ui->searchUser_Table->rowCount() - 1, 8, new QTableWidgetItem(u->getMemberSince().toString()));

    }
    this->ui->searchUser_Table->repaint();

}
void searchUser::load_menu()
{

}
void searchUser::dofilterChanged()
{
    int row = ui->searchUser_Table->rowCount();
    QVariant status = this->ui->searchUser_StatusBox->currentText();
    QVariant role = this->ui->searchUser_RoleBox->currentText();
    for (int i = 0; i < row ; ++i)
    {
        ui->searchUser_Table->showRow(i);
        if(status != QVariant(this->ui->searchUser_Table->item(i, 6)->text()) && status != "ANY")
        {
            ui->searchUser_Table->hideRow(i);
        }
        if(role != QVariant(this->ui->searchUser_Table->item(i, 5)->text()) && role != "ANY")
        {
            ui->searchUser_Table->hideRow(i);
        }

    }
}

void searchUser::on_searchUser_StatusBox_currentTextChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
        dofilterChanged();
}

void searchUser::on_searchUser_RoleBox_currentTextChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
        dofilterChanged();
}

void searchUser::on_searchUser_Table_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        int userID = ui->searchUser_Table->selectionModel()->selectedRows(0).value(0).data().toInt();
        Editprofile *editprofile = new Editprofile(this, getUserFromID(userID), user);
        editprofile->show();
    }
}
