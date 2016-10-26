#include "forgetpassword.h"
#include "database.h"
#include "ui_forgetpassword.h"

ForgetPassword::ForgetPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Forgot Password");
}

ForgetPassword::~ForgetPassword()
{
    delete ui;
}

void ForgetPassword::on_forgotpassword_SubmitButton_clicked()
{
    if(ui->forgotpassword_EmailLineEdit->text().isEmpty() || ui->forgotpassword_FirstNameLineEdit->text().isEmpty() || ui->forgotpassword_LastNameLineEdit->text().isEmpty() || ui->forgotpassword_UsernameLineEdit->text().isEmpty())
    {
         QMessageBox::warning(this, "Forgot Password","Some fields are Empty, please fill in all fields");
         return;
    }
    QString message = "User " + ui->forgotpassword_UsernameLineEdit->text();
    message += "\n has forgotten thier password, please reset and send to \n";
    message += ui->forgotpassword_EmailLineEdit->text();
    User *dev = getUserFromID(1);
    addNotificationToUser(*dev, message);
     QMessageBox::about(this, "Forgot Password","Password Reset Request Submitted, an email will be sent to you");
     close();
}

void ForgetPassword::on_forgotpassword_CancelButton_clicked()
{
    close();
}
