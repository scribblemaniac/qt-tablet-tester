#ifndef TILTTRACKER_H
#define TILTTRACKER_H

#include <QWidget>

namespace Ui {
    class TiltTracker;
}

class TiltTracker : public QWidget
{
    Q_OBJECT

public:
    explicit TiltTracker(QWidget *parent = nullptr);
    ~TiltTracker();

public slots:
    void canvasEvent(const QEvent *event);

private:
    Ui::TiltTracker *ui;

    QRect mMinArea, mMaxArea;
};

#endif // TILTTRACKER_H
