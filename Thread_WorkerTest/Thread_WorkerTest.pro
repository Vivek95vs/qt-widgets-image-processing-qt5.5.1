QT += core
QT -= gui

TARGET = Thread_WorkerTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myworker.cpp

HEADERS += \
    myworker.h

