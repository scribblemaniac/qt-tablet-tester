#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "canvaswindow.h"
#include "eventloggerwindow.h"
#include "pressureleveltesterwindow.h"
#include "reportratetrackerwindow.h"
#include "rotationtrackerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString versionStr = getVersionString();

    setWindowTitle(windowTitle().arg(versionStr));
    ui->title->setText(ui->title->text().arg(versionStr));

    connect(ui->pressureLevelButton, &QPushButton::pressed, this, &MainWindow::openPressureLevelTester);
    connect(ui->reportRateButton, &QPushButton::pressed, this, &MainWindow::openReportRateTracker);
    connect(ui->rotationButton, &QPushButton::pressed, this, &MainWindow::openRotationTracker);
    connect(ui->eventLoggerButton, &QPushButton::pressed, this, &MainWindow::openEventLogger);
    connect(ui->freeDrawButton, &QPushButton::pressed, this, &MainWindow::openFreeDraw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getVersionString()
{
    // App version

    // TODO

    // Qt version
    QString compileQtVersion = QT_VERSION_STR;
    QString runtimeQtVersion = qVersion();

    QString versionString;

    if(compileQtVersion == runtimeQtVersion) {
        versionString.append(compileQtVersion);
    }
    else {
        versionString = versionString.append("%1ct %2rt").arg(compileQtVersion, runtimeQtVersion);
    }

    // Modifed/Umodifed Qt?

    return versionString;
}

void MainWindow::openPressureLevelTester()
{
    PressureLevelTesterWindow *window = new PressureLevelTesterWindow(this);
    window->show();
}

void MainWindow::openReportRateTracker()
{
    ReportRateTrackerWindow *window = new ReportRateTrackerWindow(this);
    window->show();
}

void MainWindow::openRotationTracker()
{
    RotationTrackerWindow *window = new RotationTrackerWindow(this);
    window->show();
}

void MainWindow::openEventLogger()
{
    EventLoggerWindow *window = new EventLoggerWindow(this);
    window->show();
}

void MainWindow::openFreeDraw()
{
    CanvasWindow *window = new CanvasWindow(this);
    window->setWindowTitle("Free Draw");
    window->show();
}

