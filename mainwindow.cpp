#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString versionStr = getVersionString();

    setWindowTitle(windowTitle().arg(versionStr));
    ui->title->setText(ui->title->text().arg(versionStr));
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

