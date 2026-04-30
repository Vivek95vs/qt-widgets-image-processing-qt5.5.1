#-------------------------------------------------
#
# Project created by QtCreator 2023-10-31T15:22:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matlabtrigger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



#MATLAB LIBFILES

INCLUDEPATH += "D:\\TKs\\Enh_final\\include"
LIBS    += -L"D:\\TKs\\Enh_final\\lib"\
            -lEnhancement_Rad

INCLUDEPATH += "D:\\TKs\\DRRGen1\\include"
LIBS    += -L"D:\\TKs\\DRRGen1\\lib"\
            -lDRRGen1

INCLUDEPATH += "D:\\Extern Buffer single Image\\New scatter\\include"
LIBS    += -L"D:\\Extern Buffer single Image\\New scatter\\lib"\
            -lSC_grab

INCLUDEPATH += "D:\\Extern Buffer single Image\\Grab test\\include"
LIBS    += -L"D:\\Extern Buffer single Image\\Grab test\\lib"\
            -lSC_grab_test

INCLUDEPATH += "D:\\Extern Buffer single Image\\SC_grab_v2\\include"
LIBS    += -L"D:\\Extern Buffer single Image\\SC_grab_v2\\lib"\
            -lSC_grab_v2


INCLUDEPATH += "C:\\Program Files\\MATLAB\\MATLAB Runtime\\R2023a\\extern\\include"
LIBS    += -L"C:\\Program Files\\MATLAB\\MATLAB Runtime\\R2023a\\extern\\lib\\win64\\microsoft"\
-llibut\
-lmclbase\
-lmclcommain\
-lmclmcr\
-lmclmcrrt\
-lmclxlmain\
-locrutils\
-locrutilsLegacy\
-lrtwcg\
-lSimulinkBlock\
-ltammex\
-lvideocoderutils\
-lasynciocoder\
-ldisplay_core\
-lgpu\
-lgpumexbinder\
-limagesdatatypescodegenc\
-limagesdatatypescodegenmexutils\
-limagesdatatypesimage\
-limagesdatatypesopencvutils\
-llibcovrt\
-llibemlrt\
-llibeng\
-llibfixedpoint\
-llibmat\
-llibMatlabCppSharedLib\
-llibMatlabDataArray\
-llibmex\
-llibmwacfObjectDetector\
-llibmwastarcodegen\
-llibmwautonomouscodegen\
-llibmwblas\
-llibmwblascompat32\
-llibmwboxfilter\
-llibmwboxfilter3\
-llibmwbundleAdjust\
-llibmwbwdistEDT\
-llibmwbwdistEDT_tbb\
-llibmwbwdistEDTFT\
-llibmwbwdistEDTFT_tbb\
-llibmwbwlookup\
-llibmwbwlookup_tbb\
-llibmwbwpackc\
-llibmwbwpackctbb\
-llibmwbwunpackc\
-llibmwbwunpackctbb\
-llibmwcannythresholding_tbb\
-llibmwcerescodegen\
-llibmwcgir_construct\
-llibmwcgxeooprt\
-llibmwcgxert\
-llibmwcoder_ParamTuningTgtAppSvc\
-llibmwcoder_target_services\
-llibmwcollisionbuiltins\
-llibmwcollisioncodegen\
-llibmwcollisionmapcodegen\
-llibmwComputeMetric\
-llibmwcoveragecodegen\
-llibmwddist\
-llibmwdisparitySGM\
-llibmwdsp_halidesim\
-llibmwedgesobelprewitt_tbb\
-llibmwedgethinning_tbb\
-llibmwforegroundDetector\
-llibmwgetnumcores\
-llibmwgrayto8\
-llibmwgrayto16\
-llibmwgrayxform\
-llibmwgrayxform_tbb\
-llibmwi18n\
-llibmwimfilter\
-llibmwimlincomb\
-llibmwimlincomb_tbb\
-llibmwimreconstruct\
-llibmwimregionalmax\
-llibmwimterp2d\
-llibmwint8touint8\
-llibmwint16touint16\
-llibmwint32touint32\
-llibmwintlut\
-llibmwintluttbb\
-llibmwipp\
-llibmwippfilter\
-llibmwippgeotrans\
-llibmwippmedianfilter\
-llibmwippreconstruct\
-llibmwjpegreader\
-llibmwkdtree\
-llibmwlapack\
-llibmwmathutil\
-llibmwmavlinkcodegen\
-llibmwmclcodegen\
-llibmwmfl_interp\
-llibmwmorphop_binary\
-llibmwmorphop_binary_tbb\
-llibmwmorphop_flat\
-llibmwmorphop_flat_tbb\
-llibmwmorphop_ipp\
-llibmwmorphop_nonflat\
-llibmwmorphop_nonflat_tbb\
-llibmwmorphop_packed\
-llibmwoctomapcodegen\
-llibmwocvmex\
-llibmwoptimizePoses\
-llibmwordfilt2\
-llibmwplanningcodegen\
-llibmwpolyfun\
-llibmwpriorityqueuecodegen\
-llibmwreadAprilTag\
-llibmwreadBarcode\
-llibmwremap\
-llibmwremaptbb\
-llibmwrgb2gray_tbb\
-llibmwrgb2hsv_tbb\
-llibmwsdi_raccel\
-llibmwsearchOrganizedPointCloud\
-llibmwservices\
-llibmwsl_AsyncioQueue\
-llibmwsl_sfcn_loader\
-llibmwslpointerutil\
-llibmwstringutil\
-llibmwtbbhist\
-llibmwuavdubinscodegen\
-llibmwuint16toint16\
-llibmwvoxelGridFilter\
-llibmx
LIBS    += -L"C:\\Program Files\\MATLAB\\MATLAB Runtime\\R2023a\\extern\\lib\\win64"\
-llibMatlabCppSharedLib

