QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS +=-lShell32
LIBS += -lAdvapi32
LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

DEFINES -= UNICODE

INCLUDEPATH +="D:\\TKs\\2019 dll build\\ITK\\ITK_R\\include\\ITK-5.3"
LIBS    +=-L"D:\\TKs\\2019 dll build\\ITK\\ITK_R\\lib"\
-lITKDenoising-5.3\
-lITKDICOMParser-5.3\
-lITKDiffusionTensorImage-5.3\
-litkdouble-conversion-5.3\
-lITKEXPAT-5.3\
-lITKFastMarching-5.3\
-lITKFEM-5.3\
-lITKFEMRegistration-5.3\
-lITKFFT-5.3\
-litkgdcmcharls-5.3\
-litkgdcmCommon-5.3\
-litkgdcmDICT-5.3\
-litkgdcmDSED-5.3\
-litkgdcmIOD-5.3\
-litkgdcmjpeg8-5.3\
-litkgdcmjpeg12-5.3\
-litkgdcmjpeg16-5.3\
-litkgdcmMEXD-5.3\
-litkgdcmMSFF-5.3\
-litkgdcmopenjp2-5.3\
-litkgdcmsocketxx-5.3\
-lITKgiftiio-5.3\
-litkgtest_main-5.3\
-litkgtest-5.3\
-litkhdf5_cpp-shared-5.3\
-litkhdf5_hl-shared-5.3\
-litkhdf5-shared-5.3\
-lITKImageFeature-5.3\
-lITKImageIntensity-5.3\
-lITKIOBioRad-5.3\
-lITKIOBMP-5.3\
-lITKIOBruker-5.3\
-lITKIOCSV-5.3\
-lITKIODCMTK-5.3\
-lITKIOGDCM-5.3\
-lITKIOGE-5.3\
-lITKIOGIPL-5.3\
-lITKIOHDF5-5.3\
-lITKIOImageBase-5.3\
-lITKIOIPL-5.3\
-lITKIOJPEG-5.3\
-lITKIOJPEG2000-5.3\
-lITKIOLSM-5.3\
-lITKIOMeshBase-5.3\
-lITKIOMeshBYU-5.3\
-lITKIOMeshFreeSurfer-5.3\
-lITKIOMeshGifti-5.3\
-lITKIOMeshOBJ-5.3\
-lITKIOMeshOFF-5.3\
-lITKIOMeshVTK-5.3\
-lITKIOMeta-5.3\
-lITKIOMINC-5.3\
-lITKIOMRC-5.3\
-lITKIONIFTI-5.3\
-lITKIONRRD-5.3\
-lITKIOPNG-5.3\
-lITKIOSiemens-5.3\
-lITKIOSpatialObjects-5.3\
-lITKIOStimulate-5.3\
-lITKIOTIFF-5.3\
-lITKIOTransformBase-5.3\
-litkIOTransformDCMTK-5.3\
-lITKIOTransformHDF5-5.3\
-lITKIOTransformInsightLegacy-5.3\
-lITKIOTransformMatlab-5.3\
-lITKIOVTK-5.3\
-lITKIOXML-5.3\
-litkjpeg-5.3\
-lITKKLMRegionGrowing-5.3\
-lITKLabelMap-5.3\
-litklbfgs-5.3\
-lITKMarkovRandomFieldsClassifiers-5.3\
-lITKMathematicalMorphology-5.3\
-lITKMesh-5.3\
-lITKMetaIO-5.3\
-litkminc2-5.3\
-litkMinimalPathExtraction-5.3\
-litkMontage-5.3\
-litkNetlibSlatec-5.3\
-lITKniftiio-5.3\
-lITKNrrdIO-5.3\
-litkopenjpeg-5.3\
-lITKOptimizers-5.3\
-lITKOptimizersv4-5.3\
-lITKPath-5.3\
-lITKPDEDeformableRegistration-5.3\
-litkpng-5.3\
-lITKPolynomials-5.3\
-lITKQuadEdgeMesh-5.3\
-lITKQuadEdgeMeshFiltering-5.3\
-lITKRegionGrowing-5.3\
-lITKRegistrationMethodsv4-5.3\
-litkSimpleITKFilters-5.3\
-lITKSmoothing-5.3\
-lITKSpatialObjects-5.3\
-lITKStatistics-5.3\
-litksys-5.3\
-lITKTestKernel-5.3\
-litktestlib-5.3\
-litktiff-5.3\
-lITKTransform-5.3\
-lITKTransformFactory-5.3\
-litkv3p_netlib-5.3\
-litkvcl-5.3\
-lITKVideoCore-5.3\
-lITKVideoIO-5.3\
-litkvnl_algo-5.3\
-litkvnl-5.3\
-lITKVNLInstantiation-5.3\
-lITKVTK-5.3\
-lITKWatersheds-5.3\
-litkzlib-5.3\
-lITKznz-5.3\
-lhdf5_hl_cpp-shared\
-litkAdaptiveDenoising-5.3\
-litkAnalyzeObjectLabelMap-5.3\
-lITKBiasCorrection-5.3\
-lITKColormap-5.3\
-lITKCommon-5.3\
-lITKConvolution-5.3\
-litkCudaCommon-5.3\
-lITKDeformableMesh-5.3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
