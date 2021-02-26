#ifndef REPORTRATETRACKERWINDOW_H
#define REPORTRATETRACKERWINDOW_H

#include "canvaswindow.h"

class ReportRateTracker;

class ReportRateTrackerWindow : public CanvasWindow
{
    Q_OBJECT
public:
    ReportRateTrackerWindow(QWidget *parent = nullptr);

private:
    ReportRateTracker *mReportRateTracker;
};

#endif // REPORTRATETRACKERWINDOW_H
