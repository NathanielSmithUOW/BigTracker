#include "addbug.h"
#include "ui_addbug.h"
#include<QMessageBox>
#include<QFileDialog>



AddBug::AddBug(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBug)
{
    ui->setupUi(this);
    ui->addBug_ExtraOptionsFrame->hide();
    this->setFixedSize(880,300);
}




AddBug::~AddBug()
{
    delete ui;

}


//method to upload a file - png xpm jpg txt csv xml accepted
void AddBug::on_addBug_uploadFileButton_clicked()
{
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setWindowTitle("Open File");

    QString directory = dialog.getOpenFileName(this, tr("Open File"),tr("Image Files (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml);; csv files (*csv)"));




   if(!directory.isEmpty()){
        if(ui->addBug_fileUploadCombo->findText(directory)==-1)
                   ui->addBug_fileUploadCombo->addItem(directory);
                    ui->addBug_fileUploadCombo->setCurrentIndex(ui->addBug_fileUploadCombo->findText(directory));

    }

   QString fileName = ui->addBug_fileUploadCombo->currentText();
   QString path = ui->addBug_fileUploadCombo->currentText();
   QFileInfo fi(directory);

   QString file = fi.fileName();//file to be saved to database when method is revised
   QMessageBox msge;

   //qDebug() << "file name is " << file;

}

//removes the last uploaded file
void AddBug::on_addBug_RemoveFileButton_clicked()
{
    ui->addBug_fileUploadCombo->removeItem(ui->addBug_fileUploadCombo->currentIndex());
}

//show only essential data needed interface
void AddBug::showOptions(){
    ui->addBug_ExtraOptionsFrame->show();
    this->setFixedSize(880,600);
}

//hide extra options interface
void AddBug::hideOptions(){
    ui->addBug_ExtraOptionsFrame->hide();
    this->setFixedSize(880,300);
}


//close interface
void AddBug::on_addBug_cancelButton_clicked()
{
    this->close();
}


//method talks to controller class to submit the data
void AddBug::on_addBug_SubmitButton_clicked()
{
    addBugController bugControl;

        QString title = ui->addBug_titleLineEdit->text();

        QString application = ui->addBug_ApplicationQCombo->currentText();
        QString description=ui->addBug_DescriptionTextEdit->toPlainText();
        QString v = ui->addBug_VersionTextEdit->text();
        double version = v.toDouble();
        QString platform=ui->addBug_PlatformCombo->currentText();
        QString component=ui->addBug_ComponentTextEdit->text();
        QString priority = ui->addBug_PriorityCombo_2->currentText();
        QString severity= ui->addBug_SeverityCombo_2->currentText();
        QString walkthrough = ui->addBug_WalkthroughTextEdti->toPlainText();

        QString history = "new bug";
        QString identifiedBy = user.getUserName();//get id of logged in user


        /*
         * test values are correct
         * qDebug() << application  << ' ' <<  title << ' ' << description << ' ' << version << ' ' << platform << ' ' << compenent << ' ' << priority << ' ' << severity << ' ' << walkthrough;
         */
        bugControl.createBug(title,"new",application,version,description,platform,component,priority,severity,walkthrough,history,"tessamarelic@gmail.com");

        reset();

}





//toggle button to toggle add options
void AddBug::on_addBug_OptionsButton_toggled(bool checked)
{

    if(checked==false){
        hideOptions();
    }else{
    showOptions();

    checked=true;
    }

}


//method to reset textedits on interface back to null
void AddBug::reset(){


    ui->addBug_titleLineEdit->setText("");
    ui->addBug_VersionTextEdit->setText("");
    ui->addBug_ComponentTextEdit->setText("");
    ui->addBug_WalkthroughTextEdti->setText("");
    ui->addBug_DescriptionTextEdit->setText("");
}



