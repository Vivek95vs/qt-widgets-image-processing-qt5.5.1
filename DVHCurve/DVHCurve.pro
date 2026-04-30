#-------------------------------------------------
#
# Project created by QtCreator 2023-08-19T12:26:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DVHCurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        qcustomplot.cpp

HEADERS  += mainwindow.h\
            qcustomplot.h

FORMS    += mainwindow.ui
