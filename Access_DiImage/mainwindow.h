#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QString>
#include <QtCore>
#include <QtGui>
#include "dcmtk/dcmrt/drtplan.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcmetinf.h"

#include "dcmtk/dcmdata/dcrlerp.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmdata/dcuid.h"           /* for UID_ defines */
#include "dcmtk/dcmjpeg/djencode.h"
#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/dcmdata/dcvrda.h"
#include "dcmtk/dcmdata/dcvrtm.h"

#include <itkImage.h>
#include <itkPoint.h>
#include <itkImageSliceIteratorWithIndex.h>
#include <itkImageIteratorWithIndex.h>
#include <itkPointSetToImageFilter.h>
#include <itkExtractImageFilter.h>
#include <itkGroupSpatialObject.h>
#include <itkSpatialObjectToImageFilter.h>
#include <itkPolygonSpatialObject.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>

#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include <gdcmTypes.h>
#include <gdcmReader.h>
#include <gdcmSmartPointer.h>
#include <gdcmAttribute.h>
#include <gdcmSequenceOfItems.h>
#include <gdcmFileMetaInformation.h>
#include "itkRGBPixel.h"
#include "itkPNGImageIO.h"
#include "itkNiftiImageIO.h"
#include "itkNiftiImageIOFactory.h"
#include <nifti1_io.h>
#include <itkAndImageFilter.h>

#include "gdcmImage.h"
#include "gdcmReader.h"
#include "gdcmFile.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmWriter.h"
#include "gdcmItem.h"
#include "gdcmTag.h"
#include "gdcmImageWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageReader.h"
#include <gdcmSmartPointer.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString strlist;
    QList<QList<QStringList>> tags;
    double PixelX=300,PixelY=300;
    QPointF PixelPitch1;
    QPointF PointCen;
    QVector<QPointF>Size,Cancer_center;
    QList<QStringList>Contentlist2;
    QStringList TagList1;
    int i;
    QList<QPointF> IsoCentres;
    int width=512 ;
    int height=512;
    int Rows;
    int Cols;
    unsigned char *dispImg;
    unsigned char *slice;
    QImage q_image;
    QString editBeamName;

    QString ImageTypes;
    QString InstanceCreationDate;
    QString InstanceCreationTime;
   QString SOPClassUIDs;
   QString StudyInstanceUID;
   QString SeriesInstanceUID;
    QString StudyDate;
    QString SeriesDate;
    QString SeriesDescription;
    QString AcquisitionDate;
    QString ContentDate;
    QString StudyTime;
    QString SeriesTime;
    QString AcquisitionTime;
    QString ContentTime;
    QString AccessionNumber;
    QString Modality;
    QString Manufacturer;
    QString InstitutionName;
    QString ReferringPhysiciansName;
    QString StationName;
    QString PerformingPhysiciansName;
    QString OperatorsName;
    QString ManufacturersModelName;
    QString PatientID;
    QString patientsBirthDate;
    QString PatientsSex;
    QString ScanOptions;
    QString SliceThickness2;
    QString KVP;
    QString DataCollectionDiameter;
    QString DeviceSerialNumber;
    QString PatientPositionSetup;
    QString m_Patientsetup;
    QString SoftwareVersions;
    QString ProtocolName;
    QString ReconstructionDiameter;
    QString GantryDetectorTilt;
    QString TableHeight;
    QString RotationDirection;
    QString ExposureTime;
    QString XRayTubeCurrent;
    QString ExposureInuAs;
    QString FilterType;
    QString GeneratorPower;
    QString FocalSpots;
    QString DateofLastCalibration;
    QString TimeofLastCalibration;
    QString ConvolutionKernel;
    QString PatientPosition;
    QString SeriesNumber;
    QString AcquisitionNumber;
    QString InstanceNumber;

    QStringList ImagePositionPatients;
    QStringList ImageOrientationPatient;
    QString FrameofReferenceUID;
    QString PositionReferenceIndicator;
    QString SliceLocation;
    QString SamplesperPixel;
    QString PhotometricInterpretation;
    QString Rows1;
    QString Columns;
    QStringList PixelSpacing;
    QString BitsAllocated;
    QString BitsStored;
    QString HighBit;
    QString PixelRepresentation;
    QString SmallestImagePixelValue;
    QString LargestImagePixelValue;
    QString SmallestPixelValueinSeries;
    QString LargestPixelValueinSeries;
    QString QualityControlImage;
    QString RescaleIntercept;
    QString RescaleSlope;
    QString PixelData;
    QString WindowWidth;
    QString WindowCenter;


    void downsampleImageVertical(unsigned short *originalImage, std::vector<unsigned short> &downsampledImage, int Originalwidth, int Originalheight, int downsampledWidth, int downsampledHeight);
    void downsampleImageHorizontal(unsigned short *originalImage, std::vector<unsigned short> &downsampledImage, int Originalwidth, int Originalheight, int downsampledWidth, int downsampledHeight);
    QByteArray imageToByteArray(const QString &imagePath);
public slots:

    void write();
    void read();
    void stitchlateral();
    void stitchlogitudinal();
    void stitchlogitudinalfive();

private slots:
    void on_Dicomtoraw_clicked();

    void on_pushButton_clicked();

    void on_Access_clicked();

    void on_Blank_raw_clicked();

    void on_compress_CBCT_clicked();

    void on_on_crop_raw_clicked();

    void on_vertical_crop_clicked();

    void on_Converttobinary_clicked();

    void on_Block_input_clicked();

    void on_Decrypt_clicked();

    void on_Dicom_lateral_crop_clicked();

    void on_longitudinalfive_clicked();

    void on_lateralfive_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    QGraphicsView *view;

};

#endif // MAINWINDOW_H
