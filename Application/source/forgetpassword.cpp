#include "forgetpassword.h"
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
