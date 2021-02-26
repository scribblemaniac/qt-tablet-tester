#include "reportratetrackerwindow.h"

#include "reportratetracker.h"
#include "ui_canvaswindow.h"

ReportRateTrackerWindow::ReportRateTrackerWindow(QWidget *parent) :
    CanvasWindow(parent),
    mReportRateTracker(new ReportRateTracker)
{
    ui->verticalLayout->addWidget(mReportRateTracker);

    setWindowTitle("Tablet Report Rate Tracker");

    connect(ui->canvas, &Canvas::canvasEvent, mReportRateTracker, &ReportRateTracker::canvasEvent);
}
