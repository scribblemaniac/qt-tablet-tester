#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QString getVersionString();

private:
    void openPressureLevelTester();
    void openTiltTracker();
    void openReportRateTracker();
    void openRotationTracker();
    void openEventLogger();
    void openFreeDraw();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
