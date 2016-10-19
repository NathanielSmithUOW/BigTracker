
#include"ui_viewbug.h"
#include "database.h"
#include"viewbug.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>



ViewBug::ViewBug(QWidget *parent) : QMainWindow(parent), ui(new Ui::ViewBug)
{
    ui->setupUi(this);
    user = NULL;
    bug = getBugFromID(1);
    ui->viewBug_middleGroupBox->hide();
    setBug();
    checkRole();

}
ViewBug::ViewBug (QWidget *parent, Bug *b, User *u) : QMainWindow(parent), ui(new Ui::ViewBug)
{
    bug = b;
    user = u;
    ui->setupUi(this);
    ui->viewBug_middleGroupBox->hide();
    ViewBug::setFixedHeight(700);
    this->ui->viewBug_middleGroupBox->setFixedHeight(800);
    this->ui->viewBug_CommentListArea->setStyleSheet( "QListWidget::item { border-bottom: 1px solid black; }QListWidget::item:selected {background-color: white; color: black}" );
    setBug();
    checkRole();
}

ViewBug::~ViewBug()
{
    delete ui;

}
void ViewBug::checkRole()
{
    if(user != NULL)
    {
        if(user->getRole() != "System Administrator" && user->getRole() != "Triager")
        {
            ui->viewBug_IDTextEdit->setReadOnly(true);
            ui->viewBug_StatusTextEdit->setReadOnly(true);
            ui->viewBug_ApplicationTextEdit->setReadOnly(true);
            ui->viewBug_VersionTextEdit_2->setReadOnly(true);
            ui->viewBug_dateSubmittedTextEdit->setReadOnly(true);
            ui->viewBug_AssignedToTextEdit->setReadOnly(true);
            ui->viewBug_identifiedByTextEdit->setReadOnly(true);
            ui->viewBug_PriorityTextEdit->setReadOnly(true);
            ui->viewBug_DescriptionTextArea->setReadOnly(true);
            ui->viewBug_PlatformTextEdit->setReadOnly(true);
            ui->viewBug_SeverityTextEdit->setReadOnly(true);
            ui->viewBug_clearCCListButton->hide();
            ui->viewBug_saveButton->hide();
        }
    }
    else
    {
        ui->viewBug_IDTextEdit->setReadOnly(true);
        ui->viewBug_StatusTextEdit->setReadOnly(true);
        ui->viewBug_ApplicationTextEdit->setReadOnly(true);
        ui->viewBug_VersionTextEdit_2->setReadOnly(true);
        ui->viewBug_dateSubmittedTextEdit->setReadOnly(true);
        ui->viewBug_AssignedToTextEdit->setReadOnly(true);
        ui->viewBug_identifiedByTextEdit->setReadOnly(true);
        ui->viewBug_PriorityTextEdit->setReadOnly(true);
        ui->viewBug_DescriptionTextArea->setReadOnly(true);
        ui->viewBug_PlatformTextEdit->setReadOnly(true);
        ui->viewBug_SeverityTextEdit->setReadOnly(true);
        ui->viewBug_clearCCListButton->hide();
        ui->viewBug_addToCCListButton->hide();
        ui->viewBug_addCommentButton->hide();
    }
}

//method to handle toggle of view more button
void ViewBug::on_viewBug_ViewMoreButton_toggled(bool checked)
{
if(checked){
    ui->viewBug_middleGroupBox->show();
    ViewBug::setFixedHeight(1500);

}else{
    ui->viewBug_middleGroupBox->hide();
    ViewBug::setFixedHeight(700);

}
}

//method to display the bug attributes on the interface text edits
void ViewBug::setBug(){


    ui->viewBug_TitleTextEdit->setText(bug->getTitle());

    //qDebug() << ui->viewBug_TitleTextEdit; to check values are retrieved

    ui->viewBug_IDTextEdit->setText(QString::number(bug->getID()));
    ui->viewBug_StatusTextEdit->setText(bug->getStatus());
    ui->viewBug_ApplicationTextEdit->setText(bug->getApplication());
    ui->viewBug_VersionTextEdit_2->setText(QString::number(bug->getVersion()));
    ui->viewBug_dateSubmittedTextEdit->setText(bug->getSubmitted().toString("yyyy-MM-dd hh:mm:ss"));
    ui->viewBug_AssignedToTextEdit->setText(bug->getAssignedTo());
    ui->viewBug_identifiedByTextEdit->setText(bug->getIdentifiedBy());
    ui->viewBug_PriorityTextEdit->setText(bug->getPriority());
    ui->viewBug_DescriptionTextArea->appendPlainText(bug->getDescription());
    ui->viewBug_PlatformTextEdit->setText(bug->getPlatform());
    ui->viewBug_SeverityTextEdit->setText(bug->getSeverity());
    ui->viewBug_CCListArea->addItems(getSubscribers(*bug));
     ui->viewBug_CommentListArea->addItems(getBugComments(*bug));
     load_attachments();

}


void ViewBug::on_viewBug_addToCCListButton_clicked()
{
     ui->viewBug_CCListArea->clear();
     addSubscriber(*bug, *user);
     ui->viewBug_CCListArea->addItems(getSubscribers(*bug));
}

void ViewBug::on_viewBug_clearCCListButton_clicked()
{
    deleteAllSubscribers(*bug);
     ui->viewBug_CCListArea->clear();
}

void ViewBug::on_viewBug_addCommentButton_clicked()
{
    if(!ui->viewBug_commentAddArea->toPlainText().isEmpty())
    {
        addBugComment(*bug, *user, ui->viewBug_commentAddArea->toPlainText());
        ui->viewBug_CommentListArea->addItem(user->getUserName() + "\t" + QDate::currentDate().toString() + "\n" + ui->viewBug_commentAddArea->toPlainText());
    }
    ui->viewBug_commentAddArea->clear();
}

void ViewBug::on_viewBug_cancelButton_clicked()
{
    this->close();
}

void ViewBug::on_viewBug_saveButton_clicked()
{

}
void ViewBug::load_attachments()
{
    this->ui->viewBug_attachmentTable->clearContents();
    this->ui->viewBug_attachmentTable->setRowCount(0);
    QList<QString> list = getAttachments(*bug);
    for(QString attachment : list)
    {
        QStringList array = attachment.split("|");
        this->ui->viewBug_attachmentTable->insertRow(this->ui->viewBug_attachmentTable->rowCount());
        this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 0, new QTableWidgetItem(array.value(0)));
        this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 1, new QTableWidgetItem(array.value(1)));
         this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 2, new QTableWidgetItem(array.value(2)));
    }
    this->ui->viewBug_attachmentTable->repaint();

}
