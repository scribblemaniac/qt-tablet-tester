#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <QElapsedTimer>
#include <QEvent>
#include <QTabletEvent>
#include <QWidget>

namespace Ui {
    class EventLogger;
}

class EventLogger : public QWidget
{
    Q_OBJECT

public:
    explicit EventLogger(QWidget *parent = nullptr);
    ~EventLogger();

public slots:
    void showEvent(QShowEvent *event) override;

    void canvasEvent(const QEvent *event);

protected slots:
    void copy();
    void save();

private:
    Ui::EventLogger *ui;

    QElapsedTimer mTimer;
    QString mSaveLocation;

    // TODO make const static
    QHash<QEvent::Type, QString> cTypeMap;
    QHash<Qt::MouseButton, QString> cMouseButtonMap;
    QHash<Qt::MouseEventFlag, QString> cMouseFlagMap;
    QHash<Qt::MouseEventSource, QString> cMouseSourceMap;
    QHash<QTabletEvent::PointerType, QString> cPointerTypeMap;
    QHash<QTabletEvent::TabletDevice, QString> cTabletDeviceMap;
};

#endif // EVENTLOGGER_H
