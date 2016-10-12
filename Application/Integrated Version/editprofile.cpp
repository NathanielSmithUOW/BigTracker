#include "editprofile.h"
#include "ui_editprofile.h"
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

Editprofile::Editprofile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editprofile)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit profile");
    loadUser();
}
Editprofile::Editprofile(QWidget *parent, User* profile, User *user) : QDialog(parent), ui(new Ui::Editprofile)
{
    this->profile = profile;
    this->user = user;
      ui->setupUi(this);
      this->setWindowTitle("Edit profile");
      loadUser();
      checkAllowEdit();
}
void Editprofile::checkAllowEdit()
{
    if(profile->getID() != user->getID() || user->getRole() != "System Administrator")
    {
        this->ui->editprofile_deletePushButton->setEnabled(false);
        this->ui->editprofile_emailLineEdit->setReadOnly(true);
        this->ui->editprofile_femaleCheckBox->setEnabled(false);
        this->ui->editprofile_fnameLineEdit->setReadOnly(true);
        this->ui->editprofile_lnameLineEdit->setReadOnly(true);
        this->ui->editprofile_maleCheckBox->setEnabled(false);
        this->ui->editprofile_pwdPushButton->hide();
        this->ui->editprofile_savePushButton->hide();
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
            ui->editprofile_maleCheckBox->setChecked(true);
    }
    else if(profile->getGender()=="F")
    {
            ui->editprofile_femaleCheckBox->setChecked(true);
    }
    ui->editprofile_memberSinceLabel->setText(profile->getMemberSince().toString("dd/MM/yyyy"));
    ui->editprofile_roleDataLabel->setText(profile->getRole());
    int reputation= profile->getReputation();
    QString UserReputation = QString::number(reputation,10);
    ui->editprofile_reputationDataLabel->setText(UserReputation);
    ui->editprofile_pictureLabel->setPixmap(getProfilePicture());
    bool status=profile->getStatus();
    if(status)
    {
        ui->editprofile_statusDataLabel->setText("Enabled");
    }
    else
    {
        ui->editprofile_statusDataLabel->setText("Disabled");
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
    QString path("E:\QT_playing\TestingHttpRequests\debug\Chrysanthemum.jpg");
    QNetworkRequest request(QUrl("http://192.168.0.194/testuploads.php")); //our server with php-script

        QString bound="margin"; //name of the boundary

    //according to rfc 1867 we need to put this string here:
    QByteArray data(QString("--" + bound + "\r\n").toLatin1());
    data.append("Content-Disposition: form-data; name=""action""\r\n\r\n");
    data.append("testuploads.php\r\n"); //our script's name, as I understood. Please, correct me if I'm wrong
    data.append("--" + bound + "\r\n"); //according to rfc 1867
    data.append("Content-Disposition: form-data; name=""uploaded""; filename=""1.jpg""\r\n"); //name of the input is "uploaded" in my form, next one is a file name.
    data.append("Content-Type: image/jpeg\r\n\r\n"); //data type
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    return;
    data.append(file.readAll()); //let's read the file
    data.append("\r\n");
    data.append("--" + bound + "--\r\n"); //closing boundary according to rfc 1867
    request.setRawHeader(QString("Content-Type").toLatin1(),QString("multipart/form-data; boundary=" + bound).toLatin1());
    request.setRawHeader(QString("Content-Length").toLatin1(), QString::number(data.length()).toLatin1());
    ////this->reply = am->post(request,data);

   // connect(this->reply, SIGNAL(finished()), this, SLOT(replyFinished()))
}

QPixmap Editprofile::getProfilePicture()
{
    QNetworkAccessManager *nam = new QNetworkAccessManager;
    QString picurl = "http://103.29.85.127/images/profile/";
    int uid = user->getID();
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
        if(ui->editprofile_maleCheckBox->isChecked())
        {
            profile->setGender("M");
        }
        if(ui->editprofile_femaleCheckBox->isChecked())
        {
            profile->setGender("F");
        }
        QString lastName = ui->editprofile_lnameLineEdit->text();
        QString firstName = ui->editprofile_fnameLineEdit->text();
        QString email = ui->editprofile_emailLineEdit->text();

        profile->setFirstName(firstName);
        profile->setLastName(lastName);
        profile->setEmail(email);
        if(updateUser(*profile))
        {
            QMessageBox::about(this, "Edit profile","Edit successfully");
        }

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
    //changePWD = new ChangePassword (ID, this);
    //changePWD->show();
    //hide();
}
