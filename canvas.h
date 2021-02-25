#ifndef CANVAS_H
#define CANVAS_H

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

private:
    std::unique_ptr<QPixmap> mCanvas;
};

#endif // CANVAS_H
