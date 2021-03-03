#include "reportratetester.h"
#include "ui_reportratetester.h"

#include <QElapsedTimer>
#include <QTabletEvent>

const QString ReportRateTester::cLabelTemplate = tr("<h1>%1 Hz</h1><small>Peak: %2 Hz</small>");

ReportRateTester::ReportRateTester(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportRateTester),
    mUpdateTimer(this)
{
    ui->setupUi(this);

    connect(&mUpdateTimer, &QTimer::timeout, this, &ReportRateTester::updateRates);
    mUpdateTimer.start(200);
}

ReportRateTester::~ReportRateTester()
{
    delete ui;
    if(mLastHoverEvent) {
        delete mLastHoverEvent;
    }
    if(mLastPressEvent) {
        delete mLastPressEvent;
    }
}

// TODO Improve algorithm. Check all 1 second intervals for max, show average of 1 second intervals between updateRates calls.
void ReportRateTester::updateRates() {
    while(!mHoverQueue.isEmpty() && mHoverQueue.last().hasExpired(1000)) {
        mHoverQueue.removeLast();
    }
    mMaxHoverRate = qMax(mMaxHoverRate, mHoverQueue.count());
    ui->hoverReportRate->setText(cLabelTemplate.arg(mHoverQueue.count()).arg(mMaxHoverRate));

    while(!mPressQueue.isEmpty() && mPressQueue.last().hasExpired(1000)) {
        mPressQueue.removeLast();
    }
    mMaxPressRate = qMax(mMaxPressRate, mPressQueue.count());
    ui->pressReportRate->setText(cLabelTemplate.arg(mPressQueue.count()).arg(mMaxPressRate));
}

void ReportRateTester::canvasEvent(const QEvent *event)
{
    if(event->type() == QEvent::TabletMove) {
        const QTabletEvent *tabletEvent = static_cast<const QTabletEvent *>(event);
        QElapsedTimer time;
        time.start();
        if(!tabletEvent->buttons()) {
            if(!mLastHoverEvent ||
               tabletEvent->globalPosF() != mLastHoverEvent->globalPosF() ||
               tabletEvent->posF() != mLastHoverEvent->posF() ||
               tabletEvent->pressure() != mLastHoverEvent->pressure() ||
               tabletEvent->rotation() != mLastHoverEvent->rotation() ||
               tabletEvent->xTilt() != mLastHoverEvent->xTilt() ||
               tabletEvent->yTilt() != mLastHoverEvent->yTilt() ||
               tabletEvent->z() != mLastHoverEvent->z()) {
                mHoverQueue.prepend(time);
            }
            mLastHoverEvent = new QTabletEvent(*tabletEvent);
        }
        else {
            if(!mLastPressEvent ||
               tabletEvent->globalPosF() != mLastPressEvent->globalPosF() ||
               tabletEvent->posF() != mLastPressEvent->posF() ||
               tabletEvent->pressure() != mLastPressEvent->pressure() ||
               tabletEvent->rotation() != mLastPressEvent->rotation() ||
               tabletEvent->xTilt() != mLastPressEvent->xTilt() ||
               tabletEvent->yTilt() != mLastPressEvent->yTilt() ||
               tabletEvent->z() != mLastPressEvent->z()) {
                mPressQueue.prepend(time);
            }
            mLastPressEvent = new QTabletEvent(*tabletEvent);
        }
    }
}
