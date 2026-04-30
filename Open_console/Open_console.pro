QT += core
QT -= gui

TARGET = Open_console
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += D:\\Workflow\\Work\\Opencv\\include \

LIBS += -LD:\\Workflow\\Work\\Opencv\\x64\\vc12\\lib \
           -lopencv_world300\
           -lopencv_world300d\
           -lopencv_ts300\
           -lopencv_ts300d
