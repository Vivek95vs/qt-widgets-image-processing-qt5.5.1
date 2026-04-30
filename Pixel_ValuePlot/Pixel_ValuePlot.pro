#-------------------------------------------------
#
# Project created by QtCreator 2021-09-02T12:59:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = Pixel_ValuePlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    disp_evt.cpp\
    qcustomplot.cpp \
    applogger.cpp

HEADERS  += mainwindow.h \
    disp_evt.h\
    qcustomplot.h \
    applogger.h

FORMS    += mainwindow.ui

LIBS += "AdvAPI32.lib"
LIBS +="Shell32.lib"

INCLUDEPATH +="D:\\TKs\\LibsForGRAY\\Opencv\\include"
LIBS   += -L"D:\\TKs\\LibsForGRAY\\Opencv\\x64\\vc12\\lib"\
           -lopencv_world300\
           -lopencv_ts300\
