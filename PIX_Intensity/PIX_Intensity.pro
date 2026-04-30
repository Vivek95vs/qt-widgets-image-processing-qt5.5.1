#-------------------------------------------------
#
# Project created by QtCreator 2021-09-02T09:52:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIX_Intensity
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    disp_evt.cpp

HEADERS  += mainwindow.h \
    disp_evt.h

FORMS    += mainwindow.ui

LIBS += "AdvAPI32.lib"
LIBS +="Shell32.lib"

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS   += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib"\
           -lopencv_world300\
           -lopencv_ts300\
