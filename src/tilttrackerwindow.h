#ifndef TILTTRACKERWINDOW_H
#define TILTTRACKERWINDOW_H

#include "canvaswindow.h"

class TiltTracker;

class TiltTrackerWindow : public CanvasWindow
{
    Q_OBJECT
public:
    TiltTrackerWindow(QWidget *parent = nullptr);

private:
    TiltTracker *mTiltTracker;
};

#endif // TILTTRACKERWINDOW_H
