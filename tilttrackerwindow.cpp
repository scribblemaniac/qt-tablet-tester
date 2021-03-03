#include "tilttrackerwindow.h"

#include "tilttracker.h"
#include "ui_canvaswindow.h"

TiltTrackerWindow::TiltTrackerWindow(QWidget *parent) :
    CanvasWindow(parent),
    mTiltTracker(new TiltTracker)
{
    ui->verticalLayout->addWidget(mTiltTracker);

    setWindowTitle(tr("Stylus Tilt Tracker"));

    connect(ui->canvas, &Canvas::canvasEvent, mTiltTracker, &TiltTracker::canvasEvent);
}
