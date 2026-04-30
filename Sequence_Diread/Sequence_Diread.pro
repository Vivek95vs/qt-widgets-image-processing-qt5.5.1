#-------------------------------------------------
#
# Project created by QtCreator 2021-06-11T11:11:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sequence_Diread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS +=-lShell32
LIBS += -lAdvapi32

DEFINES -= UNICODE

INCLUDEPATH +="D:\\Workflow\\Work\\TKs\\LibsForGRAY\\DCMTK_3.6.2\\DCMTK_D\\include"
LIBS    +=-L"D:\\Workflow\\Work\\TKs\\LibsForGRAY\\DCMTK_3.6.2\\DCMTK_D\\lib"\
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
