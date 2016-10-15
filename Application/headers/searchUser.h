#ifndef SWINDOW_H
#define SWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class sWindow;
}

class sWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sWindow(QWidget *parent = 0);

    ~sWindow();

private slots:
    void on_lineEdit_returnPressed();
    void on_pushButton_clicked();



private:
    Ui::sWindow *ui;
};

#endif // SWINDOW_H
