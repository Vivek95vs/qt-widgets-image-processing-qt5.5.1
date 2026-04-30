#-------------------------------------------------
#
# Project created by QtCreator 2023-10-04T07:20:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Resample2d
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


LIBS +=-lShell32
LIBS += -lAdvapi32

DEFINES -= UNICODE
LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\DCMTK_Release\\include"
LIBS    += -L"D:\\TKs\\LibsForGRAY\\DCMTK_Release\\lib"\
-ldcmtract\
-ldcmwlm\
-li2d\
-lijg8\
-lijg12\
-lijg16\
-loflog\
-lofstd\
-lcharls\
-lcmr\
-ldcmdata\
-ldcmdsig\
-ldcmfg\
-ldcmimage\
-ldcmimgle\
-ldcmiod\
-ldcmjpeg\
-ldcmjpls\
-ldcmnet\
-ldcmpmap\
-ldcmpstat\
-ldcmqrdb\
-ldcmrt\
-ldcmseg\
-ldcmsr\
-ldcmtls
