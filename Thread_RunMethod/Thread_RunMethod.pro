#-------------------------------------------------
#
# Project created by QtCreator 2021-04-24T11:43:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Thread_RunMethod
TEMPLATE = app


SOURCES += main.cpp\
        run_over.cpp \
    producer_run.cpp \
    consumer_run.cpp

HEADERS  += run_over.h \
    producer_run.h \
    consumer_run.h \
    commonfun.h \
    nonchangable.h

FORMS    += run_over.ui
