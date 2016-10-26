#include "addbug.h"
#include "ui_addbug.h"
#include<QMessageBox>
#include<QFileDialog>



AddBug::AddBug(QWidget *parent) : QMainWindow(parent),ui(new Ui::AddBug)
{
    ui->setupUi(this);
    ui->addBug_ExtraOptionsFrame->hide();
    //this->setFixedSize(880,300);
}
AddBug::AddBug(QWidget *parent, User *u) : QMainWindow(parent),ui(new Ui::AddBug)
{
    ui->setupUi(this);
    if(u != NULL)
    user = getUserFromID(u->getID());
    ui->addBug_ExtraOptionsFrame->hide();
    //this->setFixedSize(880,300);
    loadLists();

}
AddBug::~AddBug()
{
    delete ui;

}
void AddBug::loadLists()
{
    QList<QString> appList = getApplications();
    this->ui->addBug_ApplicationQCombo->addItems(appList);

    QList<QString> platformList = getPlatforms();
    this->ui->addBug_PlatformCombo->addItems(platformList);
}


//method to upload a file - png xpm jpg txt csv xml accepted
void AddBug::on_addBug_uploadFileButton_clicked()
{
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setWindowTitle("Open File");

    QString directory = dialog.getOpenFileName(this, tr("Open File"),tr("All files (*)"));




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
    //this->setFixedSize(880,600);
}

//hide extra options interface
void AddBug::hideOptions(){
    ui->addBug_ExtraOptionsFrame->hide();
    //this->setFixedSize(880,300);
}


//close interface
void AddBug::on_addBug_cancelButton_clicked()
{
    this->close();
}


//method talks to controller class to submit the data
void AddBug::on_addBug_SubmitButton_clicked()
{

        QString title = ui->addBug_titleLineEdit->text();

        QString application = ui->addBug_ApplicationQCombo->currentText();
        QString description=ui->addBug_DescriptionTextEdit->toPlainText();
        if(title.isEmpty() && application.isEmpty() && description.isEmpty())
        {
            QMessageBox::warning(this, "Add Bug","Title, application or description is Blank, need them");
            return;
        }
        QString v = ui->addBug_versionCombo->currentText();
        double version = v.toDouble();
        QString platform=ui->addBug_PlatformCombo->currentText();
        QString component=ui->addBug_componentsCombo->currentText();
        QString priority = ui->addBug_PriorityCombo_2->currentText();
        QString severity= ui->addBug_SeverityCombo_2->currentText();
        QString walkthrough = ui->addBug_WalkthroughTextEdti->toPlainText();


        QString identifiedBy = user->getUserName();//get id of logged in user

        Bug newBug(title,"new",application,version,description,platform,component,priority,severity,walkthrough,identifiedBy);
        addBugHistory(newBug, "New Bug Added");

        QMessageBox msgBox;
        bool bugAdded = addNewBug(newBug);
        if(bugAdded)
        {
            msgBox.setText(newBug.getTitle() + " has been received, thank you");
            msgBox.exec();
            QString message = "You added a bug to the system\n";
            message += newBug.getTitle();
            message += "\t At ";
            message += QDate::currentDate().toString();
            addNotificationToUser(*user, message);
            user->setReputation(user->getReputation()+ ADDBUG_REP);
            updateUser(*user);
            for(int i = 0;i < ui->addBug_fileUploadCombo->count();i++)
            {
               addAttachment(newBug,user->getUserName(), ui->addBug_fileUploadCombo->itemText(i), QDateTime::currentDateTime());
            }

        }
        this->close();
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
    ui->addBug_WalkthroughTextEdti->setText("");
    ui->addBug_DescriptionTextEdit->setText("");
}




void AddBug::on_addBug_ApplicationQCombo_currentIndexChanged(const QString &arg1)
{
    this->ui->addBug_versionCombo->clear();
    this->ui->addBug_componentsCombo->clear();

    QList<double> versionList = getVersions(arg1);
    for(double version : versionList)
        this->ui->addBug_versionCombo->addItem(QString::number(version));


    QList<QString> componentList = getComponents(arg1);
    for(QString comp : componentList)
        this->ui->addBug_componentsCombo->addItem(comp);
}
