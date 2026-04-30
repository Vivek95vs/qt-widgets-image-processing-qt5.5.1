#-------------------------------------------------
#
# Project created by QtCreator 2021-11-15T15:53:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Read_Raw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH +="D:\\TKs\\gpu\\gpuImageEnhancement_10.2_release\\gpuImageEnhancement"
LIBS +=-L"D:\\TKs\\gpu\\gpuImageEnhancement_10.2_release\\x64\\Release"\
        -lgpuImageEnhancement

##CUDA
#INCLUDEPATH +="D:\\TKs\\v10.2\\include"
#LIBS    += -L"D:\\TKs\\v10.2\\lib\\x64"\
INCLUDEPATH +="C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\v10.2\\include"
LIBS    += -L"C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v10.2\\lib\\x64"\
-lnvgraph\
-lnvjpeg\
-lnvml\
-lnvrtc\
-lOpenCL\
-lcublas\
-lcublasLt\
-lcuda\
-lcudadevrt\
-lcudart\
-lcudart_static\
-lcufft\
-lcufftw\
-lcurand\
-lcusolver\
-lcusolverMg\
-lcusparse\
-lnppc\
-lnppial\
-lnppicc\
-lnppicom\
-lnppidei\
-lnppif\
-lnppig\
-lnppim\
-lnppist\
-lnppisu\
-lnppitc\
-lnpps\
-lnvblas
