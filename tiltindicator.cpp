#include "tiltindicator.h"

#include <QDebug>
#include <QPainter>

TiltIndicator::TiltIndicator(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(100, 100);
}

void TiltIndicator::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QPoint center = rect().center();
    const int squareLength = qMin(width(), height());
    QPoint xOffset(squareLength / 2, 0),
           yOffset(0, squareLength / 2);

    // Draw axes
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(center - xOffset, center + xOffset);
    painter.drawLine(center - yOffset, center + yOffset);

    // Draw tick marks
    QPoint minorTickMarkX(0, 5),
           majorTickMarkX(0, 10),
           minorTickMarkY(minorTickMarkX.transposed()),
           majorTickMarkY(majorTickMarkX.transposed());
    const int tickMarkCount = squareLength >= 250 ? 10 : 4;
    const int majorTickMarkInterval = squareLength >= 250 ? 5 : 2;
    for(int i = 1; i <= tickMarkCount; i++) {
        if(i % majorTickMarkInterval == 0) {
            painter.drawLine(center - (i * xOffset) / tickMarkCount - majorTickMarkX, center - (i * xOffset) / tickMarkCount + majorTickMarkX);
            painter.drawLine(center + (i * xOffset) / tickMarkCount - majorTickMarkX, center + (i * xOffset) / tickMarkCount + majorTickMarkX);
            painter.drawLine(center - (i * yOffset) / tickMarkCount - majorTickMarkY, center - (i * yOffset) / tickMarkCount + majorTickMarkY);
            painter.drawLine(center + (i * yOffset) / tickMarkCount - majorTickMarkY, center + (i * yOffset) / tickMarkCount + majorTickMarkY);
        }
        else {
            painter.drawLine(center - (i * xOffset) / tickMarkCount - minorTickMarkX, center - (i * xOffset) / tickMarkCount + minorTickMarkX);
            painter.drawLine(center + (i * xOffset) / tickMarkCount - minorTickMarkX, center + (i * xOffset) / tickMarkCount + minorTickMarkX);
            painter.drawLine(center - (i * yOffset) / tickMarkCount - minorTickMarkY, center - (i * yOffset) / tickMarkCount + minorTickMarkY);
            painter.drawLine(center + (i * yOffset) / tickMarkCount - minorTickMarkY, center + (i * yOffset) / tickMarkCount + minorTickMarkY);
        }
    }

    // Draw arrow
    if(mXTilt == 0 && mYTilt == 0) {
        painter.drawEllipse(center, 1, 1);
    }
    else {
        painter.setPen(QPen(Qt::blue, 2));
        QPoint arrowEndpoint(squareLength / 2 * mXTilt / 60, squareLength / 2 * mYTilt / 60);
        painter.drawLine(center, center + arrowEndpoint);
    }

    // Draw range
    if(mMaxArea.isValid()) {
        painter.setPen(QPen(Qt::green, 2));
        painter.setBrush(QBrush(QColor(0, 255, 0, 90)));

        QRect minRect = QRect(center + QPoint(squareLength / 2 * mMinArea.left() / 60, squareLength / 2 * mMinArea.top() / 60),
                              center + QPoint(squareLength / 2 * mMinArea.right() / 60, squareLength / 2 * mMinArea.bottom() / 60));

        if(mMaxArea.contains(mMinArea)) {
            QRegion r1(rect()), r2(minRect);
            painter.setClipRegion(r1.subtracted(r2));
            painter.setClipping(true);
        }

        painter.drawRect(QRect(center + QPoint(squareLength / 2 * mMaxArea.left() / 60, squareLength / 2 * mMaxArea.top() / 60),
                                    center + QPoint(squareLength / 2 * mMaxArea.right() / 60, squareLength / 2 * mMaxArea.bottom() / 60)));

        if(mMaxArea.contains(mMinArea)) {
            painter.setClipping(false);
            painter.setPen(QPen(Qt::green, 2));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(minRect);
        }
    }
}

void TiltIndicator::setTilt(int xAngle, int yAngle)
{
    mXTilt = xAngle;
    mYTilt = yAngle;

    update();
}

void TiltIndicator::setTiltX(int angle)
{
    mXTilt = angle;

    update();
}

void TiltIndicator::setTiltY(int angle)
{
    mYTilt = angle;

    update();
}

void TiltIndicator::setMinArea(QRect area)
{
    mMinArea = area;

    update();
}

void TiltIndicator::setMaxArea(QRect area)
{
    mMaxArea = area;

    update();
}
