#ifndef ROTATIONTRACKER_H
#define ROTATIONTRACKER_H

#include <QWidget>

namespace Ui {
    class RotationTracker;
}

class RotationTracker : public QWidget
{
    Q_OBJECT

public:
    explicit RotationTracker(QWidget *parent = nullptr);
    ~RotationTracker();

public slots:
    void canvasEvent(const QEvent *event);

private:
    Ui::RotationTracker *ui;
};

#endif // ROTATIONTRACKER_H
