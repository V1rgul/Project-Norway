#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T18:27:13
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetNorvege
TEMPLATE = app

win32:QMAKE_LFLAGS+=/INCREMENTAL:NO



SOURCES += main.cpp\
        mainwindow.cpp \
    abstractcameramanager.cpp \
    testcameramanager.cpp \
    abstractcamera.cpp \
    testcamera.cpp \
    emptycameramanager.cpp \
    cameraproperty.cpp \
    qvideowidget.cpp \
    flycameramanager.cpp \
    flycamera.cpp \
    iscamera.cpp \
    iscameramanager.cpp

HEADERS  += mainwindow.h \
    abstractcameramanager.h \
    testcameramanager.h \
    abstractcamera.h \
    testcamera.h \
    emptycameramanager.h \
    qvideowidget.h \
    flycameramanager.h \
    flycamera.h \
    iscamera.h \
    iscameramanager.h \
    cameraproperty.h

FORMS    += \
    mainwindow.ui

OTHER_FILES += \
    ../../../../usr/lib/libflycapture.so

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lflycapture
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lflycapture
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lflycapture

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
RESOURCES += \
    Ressources.qrc
