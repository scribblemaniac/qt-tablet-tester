#ifndef EVENTLOGGERWINDOW_H
#define EVENTLOGGERWINDOW_H

#include "canvaswindow.h"

class EventLogger;

class EventLoggerWindow : public CanvasWindow
{
    Q_OBJECT
public:
    EventLoggerWindow(QWidget *parent = nullptr);

private:
    EventLogger *mEventLogger;
};

#endif // EVENTLOGGERWINDOW_H
