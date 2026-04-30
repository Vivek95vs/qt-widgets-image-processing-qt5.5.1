#-------------------------------------------------
#
# Project created by QtCreator 2024-11-13T13:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageJ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS    += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib" \
            -lopencv_world300\
            -lopencv_ts300
