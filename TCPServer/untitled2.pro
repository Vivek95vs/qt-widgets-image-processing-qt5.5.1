#-------------------------------------------------
#
# Project created by QtCreator 2023-05-22T11:46:29
#
#-------------------------------------------------

QT       += core gui
QT     +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    client.h

FORMS    += mainwindow.ui
