#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QDialog>

namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPassword(QWidget *parent = 0);
    ~ForgetPassword();

private slots:
    void on_forgotpassword_SubmitButton_clicked();

    void on_forgotpassword_CancelButton_clicked();

private:
    Ui::ForgetPassword *ui;
};

#endif // FORGETPASSWORD_H
