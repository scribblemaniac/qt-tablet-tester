#include "canvas.h"

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QTabletEvent>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    mCanvas(new QPixmap(size())),
    mPen(Qt::black, cPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
{
    setAttribute(Qt::WA_StaticContents);

    mCanvas->fill(Qt::transparent);
}

Canvas::~Canvas()
{
}

void Canvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *mCanvas);
}

void Canvas::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    std::unique_ptr<QPixmap> newCanvas(new QPixmap(size()));
    newCanvas->fill(Qt::transparent);

    QPainter painter(newCanvas.get());
    painter.drawPixmap(QPoint(0,0), *mCanvas);

    newCanvas.swap(mCanvas);
}

void Canvas::tabletEvent(QTabletEvent *event)
{
    if (event->type() == QEvent::TabletPress) {
        if(event->button() == Qt::LeftButton) {
            mPrevPos = event->pos();
            mIsDrawing = true;
        }
    }
    else if(event->type() == QEvent::TabletMove) {
        if(mIsDrawing) {
            QPoint newPos = event->pos();
            QPainter painter(mCanvas.get());
            painter.setPen(mPen);
            mPen.setWidth(cPenWidth * event->pressure());

            painter.drawLine(mPrevPos, newPos);

            mPrevPos = newPos;
            update();
        }
    }
    else if(event->type() == QEvent::TabletRelease) {
        mPrevPos = QPoint();
        mIsDrawing = false;
    }

    event->accept();
}

