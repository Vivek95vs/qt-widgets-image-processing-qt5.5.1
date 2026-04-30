#-------------------------------------------------
#
# Project created by QtCreator 2022-11-02T18:10:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wheel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mouse.cpp

HEADERS  += mainwindow.h \
    mouse.h

FORMS    += mainwindow.ui

#opencv
INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS   += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib"\
           -lopencv_world300\
           -lopencv_world300d\
           -lopencv_ts300\
           -lopencv_ts300d
