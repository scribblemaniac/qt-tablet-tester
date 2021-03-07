#ifndef PRESSURELEVELTESTER_H
#define PRESSURELEVELTESTER_H

#include <set>
#include <QWidget>

namespace Ui {
    class PressureLevelTester;
}

namespace QtCharts {
    class QSplineSeries;
}

class PressureLevelTester : public QWidget
{
    Q_OBJECT

public:
    explicit PressureLevelTester(QWidget *parent = nullptr);
    ~PressureLevelTester();

public slots:
    void canvasEvent(const QEvent *event);

private:
    void updateDataSeries();

    Ui::PressureLevelTester *ui;

    std::set<qreal> mObservedPressures;
    QtCharts::QSplineSeries* mDataSeries;
};

#endif // PRESSURELEVELTESTER_H
