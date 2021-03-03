#include "eventlogger.h"
#include "ui_eventlogger.h"

#include <QClipboard>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTabletEvent>

EventLogger::EventLogger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventLogger)
{
    ui->setupUi(this);

    QFont monoFont("Monospace");
    monoFont.setStyleHint(QFont::TypeWriter);
    ui->log->setFont(monoFont);

    connect(ui->copyButton, &QPushButton::pressed, this, &EventLogger::copy);
    connect(ui->saveButton, &QPushButton::pressed, this, &EventLogger::save);

    mSaveLocation = QDir(QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()).filePath("TabletEvents.log");

    // Initialize Enum -> QString mappings

    cTypeMap[QEvent::TabletMove] = "TabletMove";
    cTypeMap[QEvent::TabletPress] = "TabletPress";
    cTypeMap[QEvent::TabletRelease] = "TabletRelease";
    cTypeMap[QEvent::TabletEnterProximity] = "TabletEnterProximity";
    cTypeMap[QEvent::TabletLeaveProximity] = "TabletLeaveProximity";

    cMouseButtonMap[Qt::NoButton] = "NoButton";
    cMouseButtonMap[Qt::AllButtons] = "AllButtons";
    cMouseButtonMap[Qt::LeftButton] = "LeftButton";
    cMouseButtonMap[Qt::RightButton] = "RightButton";
    cMouseButtonMap[Qt::MiddleButton] = "MiddleButton";
    cMouseButtonMap[Qt::BackButton] = "BackButton";
    cMouseButtonMap[Qt::ForwardButton] = "ForwardButton";
    cMouseButtonMap[Qt::TaskButton] = "TaskButton";
    cMouseButtonMap[Qt::ExtraButton4] = "ExtraButton4";
    cMouseButtonMap[Qt::ExtraButton5] = "ExtraButton5";
    cMouseButtonMap[Qt::ExtraButton6] = "ExtraButton6";
    cMouseButtonMap[Qt::ExtraButton7] = "ExtraButton7";
    cMouseButtonMap[Qt::ExtraButton8] = "ExtraButton8";
    cMouseButtonMap[Qt::ExtraButton9] = "ExtraButton9";
    cMouseButtonMap[Qt::ExtraButton10] = "ExtraButton10";
    cMouseButtonMap[Qt::ExtraButton11] = "ExtraButton11";
    cMouseButtonMap[Qt::ExtraButton12] = "ExtraButton12";
    cMouseButtonMap[Qt::ExtraButton13] = "ExtraButton13";
    cMouseButtonMap[Qt::ExtraButton14] = "ExtraButton14";
    cMouseButtonMap[Qt::ExtraButton15] = "ExtraButton15";
    cMouseButtonMap[Qt::ExtraButton16] = "ExtraButton16";
    cMouseButtonMap[Qt::ExtraButton17] = "ExtraButton17";
    cMouseButtonMap[Qt::ExtraButton18] = "ExtraButton18";
    cMouseButtonMap[Qt::ExtraButton19] = "ExtraButton19";
    cMouseButtonMap[Qt::ExtraButton20] = "ExtraButton20";
    cMouseButtonMap[Qt::ExtraButton21] = "ExtraButton21";
    cMouseButtonMap[Qt::ExtraButton22] = "ExtraButton22";
    cMouseButtonMap[Qt::ExtraButton23] = "ExtraButton23";
    cMouseButtonMap[Qt::ExtraButton24] = "ExtraButton24";

    cPointerTypeMap[QTabletEvent::UnknownPointer] = "UnknownPointer";
    cPointerTypeMap[QTabletEvent::Pen] = "Pen";
    cPointerTypeMap[QTabletEvent::Cursor] = "Cursor";
    cPointerTypeMap[QTabletEvent::Eraser] = "Eraser";

    cTabletDeviceMap[QTabletEvent::NoDevice] = "NoDevice";
    cTabletDeviceMap[QTabletEvent::Puck] = "Puck";
    cTabletDeviceMap[QTabletEvent::Stylus] = "Stylus";
    cTabletDeviceMap[QTabletEvent::Airbrush] = "Airbrush";
    cTabletDeviceMap[QTabletEvent::FourDMouse] = "FourDMouse";
    cTabletDeviceMap[QTabletEvent::RotationStylus] = "RotationStylus";
}

EventLogger::~EventLogger()
{
    delete ui;
}

void EventLogger::showEvent(QShowEvent *event)
{
    if(!event->spontaneous()) {
        mTimer.start();
    }
}

void EventLogger::canvasEvent(const QEvent *event)
{
    QString eventName;
    QStringList eventData;
    switch(event->type()) {
        case QEvent::TabletMove:
        case QEvent::TabletPress:
        case QEvent::TabletRelease:
        case QEvent::TabletEnterProximity:
        case QEvent::TabletLeaveProximity: {
            const QTabletEvent *tabletEvent = static_cast<const QTabletEvent *>(event);
            eventName = "QTabletEvent";

            eventData << QString("Type=").append(cTypeMap[event->type()])
                      << QString("UniqueId=%1").arg(tabletEvent->uniqueId());
            if(cTabletDeviceMap.contains(tabletEvent->device())) {
                eventData << QString("DeviceType=").append(cTabletDeviceMap[tabletEvent->device()]);
            }
            else {
                eventData << QString("DeviceType=UnknownDevice[%1]").arg(tabletEvent->device());
            }
            if(cPointerTypeMap.contains(tabletEvent->pointerType())) {
                eventData << QString("PointerType=").append(cPointerTypeMap[tabletEvent->pointerType()]);
            }
            else {
                eventData << QString("PointerType=UnknownPointer[%1]").arg(tabletEvent->pointerType());
            }

            if(cMouseButtonMap.contains(tabletEvent->button())) {
                eventData << QString("Button=").append(cMouseButtonMap[tabletEvent->button()]);
            }
            else {
                eventData << QString("Button=").append(QString("UnknownButton[0x%1]").arg(tabletEvent->button(), 8, 16, QLatin1Char('0')));
            }
            if(!tabletEvent->buttons()) {
                eventData << QString("Buttons=").append(cMouseButtonMap[Qt::NoButton]);
            }
            else {
                QStringList buttonsData;
                Qt::MouseButtons foundButtons;
                for(Qt::MouseButton buttonType : cMouseButtonMap.keys()) {
                    if(buttonType == Qt::NoButton || buttonType == Qt::AllButtons) continue;
                    if(tabletEvent->buttons().testFlag(buttonType)) {
                        buttonsData << cMouseButtonMap[buttonType];
                        foundButtons.setFlag(buttonType);
                    }
                }
                if(tabletEvent->buttons() != foundButtons) {
                    buttonsData << QString("UnknownButtons[0x%1]").arg(tabletEvent->buttons()^foundButtons, 8, 16, QLatin1Char('0'));
                }
                eventData << QString("Buttons=[%1]").arg(buttonsData.join(','));
            }

            eventData << QString("GlobalPos=[%1,%2]").arg(tabletEvent->globalPos().x()).arg(tabletEvent->globalPos().y())
                      << QString("GlobalPosF=[%1,%2]").arg(tabletEvent->globalPosF().x()).arg(tabletEvent->globalPosF().y())
                      << QString("GlobalX=%1").arg(tabletEvent->globalX()) << QString("GlobalY=%1").arg(tabletEvent->globalY())
                      << QString("Pos=[%1,%2]").arg(tabletEvent->pos().x()).arg(tabletEvent->pos().y())
                      << QString("PosF=[%1,%2]").arg(tabletEvent->posF().x()).arg(tabletEvent->posF().y())
                      << QString("X=%1").arg(tabletEvent->x()) << QString("Y=%1").arg(tabletEvent->y()) << QString("Z=%1").arg(tabletEvent->z());

            eventData << QString("Pressure=%1").arg(tabletEvent->pressure())
                      << QString("Rotation=%1").arg(tabletEvent->rotation())
                      << QString("TangentialPressure=%1").arg(tabletEvent->tangentialPressure())
                      << QString("XTilt=%1").arg(tabletEvent->xTilt())
                      << QString("YTilt=%1").arg(tabletEvent->yTilt());

            break;
        }
        default: {
            return;
        }
    }
    ui->log->append(QString("[%1] ").arg(mTimer.elapsed()).append(eventData.join(',')));
}

void EventLogger::copy()
{
    QGuiApplication::clipboard()->setText(ui->log->toPlainText());
}

void EventLogger::save()
{
    QString savePath = QFileDialog::getSaveFileName(this, tr("Save Event Log"), mSaveLocation);
    if(!savePath.isEmpty()) {
        QFile saveFile(savePath);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file, cannot save logs.", "EventLogger"));
            return;
        }
        saveFile.write(ui->log->toPlainText().toUtf8());
        mSaveLocation = savePath;
    }
}
