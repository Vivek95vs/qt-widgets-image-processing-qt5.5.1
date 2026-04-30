#-------------------------------------------------
#
# Project created by QtCreator 2024-05-06T12:23:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelCorrection
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



# openCV
INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS    += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib" \
            -lopencv_world300\
            -lopencv_ts300
