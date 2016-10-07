#ifndef VIEWBUG_H
#define VIEWBUG_H

#include <QMainWindow>

#include "viewbugcontroller.h"
#include "bug.h"


namespace Ui {
class ViewBug;
}

class ViewBug : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewBug(QWidget *parent = 0);
    ~ViewBug();
    void setBug();

private slots:
    void on_viewBug_ViewMoreButton_toggled(bool checked);

private:
    Ui::ViewBug *ui;
    Bug *b;


};

#endif // VIEWBUG_H
