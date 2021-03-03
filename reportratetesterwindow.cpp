#include "reportratetesterwindow.h"

#include "reportratetester.h"
#include "ui_canvaswindow.h"

ReportRateTesterWindow::ReportRateTesterWindow(QWidget *parent) :
    CanvasWindow(parent),
    mReportRateTester(new ReportRateTester)
{
    ui->verticalLayout->addWidget(mReportRateTester);

    setWindowTitle(tr("Tablet Report Rate Tester"));

    connect(ui->canvas, &Canvas::canvasEvent, mReportRateTester, &ReportRateTester::canvasEvent);
}
