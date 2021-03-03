#include "tilttracker.h"
#include "ui_tilttracker.h"

#include <QTabletEvent>

TiltTracker::TiltTracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TiltTracker)
{
    ui->setupUi(this);

    mMinArea = QRect(QPoint(0, 0), QPoint(0, 0));
    mMaxArea = QRect(QPoint(0, 0), QSize(0, 0));
}

TiltTracker::~TiltTracker()
{
    delete ui;
}

void TiltTracker::canvasEvent(const QEvent *event)
{
    if(event->type() == QEvent::TabletMove) {
        const QTabletEvent *tabletEvent = static_cast<const QTabletEvent *>(event);
        int xTilt = tabletEvent->xTilt();
        int yTilt = tabletEvent->yTilt();
        if(xTilt == 0 && yTilt == 0) return;

        QPoint tiltPoint = QPoint(xTilt, yTilt);
        if(xTilt < 0) {
            mMinArea.setLeft(mMinArea.left() == 0 ? xTilt : qMax(mMinArea.left(), xTilt));
        }
        else if(xTilt > 0) {
            mMinArea.setRight(mMinArea.right() == 0 ? xTilt : qMin(mMinArea.right(), xTilt));
        }
        if(yTilt < 0) {
            mMinArea.setTop(mMinArea.top() == 0 ? yTilt : qMax(mMinArea.top(), yTilt));
        }
        else if(yTilt > 0) {
            mMinArea.setBottom(mMinArea.bottom() == 0 ? yTilt : qMin(mMinArea.bottom(), yTilt));
        }
        ui->tiltIndicator->setMinArea(mMinArea);
        if(!mMaxArea.contains(tiltPoint)) {
            mMaxArea = mMaxArea.united(QRect(QPoint(0,0), tiltPoint).normalized());
            ui->tiltIndicator->setMaxArea(mMaxArea);
        }

        ui->tiltX->setText(QString("<h1>%1°</h1>").arg(QString::number(xTilt, 'f', 2)));
        ui->tiltY->setText(QString("<h1>%1°</h1>").arg(QString::number(yTilt, 'f', 2)));

        ui->tiltIndicator->setTilt(xTilt, yTilt);
    }
}
