#ifndef PRESSURELEVELTESTERWINDOW_H
#define PRESSURELEVELTESTERWINDOW_H

#include "canvaswindow.h"

class PressureLevelTester;

class PressureLevelTesterWindow : public CanvasWindow
{
    Q_OBJECT
public:
    PressureLevelTesterWindow(QWidget *parent = nullptr);

private:
    PressureLevelTester *mPressureLevelTester;
};

#endif // PRESSURELEVELTESTERWINDOW_H
