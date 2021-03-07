QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT += charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/canvas.cpp \
    src/canvaswindow.cpp \
    src/eventlogger.cpp \
    src/eventloggerwindow.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pressureleveltester.cpp \
    src/pressureleveltesterwindow.cpp \
    src/reportratetester.cpp \
    src/reportratetesterwindow.cpp \
    src/rotationtracker.cpp \
    src/rotationtrackerwindow.cpp \
    src/tiltindicator.cpp \
    src/tilttracker.cpp \
    src/tilttrackerwindow.cpp

HEADERS += \
    src/canvas.h \
    src/canvaswindow.h \
    src/eventlogger.h \
    src/eventloggerwindow.h \
    src/mainwindow.h \
    src/pressureleveltester.h \
    src/pressureleveltesterwindow.h \
    src/reportratetester.h \
    src/reportratetesterwindow.h \
    src/rotationtracker.h \
    src/rotationtrackerwindow.h \
    src/tiltindicator.h \
    src/tilttracker.h \
    src/tilttrackerwindow.h

FORMS += \
    src/canvaswindow.ui \
    src/eventlogger.ui \
    src/mainwindow.ui \
    src/pressureleveltester.ui \
    src/reportratetester.ui \
    src/rotationtracker.ui \
    src/tilttracker.ui

TRANSLATIONS += \
    qt-tablet-tester_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
