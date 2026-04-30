#-------------------------------------------------
#
# Project created by QtCreator 2021-04-22T10:42:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Thread_Test
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    myworker.cpp

HEADERS  += dialog.h \
    myworker.h

FORMS    += dialog.ui
