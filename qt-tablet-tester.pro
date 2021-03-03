QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT += charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    canvaswindow.cpp \
    eventlogger.cpp \
    eventloggerwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    pressureleveltester.cpp \
    pressureleveltesterwindow.cpp \
    reportratetracker.cpp \
    reportratetrackerwindow.cpp \
    rotationtracker.cpp \
    rotationtrackerwindow.cpp \
    tiltindicator.cpp \
    tilttracker.cpp \
    tilttrackerwindow.cpp

HEADERS += \
    canvas.h \
    canvaswindow.h \
    eventlogger.h \
    eventloggerwindow.h \
    mainwindow.h \
    pressureleveltester.h \
    pressureleveltesterwindow.h \
    reportratetracker.h \
    reportratetrackerwindow.h \
    rotationtracker.h \
    rotationtrackerwindow.h \
    tiltindicator.h \
    tilttracker.h \
    tilttrackerwindow.h

FORMS += \
    canvaswindow.ui \
    eventlogger.ui \
    mainwindow.ui \
    pressureleveltester.ui \
    reportratetracker.ui \
    rotationtracker.ui \
    tilttracker.ui

TRANSLATIONS += \
    qt-tablet-tester_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
