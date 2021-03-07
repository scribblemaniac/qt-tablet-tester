#ifndef ROTATIONTRACKERWINDOW_H
#define ROTATIONTRACKERWINDOW_H

#include "canvaswindow.h"

class RotationTracker;

class RotationTrackerWindow : public CanvasWindow
{
    Q_OBJECT
public:
    RotationTrackerWindow(QWidget *parent = nullptr);

private:
    RotationTracker *mRotationTracker;
};

#endif // ROTATIONTRACKERWINDOW_H
