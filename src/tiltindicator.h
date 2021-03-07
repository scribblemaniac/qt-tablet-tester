#ifndef TILTINDICATOR_H
#define TILTINDICATOR_H

#include <QWidget>

class TiltIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit TiltIndicator(QWidget *parent = nullptr);

public slots:
    void paintEvent(QPaintEvent* event) override;

    void setTilt(int xAngle, int yAngle);
    void setTiltX(int angle);
    void setTiltY(int angle);

    void setMinArea(QRect area);
    void setMaxArea(QRect area);

private:
    int mXTilt, mYTilt;

    QRect mMinArea, mMaxArea;
};

#endif // TILTINDICATOR_H
