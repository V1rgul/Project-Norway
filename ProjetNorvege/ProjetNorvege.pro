#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T18:27:13
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetNorvege
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp \
    abstractcameramanager.cpp \
    testcameramanager.cpp \
    abstractcamera.cpp \
    testcamera.cpp \
    emptycameramanager.cpp \
    cameraproperty.cpp

HEADERS  += mainwindow.h \
    abstractcameramanager.h \
    testcameramanager.h \
    abstractcamera.h \
    testcamera.h \
    emptycameramanager.h \
    cameraproperty.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    Ressources.qrc
