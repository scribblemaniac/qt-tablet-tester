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

    mCanvas->fill(cBackground);

    setMouseTracking(true); // reacts to mouse move events, even if the button is not pressed

#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    setTabletTracking(true);
#endif
}

Canvas::~Canvas()
{
}

bool Canvas::event(QEvent *event)
{
    emit canvasEvent(event);
    return QWidget::event(event);
}

void Canvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    // Draw strokes
    painter.drawPixmap(QPoint(0, 0), *mCanvas);

    // Draw border
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush());
    painter.drawRect(rect().adjusted(1, 1, -1, -1));
}

void Canvas::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    std::unique_ptr<QPixmap> newCanvas(new QPixmap(size()));
    newCanvas->fill(cBackground);

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
            update(); // TODO Update only affected area
        }
    }
    else if(event->type() == QEvent::TabletRelease) {
        mPrevPos = QPoint();
        mIsDrawing = false;
    }

    event->accept();
}

