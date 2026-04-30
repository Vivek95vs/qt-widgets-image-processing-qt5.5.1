#-------------------------------------------------
#
# Project created by QtCreator 2021-04-01T14:50:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tut-WidOpen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:\\Workflow\\Work\\Opencv\\include \

LIBS += -LD:\\Workflow\\Work\\Opencv\\x64\\vc12\\lib \
        -lopencv_ts300 \
        -lopencv_ts300d \
        -lopencv_world300 \
        -lopencv_world300d
