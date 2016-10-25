#include "editprofile.h"
#include "ui_editprofile.h"


Editprofile::Editprofile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editprofile)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit profile");
    loadUser();
}
Editprofile::Editprofile(QWidget *parent, User* profile, User *u) : QDialog(parent), ui(new Ui::Editprofile)
{
    this->profile = profile;
    this->user = u;
      ui->setupUi(this);
      this->setWindowTitle("Edit profile");
      loadUser();
      checkAllowEdit();
}
void Editprofile::checkAllowEdit()
{
    if(user != NULL)
    {
        if(profile->getID() != user->getID() && user->getRole() != "System Administrator")
        {
            this->ui->editprofile_deletePushButton->hide();
            this->ui->editprofile_emailLineEdit->setReadOnly(true);
            this->ui->editprofile_femaleRadioButton->setEnabled(false);
            this->ui->editprofile_fnameLineEdit->setReadOnly(true);
            this->ui->editprofile_lnameLineEdit->setReadOnly(true);
            this->ui->editprofile_maleRadioButton->setEnabled(false);
            this->ui->editprofile_pwdPushButton->hide();
            this->ui->editprofile_savePushButton->hide();
            this->ui->editprofile_changeProfileButton->hide();
            this->ui->editprofile_statusComboBox->setEnabled(false);
             this->ui->editprofile_roleComboBox->setEnabled(false);
             this->ui->editprofile_reputationSpin->setEnabled(false);

        }
        if(user->getRole() != "System Administrator")
        {
            this->ui->editprofile_statusComboBox->setEnabled(false);
             this->ui->editprofile_roleComboBox->setEnabled(false);
             this->ui->editprofile_reputationSpin->setEnabled(false);
        }
    }
    else
    {
        this->ui->editprofile_deletePushButton->hide();
        this->ui->editprofile_emailLineEdit->setReadOnly(true);
        this->ui->editprofile_femaleRadioButton->setEnabled(false);
        this->ui->editprofile_fnameLineEdit->setReadOnly(true);
        this->ui->editprofile_lnameLineEdit->setReadOnly(true);
        this->ui->editprofile_maleRadioButton->setEnabled(false);
        this->ui->editprofile_pwdPushButton->hide();
        this->ui->editprofile_savePushButton->hide();
        this->ui->editprofile_changeProfileButton->hide();
        this->ui->editprofile_statusComboBox->setEnabled(false);
         this->ui->editprofile_roleComboBox->setEnabled(false);
         this->ui->editprofile_reputationSpin->setEnabled(false);
        this->ui->editprofile_statusComboBox->setEnabled(false);
         this->ui->editprofile_roleComboBox->setEnabled(false);
         this->ui->editprofile_reputationSpin->setEnabled(false);
    }
}

void Editprofile::loadUser()
{
    ui->editprofile_UsernameLabelText->setText(profile->getUserName());
    ui->editprofile_fnameLineEdit->setText(profile->getFirstName());
    ui->editprofile_lnameLineEdit->setText(profile->getLastName());
    ui->editprofile_emailLineEdit->setText(profile->getEmail());
    if(profile->getGender()=="M")
    {
            ui->editprofile_maleRadioButton->setChecked(true);
    }
    else if(profile->getGender()=="F")
    {
            ui->editprofile_femaleRadioButton->setChecked(true);
    }
    ui->editprofile_memberSinceLabel->setText(profile->getMemberSince().toString("dd/MM/yyyy"));
    ui->editprofile_roleComboBox->setCurrentIndex(ui->editprofile_roleComboBox->findText(profile->getRole()));
    ui->editprofile_reputationSpin->setValue(profile->getReputation());
    ui->editprofile_pictureLabel->setPixmap(getProfilePicture());
    bool status=profile->getStatus();
    if(status)
    {
        ui->editprofile_statusComboBox->setCurrentIndex(ui->editprofile_statusComboBox->findText("Enabled"));
    }
    else
    {
        ui->editprofile_statusComboBox->setCurrentIndex(ui->editprofile_statusComboBox->findText("Disabled"));
    }
    ui->editprofile_subscribeListWidget->addItems(getSubscriptions(*profile));

}

Editprofile::~Editprofile()
{
    delete ui;
}
void Editprofile::uploadProfilePicture()
{

    QNetworkAccessManager *am = new QNetworkAccessManager(this);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setWindowTitle("Open File");

    QString directory = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

if(!directory.isEmpty())
{


        QNetworkRequest request(QUrl("http://103.29.85.127/upload.php")); //our server with php-script

            QString bound="margin"; //name of the boundary

        //according to rfc 1867 we need to put this string here:
        QByteArray data(QString("--" + bound + "\r\n").toLatin1());
        data.append("Content-Disposition: form-data; name=""action""\r\n\r\n");
        data.append("upload.php\r\n"); //our script's name, as I understood. Please, correct me if I'm wrong
        data.append("--" + bound + "\r\n"); //according to rfc 1867
        data.append("Content-Disposition: form-data; name=""fileToUpload""; filename=");
        data.append(QString::number(user->getID()));
        data.append(".jpg""\r\n"); //name of the input is "uploaded" in my form, next one is a file name.
        data.append("Content-Type: image/jpeg\r\n\r\n"); //data type
        QFile file(directory);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::about(this, "Upload Profile Picture","Error opening file");
               return;
        }

        data.append(file.readAll()); //let's read the file
        data.append("\r\n");
        data.append("--" + bound + "--\r\n"); //closing boundary according to rfc 1867
        request.setRawHeader(QString("Content-Type").toLatin1(),QString("multipart/form-data; boundary=" + bound).toLatin1());
        request.setRawHeader(QString("Content-Length").toLatin1(), QString::number(data.length()).toLatin1());


        QEventLoop loop;
        QObject::connect(am,&QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
        QNetworkReply* reply = am->post(request,data);
        loop.exec();

        if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << reply->errorString();
            QMessageBox::about(this, "Upload Profile","Error uploading");
        }
        QMessageBox::about(this, "Upload Profile","Upload successfully");
}

   ui->editprofile_pictureLabel->setPixmap(getProfilePicture());
}

QPixmap Editprofile::getProfilePicture()
{
    QNetworkAccessManager *nam = new QNetworkAccessManager;
    QString picurl = "http://103.29.85.127/images/profile/";
    int uid = profile->getID();
   picurl  +=  QString::number(uid);
    picurl  +=  ".jpg";
    QUrl url(picurl);
    QEventLoop loop;
    QObject::connect(nam,&QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    loop.exec();

    QPixmap pm;

    if(reply->error())
    {
        qCritical() << reply->errorString();
       return (QPixmap(":/img/blankuser.png"));
    }
    pm.loadFromData(reply->readAll());

    delete reply;
    return pm;
}

void Editprofile::on_editprofile_savePushButton_clicked()
{
        if(ui->editprofile_maleRadioButton->isChecked())
        {
            profile->setGender("M");
        }
        if(ui->editprofile_femaleRadioButton->isChecked())
        {
            profile->setGender("F");
        }
        if(profile->getReputation() != ui->editprofile_reputationSpin->value())
        {
            QString message = "Your reputation has changed from";
            message += QString::number(profile->getReputation());
            message += " to ";
            message += QString::number(ui->editprofile_reputationSpin->value());
            message += "\n At :";
            message += QDate::currentDate().toString();
            addNotificationToUser(*profile, message);
        }
        profile->setFirstName(ui->editprofile_lnameLineEdit->text());
        profile->setLastName(ui->editprofile_fnameLineEdit->text());
        profile->setEmail(ui->editprofile_emailLineEdit->text());
        profile->setReputation(ui->editprofile_reputationSpin->value());
        profile->setRole(ui->editprofile_roleComboBox->currentText());
        if(ui->editprofile_statusComboBox->currentText() == "Enabled")
        {
            profile->setStatus("Enabled");
        }
        else
        {
            profile->setStatus("Disabled");
        }

        if(updateUser(*profile))
        {
            QMessageBox::about(this, "Edit profile","Edit successfully");
        }
        else
        {
             QMessageBox::warning(this, "Edit Profile","Edit unsuccessfully");
        }
        close();
}

void Editprofile::on_editprofile_deletePushButton_clicked()
{
    if(ui->editprofile_subscribeListWidget->currentItem() != NULL)
    {
        QString deletedItem = ui->editprofile_subscribeListWidget->currentItem()->text();
        if(!deletedItem.isNull())
        {
            delete ui->editprofile_subscribeListWidget->currentItem();
           deleteSubscriptions(*getBugFromTitle(deletedItem),*user);
        }
    }

}

void Editprofile::on_editprofile_pwdPushButton_clicked()
{
    changePWD = new ChangePassword (this, user);
    changePWD->show();
    //hide();

}

void Editprofile::on_editprofile_changeProfileButton_clicked()
{
    uploadProfilePicture();
}
