#ifndef REPORTRATETESTER_H
#define REPORTRATETESTER_H

#include <QList>
#include <QTimer>
#include <QWidget>

namespace Ui {
    class ReportRateTester;
}

class QElapsedTimer;

class ReportRateTester : public QWidget
{
    Q_OBJECT

public:
    explicit ReportRateTester(QWidget *parent = nullptr);
    ~ReportRateTester();

public slots:
    void canvasEvent(const QEvent *event);

private:
    void updateRates();
    void updateLabels();

    Ui::ReportRateTester *ui;

    QTimer mUpdateTimer;

    QTabletEvent *mLastHoverEvent = nullptr;
    QTabletEvent *mLastPressEvent = nullptr;
    QList<QElapsedTimer> mHoverQueue;
    QList<QElapsedTimer> mPressQueue;

    int mMaxHoverRate = 0;
    int mMaxPressRate = 0;

    static const QString cLabelTemplate;
};

#endif // REPORTRATETESTER_H
