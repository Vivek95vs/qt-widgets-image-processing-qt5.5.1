#-------------------------------------------------
#
# Project created by QtCreator 2021-07-20T15:22:07
#
#-------------------------------------------------

QT += core gui
QT += sql
QT += xml
QT += network
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = New_Dicom
TEMPLATE = app


SOURCES += main.cpp \
    QvtkDicomviewer.cpp \
    CommonHelper.cpp \
    DicomDataBase.cpp \
    DicomDir.cpp \
    DicomDirTreeModel.cpp \
    DicomImage.cpp \
    DicomPatient.cpp \
    DicomSeries.cpp \
    DicomStudy.cpp \
    DicomTreeItem.cpp \
    myVtkInteractorStyleImage.cpp \
    Register.cpp \
    Segmenter.cpp \
    Startup.cpp \
    ThreeD_Reconstruction.cpp \
    vtkBiDimensionalCallback.cpp \
    vtkImageSegmentCallback.cpp \
    vtkMyDICOMImageReader.cpp

HEADERS  += \
    QvtkDicomViewer.h \
    CommonHelper.h \
    DicomDataBase.h \
    DicomDir.h \
    DicomDirTreeModel.h \
    DicomImage.h \
    DicomPatient.h \
    DicomSeries.h \
    DicomStudy.h \
    DicomTreeItem.h \
    head_all.h \
    myVtkInteractorStyleImage.h \
    Register.h \
    Segmenter.h \
    Startup.h \
    ThreeD_Reconstruction.h \
    vtkBiDimensionalCallback.h \
    vtkImageSegmentCallback.h \
    vtkMyDICOMImageReader.h

FORMS    += qvtkdicomviewer.ui \
            DialogButtonBottom.ui \
            DicomDir.ui \
            MainWindow.ui \
            Register.ui \
            Segmenter.ui \
            Startup.ui \
            ThreeD_Reconstruction.ui

LIBS +=-lShell32
LIBS += -lAdvapi32

DEFINES -= UNICODE
LIBS += "Rpcrt4.lib"
LIBS += "WS2_32.lib"

INCLUDEPATH +="D:\\Workflow\\Work\\TKs\\libsfile\\dcmtk_3.6.2\\include\\dcmtk"
LIBS    +=-L"D:\\Workflow\\Work\\TKs\\libsfile\\dcmtk_3.6.2\\lib"\
-charls \
-cmr \
-dcmdata \
-dcmdsig \
-dcmfg \
-dcmimage \
-dcmimgle \
-dcmiod \
-dcmjpeg \
-dcmjpls \
-dcmnet \
-dcmpmap \
-dcmpstat \
-dcmqrdb \
-dcmrt \
-dcmseg \
-dcmsr \
-dcmtls \
-dcmtract \
-dcmwlm \
-i2d \
-ijg8 \
-ijg12 \
-ijg16 \
-oflog \
-ofstd \

INCLUDEPATH +="D:\\Workflow\\Work\\TKs\\libsfile\\itk_4.12\\include\\ITK-4.12"
LIBS    +=-L"D:\\Workflow\\Work\\TKs\\libsfile\\itk_4.12\\lib"\
-ITKTransformFactory-4.12-gd \
-itkv3p_netlib-4.12-gd \
-itkvcl-4.12-gd \
-ITKVideoCore-4.12-gd \
-ITKVideoIO-4.12-gd \
-itkvnl_algo-4.12-gd \
-itkvnl-4.12-gd \
-ITKVNLInstantiation-4.12-gd \
-ITKVTK-4.12-gd \
-ITKVtkGlue-4.12-gd \
-ITKWatersheds-4.12-gd \
-itkzlib-4.12-gd \
-ITKznz-4.12-gd \
-libitkhdf5_cpp_D-gd \
-libitkhdf5_D-gd \
-ITKBiasCorrection-4.12-gd \
-ITKBioCell-4.12-gd \
-ITKCommon-4.12-gd \
-ITKDICOMParser-4.12-gd \
-itkdouble-conversion-4.12-gd \
-ITKEXPAT-4.12-gd \
-ITKFEM-4.12-gd \
-itkgdcmcharls-4.12-gd \
-itkgdcmCommon-4.12-gd \
-itkgdcmDICT-4.12-gd \
-itkgdcmDSED-4.12-gd \
-itkgdcmIOD-4.12-gd \
-itkgdcmjpeg8-4.12-gd \
-itkgdcmjpeg12-4.12-gd \
-itkgdcmjpeg16-4.12-gd \
-itkgdcmMEXD-4.12-gd \
-itkgdcmMSFF-4.12-gd \
-itkgdcmopenjpeg-4.12-gd \
-itkgdcmsocketxx-4.12-gd \
-ITKgiftiio-4.12-gd \
-ITKIOBioRad-4.12-gd \
-ITKIOBMP-4.12-gd \
-ITKIOCSV-4.12-gd \
-ITKIOGDCM-4.12-gd \
-ITKIOGE-4.12-gd \
-ITKIOGIPL-4.12-gd \
-ITKIOHDF5-4.12-gd \
-ITKIOImageBase-4.12-gd \
-ITKIOIPL-4.12-gd \
-ITKIOJPEG-4.12-gd \
-ITKIOLSM-4.12-gd \
-ITKIOMesh-4.12-gd \
-ITKIOMeta-4.12-gd \
-ITKIOMRC-4.12-gd \
-ITKIONIFTI-4.12-gd \
-ITKIONRRD-4.12-gd \
-ITKIOPNG-4.12-gd \
-ITKIOSiemens-4.12-gd \
-ITKIOSpatialObjects-4.12-gd \
-ITKIOStimulate-4.12-gd \
-ITKIOTIFF-4.12-gd \
-ITKIOTransformBase-4.12-gd \
-ITKIOTransformHDF5-4.12-gd \
-ITKIOTransformInsightLegacy-4.12-gd \
-ITKIOTransformMatlab-4.12-gd \
-ITKIOVTK-4.12-gd \
-ITKIOXML-4.12-gd \
-itkjpeg-4.12-gd \
-ITKKLMRegionGrowing-4.12-gd \
-ITKLabelMap-4.12-gd \
-ITKMesh-4.12-gd \
-ITKMetaIO-4.12-gd \
-itknetlib-4.12-gd \
-itkNetlibSlatec-4.12-gd \
-ITKniftiio-4.12-gd \
-ITKNrrdIO-4.12-gd \
-ITKOptimizers-4.12-gd \
-ITKOptimizersv4-4.12-gd \
-ITKPath-4.12-gd \
-itkpng-4.12-gd \
-ITKPolynomials-4.12-gd \
-ITKQuadEdgeMesh-4.12-gd \
-ITKSpatialObjects-4.12-gd \
-ITKStatistics-4.12-gd \
-itksys-4.12-gd \
-itktestlib-4.12-gd \
-itktiff-4.12-gd \
-ITKTransform-4.12-gd

INCLUDEPATH +="D:\\Workflow\\Work\\TKs\\libsfile\\vtk_8.0.0\\include\vtk-8.0"
LIBS    +=-L"D:\\Workflow\\Work\\TKs\\libsfile\\vtk_8.0.0\\lib"\
-vtkalglib-8.0-gd \
-vtkChartsCore-8.0-gd \
-vtkCommonColor-8.0-gd \
-vtkCommonComputationalGeometry-8.0-gd \
-vtkCommonCore-8.0-gd \
-vtkCommonDataModel-8.0-gd \
-vtkCommonExecutionModel-8.0-gd \
-vtkCommonMath-8.0-gd \
-vtkCommonMisc-8.0-gd \
-vtkCommonSystem-8.0-gd \
-vtkCommonTransforms-8.0-gd \
-vtkDICOMParser-8.0-gd \
-vtkDomainsChemistry-8.0-gd \
-vtkDomainsChemistryOpenGL2-8.0-gd \
-vtkexoIIc-8.0-gd \
-vtkexpat-8.0-gd \
-vtkFiltersAMR-8.0-gd \
-vtkFiltersCore-8.0-gd \
-vtkFiltersExtraction-8.0-gd \
-vtkFiltersFlowPaths-8.0-gd \
-vtkFiltersGeneral-8.0-gd \
-vtkFiltersGeneric-8.0-gd \
-vtkFiltersGeometry-8.0-gd \
-vtkFiltersHybrid-8.0-gd \
-vtkFiltersHyperTree-8.0-gd \
-vtkFiltersImaging-8.0-gd \
-vtkFiltersModeling-8.0-gd \
-vtkFiltersParallel-8.0-gd \
-vtkFiltersParallelImaging-8.0-gd \
-vtkFiltersPoints-8.0-gd \
-vtkFiltersProgrammable-8.0-gd \
-vtkFiltersSelection-8.0-gd \
-vtkFiltersSMP-8.0-gd \
-vtkFiltersSources-8.0-gd \
-vtkFiltersStatistics-8.0-gd \
-vtkFiltersTexture-8.0-gd \
-vtkFiltersTopology-8.0-gd \
-vtkFiltersVerdict-8.0-gd \
-vtkfreetype-8.0-gd \
-vtkGeovisCore-8.0-gd \
-vtkgl2ps-8.0-gd \
-vtkglew-8.0-gd \
-vtkGUISupportQt-8.0-gd \
-vtkGUISupportQtSQL-8.0-gd \
-vtkhdf5-8.0-gd \
-vtkhdf5_hl-8.0-gd \
-vtkImagingColor-8.0-gd \
-vtkImagingCore-8.0-gd \
-vtkImagingFourier-8.0-gd \
-vtkImagingGeneral-8.0-gd \
-vtkImagingHybrid-8.0-gd \
-vtkImagingMath-8.0-gd \
-vtkImagingMorphological-8.0-gd \
-vtkImagingSources-8.0-gd \
-vtkImagingStatistics-8.0-gd \
-vtkImagingStencil-8.0-gd \
-vtkInfovisCore-8.0-gd \
-vtkInfovisLayout-8.0-gd \
-vtkInteractionImage-8.0-gd \
-vtkInteractionStyle-8.0-gd \
-vtkInteractionWidgets-8.0-gd \
-vtkIOAMR-8.0-gd \
-vtkIOCore-8.0-gd \
-vtkIOEnSight-8.0-gd \
-vtkIOExodus-8.0-gd \
-vtkIOExport-8.0-gd \
-vtkIOExportOpenGL2-8.0-gd \
-vtkIOGeometry-8.0-gd \
-vtkIOImage-8.0-gd \
-vtkIOImport-8.0-gd \
-vtkIOInfovis-8.0-gd \
-vtkIOLegacy-8.0-gd \
-vtkIOLSDyna-8.0-gd \
-vtkIOMINC-8.0-gd \
-vtkIOMovie-8.0-gd \
-vtkIONetCDF-8.0-gd \
-vtkIOParallel-8.0-gd \
-vtkIOParallelXML-8.0-gd \
-vtkIOPLY-8.0-gd \
-vtkIOSQL-8.0-gd \
-vtkIOTecplotTable-8.0-gd \
-vtkIOVideo-8.0-gd \
-vtkIOXML-8.0-gd \
-vtkIOXMLParser-8.0-gd \
-vtkjpeg-8.0-gd \
-vtkjsoncpp-8.0-gd \
-vtklibharu-8.0-gd \
-vtklibxml2-8.0-gd \
-vtklz4-8.0-gd \
-vtkmetaio-8.0-gd \
-vtkNetCDF-8.0-gd \
-vtknetcdf_c++-gd \
-vtkoggtheora-8.0-gd \
-vtkParallelCore-8.0-gd \
-vtkpng-8.0-gd \
-vtkproj4-8.0-gd \
-vtkRenderingAnnotation-8.0-gd \
-vtkRenderingContext2D-8.0-gd \
-vtkRenderingContextOpenGL2-8.0-gd \
-vtkRenderingCore-8.0-gd \
-vtkRenderingFreeType-8.0-gd \
-vtkRenderingGL2PSOpenGL2-8.0-gd \
-vtkRenderingImage-8.0-gd \
-vtkRenderingLabel-8.0-gd \
-vtkRenderingLOD-8.0-gd \
-vtkRenderingOpenGL2-8.0-gd \
-vtkRenderingQt-8.0-gd \
-vtkRenderingVolume-8.0-gd \
-vtkRenderingVolumeOpenGL2-8.0-gd \
-vtksqlite-8.0-gd \
-vtksys-8.0-gd \
-vtktiff-8.0-gd \
-vtkverdict-8.0-gd \
-vtkViewsContext2D-8.0-gd \
-vtkViewsCore-8.0-gd \
-vtkViewsInfovis-8.0-gd \
-vtkViewsQt-8.0-gd \
-vtkzlib-8.0-gd

RESOURCES += \
    QvtkDicomViewer.qrc \

DISTFILES += \
    defaultTreeContext.txt \
    simhei.ttf

