#include "report.h"
#include "ui_report.h"
#include <QDebug>

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    reset();

}

Report::~Report()
{
    delete ui;
}

void Report::reset()
{
    bugsReported = 0;
    bugsResolved = 0;
    bestBugReporter.clear();
    bestDevelopers.clear();
    bestReviewers.clear();
    ui->report_BugReportedDateEnd->setDate(QDate::currentDate());
     ui->report_BugResolvedDateEnd->setDate(QDate::currentDate());
}
void Report::setText()
{
    QString html;
    bestDevelopers = getBestDevelopers();
    bestReviewers = getBestReviewers();
    bestBugReporter = getBestReporters();

    html += "<h1> Bug Report </h1><br><br>";
    html += "<h2> Bugs Reported</h2><br>";
    html += "\tBetween \t" + ui->report_BugReportedDateStart->date().toString("dd-MM-yyyy");
    html += "\tAnd \t" + ui->report_BugReportedDateEnd->date().toString("dd-MM-yyyy");
    html += "<br>";
    html += QString::number(getBugsReportedBetween(ui->report_BugReportedDateStart->date(), ui->report_BugReportedDateEnd->date()));
    html += "<br>";
    html += "<br><h2>Bug Resolved</h2><br>";
    html += "\tBetween \t" + ui->report_BugResolvedDateStart->date().toString("dd-MM-yyyy");
    html += "\tAnd \t" + ui->report_BugResolvedDateEnd->date().toString("dd-MM-yyyy");
    html += "<br>";
    html += QString::number(getBugsResolvedBetween(ui->report_BugReportedDateStart->date(), ui->report_BugReportedDateEnd->date()));
    html += "<br>";
    html += "<br><br><h2> Top 10 Reporters</h2><br>";
    for(QPair<QString, int> pair: bestBugReporter)
    {
        html += pair.first;
        html += "\t";
        html += QString::number(pair.second);
        html += "<br>";
    }
    html += "<br><br><h2> Top 10 Developers</h2><br>";
    for(QPair<QString, int> pair: bestDevelopers)
    {
        html += pair.first;
        html += "\t";
        html += QString::number(pair.second);
        html += "<br>";
    }
    html += "<br><br><h2> Top 10 Reviewers</h2><br>";
    for(QPair<QString, int> pair : bestReviewers)
    {
        html += pair.first;
        html += "\t";
        html += QString::number(pair.second);
        html += "<br>";
    }


    ui->report_HTML->setText(html);


}

void Report::on_report_GenerateButton_clicked()
{
    setText();
}
