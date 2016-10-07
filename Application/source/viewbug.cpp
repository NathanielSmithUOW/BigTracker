
#include"ui_viewbug.h"
#include"viewbug.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>



ViewBug::ViewBug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewBug)
{
    ui->setupUi(this);

    ui->viewBug_middleFrame->hide();
    setBug();

}

ViewBug::~ViewBug()
{
    delete ui;

}

//method to handle toggle of view more button
void ViewBug::on_viewBug_ViewMoreButton_toggled(bool checked)
{
if(checked){
    ui->viewBug_middleFrame->show();

}else{
    ui->viewBug_middleFrame->hide();

}
}

//method to display the bug attributes on the interface text edits
void ViewBug::setBug(){


    viewBugController v;
    b = new Bug();
    b = v.getBug();

    ui->viewBug_TitleTextEdit->setText(b->getTitle());

    //qDebug() << ui->viewBug_TitleTextEdit; to check values are retrieved

    QString tmp = QString::number(b->getID());

    ui->viewBug_IDTextEdit->setText(tmp);
    ui->viewBug_StatusTextEdit->setText(b->getStatus());
    ui->viewBug_ApplicationTextEdit->setText(b->getApplication());
    QString tmp2 = QString::number(b->getVersion());//convert to QString
    ui->viewBug_VersionTextEdit_2->setText(tmp2);
    ui->viewBug_dateSubmittedTextEdit->setText(b->getSubmitted().toString());
    ui->viewBug_AssignedToTextEdit->setText(b->getAssignedTo());
    ui->viewBug_identifiedByTextEdit->setText(b->getIdentifiedBy());
    ui->viewBug_PriorityTextEdit->setText(b->getPriority());
    ui->viewBug_DescriptionTextArea->appendPlainText(b->getDescription());
    ui->viewBug_PlatformTextEdit->setText(b->getPlatform());
    ui->viewBug_SeverityTextEdit->setText(b->getSeverity());
    ui->viewBug_HistoryTextArea->appendPlainText(b->getHistory());

}

