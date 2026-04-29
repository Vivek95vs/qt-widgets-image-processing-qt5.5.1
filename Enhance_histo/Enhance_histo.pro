#-------------------------------------------------
#
# Project created by QtCreator 2021-08-28T18:01:44
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Enhance_histo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageenhancementnew.cpp

HEADERS  += mainwindow.h \
    imageenhancementnew.h

FORMS    += mainwindow.ui

win32: LIBS += "AdvAPI32.lib"
win32: LIBS +="Shell32.lib"

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS   += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib"\
           -lopencv_world300\
           -lopencv_ts300\

