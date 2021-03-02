#include "pressureleveltester.h"
#include "ui_pressureleveltester.h"

#include <QSplineSeries>
#include <QTabletEvent>
#include <QtCharts>

PressureLevelTester::PressureLevelTester(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PressureLevelTester)
{
    ui->setupUi(this);

    mObservedPressures.insert(0.);

    mDataSeries = new QSplineSeries();
    mDataSeries->append(0, 0);
    mDataSeries->append(1, 1);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(mDataSeries);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
    chartView->sizePolicy().setVerticalStretch(1);
    chartView->setMinimumSize(300, 200);

    ui->gridLayout->addWidget(chartView, 0, 1);
}

PressureLevelTester::~PressureLevelTester()
{
    delete ui;
}

void PressureLevelTester::canvasEvent(const QEvent *event)
{
    if(event->type() == QEvent::TabletMove) {
        qreal pressure = static_cast<const QTabletEvent *>(event)->pressure();
        if(mObservedPressures.find(pressure) == mObservedPressures.end()) {
            mObservedPressures.insert(pressure);
            ui->pressureLevels->setText(QString("<h1>%1</h1>").arg(mObservedPressures.size()));
        }
    }
    else if(event->type() == QEvent::TabletRelease) {
        updateDataSeries();
    }
}

void PressureLevelTester::updateDataSeries()
{
    mDataSeries->clear();
    if(mObservedPressures.size() < 2) return;
    qreal currentX = 0;
    qreal xIncrement = 1. / (mObservedPressures.size() - 1);
    for(qreal pressure : mObservedPressures) {
        mDataSeries->append(currentX, pressure);
        currentX += xIncrement;
    }
}
