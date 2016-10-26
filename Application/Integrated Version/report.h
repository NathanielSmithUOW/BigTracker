#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include "user.h"
#include "database.h"

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = 0);
    ~Report();

private slots:
    void on_report_GenerateButton_clicked();

private:
    Ui::Report *ui;
    int bugsResolved;
    int bugsReported;
    QList<QPair<QString, int>> bestDevelopers;
    QList<QPair<QString, int>> bestBugReporter;
    QList<QPair<QString, int>> bestReviewers;

    void reset();
    void setText();
};

#endif // REPORT_H
