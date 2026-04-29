#-------------------------------------------------
#
# Project created by QtCreator 2021-04-23T14:46:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment_Thread
TEMPLATE = app


SOURCES += main.cpp\
        test_thread.cpp \
    worker_producer.cpp \
    worker_consumer.cpp

HEADERS  += test_thread.h \
    worker_producer.h \
    worker_consumer.h \
    basicfunc.h \
    constants.h

FORMS    += test_thread.ui
