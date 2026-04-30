#-------------------------------------------------
#
# Project created by QtCreator 2021-05-15T10:19:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Recta_Rotate2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp \
    customitem.cpp \
    myitem.cpp \
    resizeritem.cpp \
    applogger.cpp

HEADERS  += mainwindow.h \
    customscene.h \
    customitem.h \
    myitem.h \
    resizeritem.h \
    applogger.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
