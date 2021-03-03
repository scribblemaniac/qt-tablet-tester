#include "rotationtracker.h"
#include "ui_rotationtracker.h"

#include <QTabletEvent>

#include <cmath>

RotationTracker::RotationTracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RotationTracker)
{
    ui->setupUi(this);
}

RotationTracker::~RotationTracker()
{
    delete ui;
}

void RotationTracker::canvasEvent(const QEvent *event)
{
    if(event->type() == QEvent::TabletMove) {
        const QTabletEvent *tabletEvent = static_cast<const QTabletEvent *>(event);
        qreal rotation = fmod(fmod(tabletEvent->rotation(), 360) + 360, 360);
        ui->degreeDial->setValue(rotation - 180);
        ui->degreeLabel->setText(QString("<h1>%1</h1>").arg(tr("%1°", "RotationTracker").arg(QString::number(rotation, 'f', 2))));
    }
}
