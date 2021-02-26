#include "eventloggerwindow.h"
#include "ui_canvaswindow.h"

#include <eventlogger.h>

EventLoggerWindow::EventLoggerWindow(QWidget *parent) :
    CanvasWindow(parent),
    mEventLogger(new EventLogger)
{
    ui->verticalLayout->addWidget(mEventLogger);

    setWindowTitle("Event Logger");

    connect(ui->canvas, &Canvas::canvasEvent, mEventLogger, &EventLogger::canvasEvent);
}
