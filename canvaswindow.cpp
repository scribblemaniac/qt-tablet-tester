#include "canvaswindow.h"
#include "ui_canvaswindow.h"

#include "canvas.h"

#include <QLayout>

CanvasWindow::CanvasWindow(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::CanvasWindow)
{
    ui->setupUi(this);
}

CanvasWindow::~CanvasWindow()
{
    delete ui;
}
