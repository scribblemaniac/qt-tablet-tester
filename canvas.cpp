#include "canvas.h"

#include <QLabel>
#include <QPainter>
#include <QPixmap>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    mCanvas(new QPixmap(size()))
{
    setAttribute(Qt::WA_StaticContents);

    mCanvas->fill(Qt::red);
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
    newCanvas->fill(qRgba(qMin(size().width()/2, 255), 255, qMin(size().height()/2, 255), 255));

    QPainter painter(newCanvas.get());
    painter.drawPixmap(QPoint(0,0), *mCanvas);

    newCanvas.swap(mCanvas);
}
