#-------------------------------------------------
#
# Project created by QtCreator 2021-04-26T13:48:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Operation
TEMPLATE = app


SOURCES += main.cpp\
        operation_img.cpp \
    disp_evt.cpp \
    ruler_item.cpp

HEADERS  += operation_img.h \
    disp_evt.h \
    ruler_item.h

FORMS    += operation_img.ui
