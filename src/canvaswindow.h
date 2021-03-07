#ifndef CANVASWINDOW_H
#define CANVASWINDOW_H

#include <QWidget>

namespace Ui {
    class CanvasWindow;
}

class CanvasWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWindow(QWidget *parent = nullptr);
    ~CanvasWindow();

protected:
    Ui::CanvasWindow *ui;
};

#endif // CANVASWINDOW_H
