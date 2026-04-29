#-------------------------------------------------
#
# Project created by QtCreator 2021-04-28T12:07:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Delineator_Work
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp \
    customitem.cpp \
    sizegripitem.cpp

HEADERS  += mainwindow.h \
    customscene.h \
    customitem.h \
    sizegripitem.h

FORMS    += mainwindow.ui
