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

LIBS += -lAdvapi32

LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

INCLUDEPATH +="D:\\TKs\\2019 dll build\\VTK\\VTK_R\\include\\vtk-9.3"
LIBS    +=-L"D:\\TKs\\2019 dll build\\VTK\\VTK_R\\lib"\
-lvtkCommonSystem-9.3\
-lvtkCommonTransforms-9.3\
-lvtkDICOMParser-9.3\
-lvtkDomainsChemistry-9.3\
-lvtkDomainsChemistryOpenGL2-9.3\
-lvtkdoubleconversion-9.3\
-lvtkexodusII-9.3\
-lvtkexpat-9.3\
-lvtkFiltersAMR-9.3\
-lvtkFiltersCellGrid-9.3\
-lvtkFiltersCore-9.3\
-lvtkFiltersDSP-9.3\
-lvtkFiltersExtraction-9.3\
-lvtkFiltersFlowPaths-9.3\
-lvtkFiltersGeneral-9.3\
-lvtkFiltersGeneric-9.3\
-lvtkFiltersGeometry-9.3\
-lvtkFiltersGeometryPreview-9.3\
-lvtkFiltersHybrid-9.3\
-lvtkFiltersHyperTree-9.3\
-lvtkFiltersImaging-9.3\
-lvtkFiltersModeling-9.3\
-lvtkFiltersParallel-9.3\
-lvtkFiltersParallelImaging-9.3\
-lvtkFiltersPoints-9.3\
-lvtkFiltersProgrammable-9.3\
-lvtkFiltersReduction-9.3\
-lvtkFiltersSelection-9.3\
-lvtkFiltersSMP-9.3\
-lvtkFiltersSources-9.3\
-lvtkFiltersStatistics-9.3\
-lvtkFiltersTensor-9.3\
-lvtkFiltersTexture-9.3\
-lvtkFiltersTopology-9.3\
-lvtkFiltersVerdict-9.3\
-lvtkfmt-9.3\
-lvtkfreetype-9.3\
-lvtkGeovisCore-9.3\
-lvtkgl2ps-9.3\
-lvtkglew-9.3\
-lvtkhdf5_hl-9.3\
-lvtkhdf5-9.3\
-lvtkImagingColor-9.3\
-lvtkImagingCore-9.3\
-lvtkImagingFourier-9.3\
-lvtkImagingGeneral-9.3\
-lvtkImagingHybrid-9.3\
-lvtkImagingMath-9.3\
-lvtkImagingMorphological-9.3\
-lvtkImagingSources-9.3\
-lvtkImagingStatistics-9.3\
-lvtkImagingStencil-9.3\
-lvtkInfovisCore-9.3\
-lvtkInfovisLayout-9.3\
-lvtkInteractionImage-9.3\
-lvtkInteractionStyle-9.3\
-lvtkInteractionWidgets-9.3\
-lvtkIOAMR-9.3\
-lvtkIOAsynchronous-9.3\
-lvtkIOCellGrid-9.3\
-lvtkIOCesium3DTiles-9.3\
-lvtkIOCGNSReader-9.3\
-lvtkIOChemistry-9.3\
-lvtkIOCityGML-9.3\
-lvtkIOCONVERGECFD-9.3\
-lvtkIOCore-9.3\
-lvtkIOEnSight-9.3\
-lvtkIOExodus-9.3\
-lvtkIOExport-9.3\
-lvtkIOExportGL2PS-9.3\
-lvtkIOExportPDF-9.3\
-lvtkIOFLUENTCFF-9.3\
-lvtkIOGeometry-9.3\
-lvtkIOHDF-9.3\
-lvtkIOImage-9.3\
-lvtkIOImport-9.3\
-lvtkIOInfovis-9.3\
-lvtkIOIOSS-9.3\
-lvtkIOLegacy-9.3\
-lvtkIOLSDyna-9.3\
-lvtkIOMINC-9.3\
-lvtkIOMotionFX-9.3\
-lvtkIOMovie-9.3\
-lvtkIONetCDF-9.3\
-lvtkIOOggTheora-9.3\
-lvtkIOParallel-9.3\
-lvtkIOParallelXML-9.3\
-lvtkIOPLY-9.3\
-lvtkIOSegY-9.3\
-lvtkIOSQL-9.3\
-lvtkioss-9.3\
-lvtkIOTecplotTable-9.3\
-lvtkIOVeraOut-9.3\
-lvtkIOVideo-9.3\
-lvtkIOXML-9.3\
-lvtkIOXMLParser-9.3\
-lvtkjpeg-9.3\
-lvtkjsoncpp-9.3\
-lvtkkissfft-9.3\
-lvtklibharu-9.3\
-lvtklibproj-9.3\
-lvtklibxml2-9.3\
-lvtkloguru-9.3\
-lvtklz4-9.3\
-lvtklzma-9.3\
-lvtkmetaio-9.3\
-lvtknetcdf-9.3\
-lvtkogg-9.3\
-lvtkParallelCore-9.3\
-lvtkParallelDIY-9.3\
-lvtkpng-9.3\
-lvtkpugixml-9.3\
-lvtkRenderingAnnotation-9.3\
-lvtkRenderingCellGrid-9.3\
-lvtkRenderingContext2D-9.3\
-lvtkRenderingContextOpenGL2-9.3\
-lvtkRenderingCore-9.3\
-lvtkRenderingFreeType-9.3\
-lvtkRenderingGL2PSOpenGL2-9.3\
-lvtkRenderingHyperTreeGrid-9.3\
-lvtkRenderingImage-9.3\
-lvtkRenderingLabel-9.3\
-lvtkRenderingLICOpenGL2-9.3\
-lvtkRenderingLOD-9.3\
-lvtkRenderingOpenGL2-9.3\
-lvtkRenderingSceneGraph-9.3\
-lvtkRenderingUI-9.3\
-lvtkRenderingVolume-9.3\
-lvtkRenderingVolumeOpenGL2-9.3\
-lvtkRenderingVtkJS-9.3\
-lvtksqlite-9.3\
-lvtksys-9.3\
-lvtkTestingRendering-9.3\
-lvtktheora-9.3\
-lvtktiff-9.3\
-lvtkverdict-9.3\
-lvtkViewsContext2D-9.3\
-lvtkViewsCore-9.3\
-lvtkViewsInfovis-9.3\
-lvtkWrappingTools-9.3\
-lvtkzlib-9.3\
-lport\
-lvtkcgns-9.3\
-lvtkChartsCore-9.3\
-lvtkCommonColor-9.3\
-lvtkCommonComputationalGeometry-9.3\
-lvtkCommonCore-9.3\
-lvtkCommonDataModel-9.3\
-lvtkCommonExecutionModel-9.3\
-lvtkCommonImplicitArrays-9.3\
-lvtkCommonMath-9.3\
-lvtkCommonMisc-9.3

INCLUDEPATH +="D:\\TKs\\2019 dll build\\DicomLibrary\\DICOM_R\\include"
LIBS    += -L"D:\\TKs\\2019 dll build\\DicomLibrary\\DICOM_R\\lib"\
           -ldicomcli\
           -lvtkDICOM-9.3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
