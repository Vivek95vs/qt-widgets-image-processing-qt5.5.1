#-------------------------------------------------
#
# Project created by QtCreator 2021-06-10T15:08:19
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Access_DiImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS +=-lShell32
LIBS += -lAdvapi32
LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

DEFINES -= UNICODE

    INCLUDEPATH += "D:\\TKs\\LibsForGRAY\ITK\\ITK_D\\include\\ITK-4.11"
    LIBS      += -L"D:\\TKs\\LibsForGRAY\\ITK\\ITK_D\\lib"\
                    -lITKEXPAT-4.11\
                    -lITKFEM-4.11\
                    -litkgdcmcharls-4.11\
                    -litkgdcmCommon-4.11\
                    -litkgdcmDICT-4.11\
                    -litkgdcmDSED-4.11\
                    -litkgdcmIOD-4.11\
                    -litkgdcmjpeg8-4.11\
                    -litkgdcmjpeg12-4.11\
                    -litkgdcmjpeg16-4.11\
                    -litkgdcmMEXD-4.11\
                    -litkgdcmMSFF-4.11\
                    -litkgdcmopenjpeg-4.11\
                    -litkgdcmsocketxx-4.11\
                    -lITKgiftiio-4.11\
                    -lITKIOBioRad-4.11\
                    -lITKIOBMP-4.11\
                    -lITKIOCSV-4.11\
                    -lITKIOGDCM-4.11\
                    -lITKIOGE-4.11\
                    -lITKIOGIPL-4.11\
                    -lITKIOHDF5-4.11\
                    -lITKIOImageBase-4.11\
                    -lITKIOIPL-4.11\
                    -lITKIOJPEG-4.11\
                    -lITKIOLSM-4.11\
                    -lITKIOMesh-4.11\
                    -lITKIOMeta-4.11\
                    -lITKIOMRC-4.11\
                    -lITKIONIFTI-4.11\
                    -lITKIONRRD-4.11\
                    -lITKIOPNG-4.11\
                    -lITKIOSiemens-4.11\
                    -lITKIOSpatialObjects-4.11\
                    -lITKIOStimulate-4.11\
                    -lITKIOTIFF-4.11\
                    -lITKIOTransformBase-4.11\
                    -lITKIOTransformHDF5-4.11\
                    -lITKIOTransformInsightLegacy-4.11\
                    -lITKIOTransformMatlab-4.11\
                    -lITKIOVTK-4.11\
                    -lITKIOXML-4.11\
                    -litkjpeg-4.11\
                    -lITKKLMRegionGrowing-4.11\
                    -lITKLabelMap-4.11\
                    -lITKMesh-4.11\
                    -lITKMetaIO-4.11\
                    -litknetlib-4.11\
                    -litkNetlibSlatec-4.11\
                    -lITKniftiio-4.11\
                    -lITKNrrdIO-4.11\
                    -lITKOptimizers-4.11\
                    -lITKOptimizersv4-4.11\
                    -lITKPath-4.11\
                    -litkpng-4.11\
                    -lITKPolynomials-4.11\
                    -lITKQuadEdgeMesh-4.11\
                    -lITKSpatialObjects-4.11\
                    -lITKStatistics-4.11\
                    -litksys-4.11\
                    -litktestlib-4.11\
                    -litktiff-4.11\
                    -lITKTransform-4.11\
                    -lITKTransformFactory-4.11\
                    -litkv3p_netlib-4.11\
                    -litkvcl-4.11\
                    -lITKVideoCore-4.11\
                    -lITKVideoIO-4.11\
                    -litkvnl_algo-4.11\
                    -litkvnl-4.11\
                    -lITKVNLInstantiation-4.11\
                    -lITKVTK-4.11\
                    -lITKVtkGlue-4.11\
                    -lITKWatersheds-4.11\
                    -litkzlib-4.11\
                    -lITKznz-4.11\
                    -llibitkhdf5_cpp_D\
                    -llibitkhdf5_D\
                    -lITKBiasCorrection-4.11\
                    -lITKBioCell-4.11\
                    -lITKCommon-4.11\
                    -lITKDICOMParser-4.11\
                    -litkdouble-conversion-4.11\

INCLUDEPATH += "D:\\TKs\\LibsForGRAY\\DCMTK_3.6.2\\DCMTK_D\\include"
LIBS    += -L"D:\\TKs\\LibsForGRAY\\DCMTK_3.6.2\\DCMTK_D\\lib"\
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

INCLUDEPATH += "C:\\Program Files\\OpenSSL-Win64\\include"
LIBS    += -L"C:\\Program Files\\OpenSSL-Win64\\lib\\VC\\x64\\MD"\
-levp_extra_test2\
-llegacy\
-llibapps\
-llibcommon\
-llibcrypto\
-llibcrypto_static\
-llibdefault\
-lliblegacy\
-llibssl\
-llibssl_static\
-llibtemplate\
-llibtestutil\
-lloader_attic\
-lopenssl\
-lossltest\
-lp_minimal\
-lp_test\
-lpadlock\
-lcapi\
-ldasync\
-lec_internal_test
