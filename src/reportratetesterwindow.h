#ifndef REPORTRATETESTERWINDOW_H
#define REPORTRATETESTERWINDOW_H

#include "canvaswindow.h"

class ReportRateTester;

class ReportRateTesterWindow : public CanvasWindow
{
    Q_OBJECT
public:
    ReportRateTesterWindow(QWidget *parent = nullptr);

private:
    ReportRateTester *mReportRateTester;
};

#endif // REPORTRATETESTERWINDOW_H
