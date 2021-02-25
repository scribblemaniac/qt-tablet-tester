#ifndef CANVAS_H
#define CANVAS_H

#include <QPen>
#include <QWidget>

#include <memory>

class QPixmap;

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void tabletEvent(QTabletEvent *event) override;

private:
    std::unique_ptr<QPixmap> mCanvas;

    const int cPenWidth = 20;

    QPoint mPrevPos;
    QPen mPen;
    bool mIsDrawing = false;
};

#endif // CANVAS_H
