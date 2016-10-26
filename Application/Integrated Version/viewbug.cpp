
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
            ui->viewBug_StatusComboBox->setEnabled(false);
            ui->viewBug_ApplicationTextEdit->setReadOnly(true);
            ui->viewBug_VersionTextEdit_2->setReadOnly(true);
            ui->viewBug_dateSubmittedTextEdit->setReadOnly(true);
            ui->viewBug_AssignedToComboBox->setEnabled(false);
            ui->viewBug_identifiedByTextEdit->setReadOnly(true);
            ui->viewBug_PriorityComboBox->setEnabled(false);
            ui->viewBug_DescriptionTextArea->setReadOnly(true);
            ui->viewBug_PlatformComboBox->setEnabled(false);
            ui->viewBug_SeverityComboBox->setEnabled(false);
            ui->viewBug_clearCCListButton->hide();
            ui->viewBug_saveButton->hide();
        }
        if(user->getRole() != "Reviewer")
        {
            ui->viewBug_VerifyPatchButton->hide();
           ui->viewBug_VerifySlider->hide();
            ui->viewBug_verifyBox->hide();
        }

    }
    else
    {
        ui->viewBug_IDTextEdit->setReadOnly(true);
        ui->viewBug_StatusComboBox->setEnabled(false);
        ui->viewBug_ApplicationTextEdit->setReadOnly(true);
        ui->viewBug_VersionTextEdit_2->setReadOnly(true);
        ui->viewBug_dateSubmittedTextEdit->setReadOnly(true);
        ui->viewBug_AssignedToComboBox->setEnabled(false);
        ui->viewBug_identifiedByTextEdit->setReadOnly(true);
        ui->viewBug_PriorityComboBox->setEnabled(false);
        ui->viewBug_DescriptionTextArea->setReadOnly(true);
        ui->viewBug_PlatformComboBox->setEnabled(false);
        ui->viewBug_SeverityComboBox->setEnabled(false);
        ui->viewBug_clearCCListButton->hide();
        ui->viewBug_addToCCListButton->hide();
        ui->viewBug_addCommentButton->hide();
        ui->viewBug_commentAddArea->hide();
        ui->viewBug_UploadFileButton->hide();
        ui->viewBug_VerifyPatchButton->hide();
        ui->viewBug_VerifySlider->hide();
        ui->viewBug_verifyBox->hide();
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
    ui->viewBug_StatusComboBox->setCurrentIndex(ui->viewBug_StatusComboBox->findText(bug->getStatus()));
    ui->viewBug_ApplicationTextEdit->setText(bug->getApplication());
    ui->viewBug_VersionTextEdit_2->setText(QString::number(bug->getVersion()));
    ui->viewBug_dateSubmittedTextEdit->setText(bug->getSubmitted().toString("yyyy-MM-dd hh:mm:ss"));
    ui->viewBug_AssignedToComboBox->addItems(getDevelopers());
    ui->viewBug_AssignedToComboBox->setCurrentIndex(ui->viewBug_AssignedToComboBox->findText(bug->getAssignedTo()));
    ui->viewBug_identifiedByTextEdit->setText(bug->getIdentifiedBy());
    ui->viewBug_PriorityComboBox->setCurrentIndex(ui->viewBug_PriorityComboBox->findText(bug->getPriority()));
    ui->viewBug_DescriptionTextArea->appendPlainText(bug->getDescription());
    ui->viewBug_PlatformComboBox->addItems(getPlatforms());
    ui->viewBug_PlatformComboBox->setCurrentIndex(ui->viewBug_PlatformComboBox->findText(bug->getPlatform()));
    ui->viewBug_SeverityComboBox->setCurrentIndex(ui->viewBug_SeverityComboBox->findText(bug->getSeverity()));
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
    bug->setAssignedTo(ui->viewBug_AssignedToComboBox->currentText());
    bug->setPriority(ui->viewBug_PriorityComboBox->currentText());
    bug->setSeverity(ui->viewBug_SeverityComboBox->currentText());
    bug->setStatus(ui->viewBug_StatusComboBox->currentText());
    if(updateBug(*bug))
    {
        QMessageBox::about(this, "Edit Bug","Edit successfully");
        close();
    }
    else
    {
         QMessageBox::warning(this, "Edit Bug","Edit unsuccessfully");
    }

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

void ViewBug::on_viewBug_VerifyPatchButton_clicked()
{
    if(ui->viewBug_StatusComboBox->currentText() == "PATCH UPLOADED")
    {

            bug->setStatus("VERIFIED");
            updateBug(*bug);
            if(ui->viewBug_AssignedToComboBox->currentText() != "" || ui->viewBug_AssignedToComboBox->currentText() != "Unassigned")
            {
                User *dev = getUserFromUsername(ui->viewBug_AssignedToComboBox->currentText());
                if(dev != NULL)
                {
                    dev->setReputation(dev->getReputation() + ui->viewBug_VerifySlider->value());
                    updateUser(*dev);
                    QString message = "Your patch as been verified\n";
                    message += "by " + user->getUserName();
                    message += "\t At ";
                    message += QDate::currentDate().toString();
                    addNotificationToUser(*user, message);
                }
            }
            QString message = "You verified a bug in the system\n";
            message += bug->getTitle();
            message += "\t At ";
            message += QDate::currentDate().toString();
            addNotificationToUser(*user, message);
            user->setReputation(user->getReputation() + VERIFYBUG_REP);
            updateUser(*user);
            QMessageBox::about(this, "Verify Bug","Patch has been verifed");


    }
    else
    {
        ui->viewBug_VerifyPatchButton->setEnabled(false);
       ui->viewBug_VerifySlider->setEnabled(false);

    }

}

void ViewBug::on_viewBug_UploadFileButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setWindowTitle("Open File");

        QString directory = dialog.getOpenFileName(this, tr("Open File"),tr(""));

        QFileInfo fi(directory);

        QString file = fi.fileName();//file to be saved to database when method is revised
        QStringList array = file.split('.');
        QMessageBox msge;
        this->ui->viewBug_attachmentTable->insertRow(this->ui->viewBug_attachmentTable->rowCount());
        this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 0, new QTableWidgetItem(file));
        this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 1, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
         this->ui->viewBug_attachmentTable->setItem(this->ui->viewBug_attachmentTable->rowCount() - 1, 2, new QTableWidgetItem(user->getUserName()));
        addAttachment(*bug, user->getUserName(), file, QDateTime::currentDateTime());

        if(user->getRole() == "Developer" && array.value(array.size()-1) == "patch" && ui->viewBug_AssignedToComboBox->currentText() == user->getUserName())
        {
            bug->setStatus("PATCH UPLOADED");
            updateBug(*bug);
        }

}
