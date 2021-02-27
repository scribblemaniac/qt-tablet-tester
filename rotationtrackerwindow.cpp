#include "rotationtrackerwindow.h"

#include "rotationtracker.h"
#include "ui_canvaswindow.h"

RotationTrackerWindow::RotationTrackerWindow(QWidget *parent) :
    CanvasWindow(parent),
    mRotationTracker(new RotationTracker)
{
    ui->verticalLayout->addWidget(mRotationTracker);

    setWindowTitle("Stylus Rotation Tracker");

    connect(ui->canvas, &Canvas::canvasEvent, mRotationTracker, &RotationTracker::canvasEvent);
}
