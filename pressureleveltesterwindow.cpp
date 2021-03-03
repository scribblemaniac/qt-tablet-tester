#include "pressureleveltesterwindow.h"

#include "pressureleveltester.h"
#include "ui_canvaswindow.h"

PressureLevelTesterWindow::PressureLevelTesterWindow(QWidget *parent) :
    CanvasWindow(parent),
    mPressureLevelTester(new PressureLevelTester)
{
    ui->verticalLayout->addWidget(mPressureLevelTester);

    setWindowTitle(tr("Tablet Pressure Level Tester"));

    connect(ui->canvas, &Canvas::canvasEvent, mPressureLevelTester, &PressureLevelTester::canvasEvent);
}
