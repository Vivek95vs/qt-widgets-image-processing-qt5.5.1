#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T18:06:10
#
#-------------------------------------------------

QT       = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bitmap
TEMPLATE = app
CONFIG += qt warn_on
CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    paintdraw.cpp

HEADERS  += mainwindow.h \
    paintdraw.h

RESOURCES += \
    resource.qrc
