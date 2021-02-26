#ifndef REPORTRATETRACKER_H
#define REPORTRATETRACKER_H

#include <QList>
#include <QTimer>
#include <QWidget>

namespace Ui {
    class ReportRateTracker;
}

class QElapsedTimer;

class ReportRateTracker : public QWidget
{
    Q_OBJECT

public:
    explicit ReportRateTracker(QWidget *parent = nullptr);
    ~ReportRateTracker();

public slots:
    void canvasEvent(const QEvent *event);

private:
    void updateRates();

    Ui::ReportRateTracker *ui;

    QTimer mUpdateTimer;

    QTabletEvent *mLastHoverEvent = nullptr;
    QTabletEvent *mLastPressEvent = nullptr;
    QList<QElapsedTimer> mHoverQueue;
    QList<QElapsedTimer> mPressQueue;

    int mMaxHoverRate = 0;
    int mMaxPressRate = 0;

    static const QString cLabelTemplate;
};

#endif // REPORTRATETRACKER_H
