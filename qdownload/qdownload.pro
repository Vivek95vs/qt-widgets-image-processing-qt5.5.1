#-------------------------------------------------
#
# Project created by QtCreator 2022-09-30T14:54:12
#
#-------------------------------------------------

QT       += core gui
QT       += network


DEFINES  += QT_NO_SSL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qdownload
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
