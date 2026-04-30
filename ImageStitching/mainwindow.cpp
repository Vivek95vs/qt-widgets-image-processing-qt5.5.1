#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <itkImage.h>
#include <itkRegionOfInterestImageFilter.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <gdcmUIDGenerator.h>
#include <itkCommand.h>
#include "itkImageFileWriter.h"
#include <itkGDCMImageIO.h>
#include "itkMetaDataObject.h"
#include <itkMetaDataDictionary.h>
#include "itkImportImageFilter.h"
#include "itkImage.h"
#include "itkResampleImageFilter.h"
#include "itkAffineTransform.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "QDir"
#include "QDate"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene();

    Simulation_Quad_Raw_Path= "D:\\RAD\\Linac Stitch";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::downsampleImage(unsigned short* originalImage, std::vector<unsigned short>& downsampledImage,int Originalwidth,int Originalheight,int downsampledWidth,int downsampledHeight)
{

    int dimSRAD[2];
    dimSRAD[0]    = (int)radSize;
    dimSRAD[1]    = (int)radSize;

    // Iterate over each block in the downsampled image
    for (int j = 0; j < downsampledHeight; j++) {
        for (int i = 0; i < downsampledWidth; i++) {
            // Calculate the corresponding block in the original image
            int originalStartX = i * Originalwidth / downsampledWidth;
            int originalStartY = j * Originalheight / downsampledHeight;

            // Calculate the average value of the block in the original image
            unsigned short averageValue = 0;
            for (int y = 0; y < Originalheight / downsampledHeight; y++) {
                for (int x = 0; x < Originalwidth / downsampledWidth; x++) {
                    averageValue += originalImage[originalStartX + x + (originalStartY + y) * Originalwidth];
                }
            }
            averageValue /= (Originalheight / downsampledHeight) * (Originalwidth / downsampledWidth);

            // Assign the average value to the corresponding pixel in the downsampled image
            downsampledImage[i + j * downsampledWidth] = averageValue;
        }
    }

    // Create a new image to store the rotated result
    std::vector<unsigned short> rotatedImage(downsampledWidth * downsampledHeight);

    // Rotate the image
    for (int j = 0; j < downsampledHeight; ++j) {
        for (int i = 0; i < downsampledWidth; ++i) {
            // Rotate the pixels
            rotatedImage[j + (downsampledWidth - i - 1) * downsampledHeight] = downsampledImage[i + j * downsampledWidth];
        }
    }


    FILE* Fp831_cropped;
    QString cropped1=Simulation_Quad_Raw_Path+"\\"+"Downsampled_rotated_cropped.raw";
    fopen_s(&Fp831_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(/*rotatedImage.data()*/downsampledImage.data(), sizeof(unsigned short), 3072 * 3072, Fp831_cropped);

    fclose(Fp831_cropped);

//    QString filename = Simulation_Quad_Raw_Path+"\\"+"Downsampled_rotated_cropped.raw";
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned char *dispImg= new unsigned char[radSize*radSize];
//    unsigned short *radbuf1 = new unsigned short[radSize*radSize];

//    fread(radbuf1,sizeof(unsigned short),radSize*radSize,Img);

//    int max_value=0;
//     for(int m=0;m<radSize*radSize;m++)
//     {
//         if(radbuf1[m]>max_value)
//         {
//             max_value=radbuf1[m];
//         }
//     }
////                       maximum_value_for_denom = max_value;
//     qDebug()<<max_value<<"maximum value-------";
//    for(int i=0;i<radSize*radSize;++i)
//    {
//        dispImg[i] = radbuf1[i]*255.0/max_value;
//    }


//    QString fpath=Simulation_RAD_DICOM_Path+"\\"+"Stitched Image.dcm";
//    if(DicomModality=="DX")
//    {
//       this->saveImageTostitchDicomDX(radbuf1, fpath,radSize);
//    }
//    else
//    {
//       this->saveImageTostitchDicomRT(radbuf1, fpath,radSize);//Save Images without Cropping Also
//    }

//    this->displayImage(sceneMLC,dispImg,color_table1,dimSRAD);

//    fclose(Img);
//    delete[] dispImg;

//    radProjCount=0;
////    this->updateDilineatorInfo(radSize);

////    if(ui->EDilineator->isChecked())

//    //        ui->EDilineator->setChecked(false);
//    ui->EDilineator->setDisabled(true);

}
void MainWindow::ImageStitching()
{

      int width=3072;
      int height=3072;
      int height1=9216 ,width1=9216;

      unsigned short *imagein1 = new unsigned short[width*height];
      unsigned short *imagein2 = new unsigned short[width*height];
      unsigned short *imagein3 = new unsigned short[width*height];
//      unsigned short *imagein4 = new unsigned short[width*height];

      QString LoadImg1= Simulation_Quad_Raw_Path+QString("\\proj_1.raw");
      FILE* Fp_in1;
      fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
      fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
      fclose(Fp_in1);

      QString LoadImg2= Simulation_Quad_Raw_Path+QString("\\proj_2.raw");
      FILE* Fp_in2;
      fopen_s(&Fp_in2, LoadImg2.toStdString().c_str(), "rb+");
      fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
      fclose(Fp_in2);

      QString LoadImg3= Simulation_Quad_Raw_Path+QString("\\proj_3.raw");
      FILE* Fp_in3;
      fopen_s(&Fp_in3, LoadImg3.toStdString().c_str(), "rb+");
      fread(imagein3, sizeof(unsigned short), width * height, Fp_in3);
      fclose(Fp_in3);

//      QString LoadImg4= Simulation_Quad_Raw_Path+QString("\\Quad_4.raw");
//      FILE* Fp_in4;
//      fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
//      fread(imagein4, sizeof(unsigned short), width * height, Fp_in4);
//      fclose(Fp_in4);


    qDebug() << "Image addition 1";
      unsigned short **one_img = new unsigned short*[height];

      for (int i = 0; i < height; i++)
          one_img[i] = new unsigned short[width];
        int p = 0;

       for (int i = 0; i < height; i++)
       {
            for (int j = 0; j < width ; j++)
           {
              one_img[i][j] = imagein1[p];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
              p = p + 1;
           }
       }
    qDebug() << "Image addition2 ";

       unsigned short **two_img = new unsigned short*[height];

       for (int i = 0; i < height; i++)
           two_img[i] = new unsigned short[width];
         int p1 = 0;

        for (int i = 0; i < height; i++)
        {
             for (int j = 0; j < width ; j++)
            {
               two_img[i][j] = imagein2[p1];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
               p1 = p1 + 1;
            }
        }

        qDebug() << "Image addition 3";

        unsigned short **three_img = new unsigned short*[height];

        for (int i = 0; i < height; i++)
            three_img[i] = new unsigned short[width];
          int p2 = 0;

         for (int i = 0; i < height; i++)
         {
              for (int j = 0; j < width ; j++)
             {
                three_img[i][j] = imagein3[p2];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
                p2 = p2 + 1;
             }
         }

         qDebug() << "Image addition 4";

//         unsigned short **four_img = new unsigned short*[height];

//         for (int i = 0; i < height; i++)
//             four_img[i] = new unsigned short[width];
//           int p3 = 0;
           int m=0;int n=0;

//          for (int i = 0; i < height; i++)
//          {
//               for (int j = 0; j < width ; j++)
//              {
//                 four_img[i][j] = imagein4[p3];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
//                 p3 = p3 + 1;
//              }
//          }
//          qDebug() << "Image addition5 ";


          unsigned short **Fin_img = new unsigned short*[height1];

          for (int i = 0; i < height1; i++)
              Fin_img[i] = new unsigned short[width1];


            for (int i = 0; i < height; i++)
            {
                 for (int j = 0; j < width ; j++)
                {
                   Fin_img[i][j] = one_img[i][j];
                }
            }
            qDebug() << "Image addition6 ";


            for (int i = 0; i < height; i++)
            {
                 for (int j = width; j < width1 ; j++)
                {
//                   qDebug()<<i<<j<<m<<n;
                   Fin_img[i][j] = two_img[m][n];
                   n=n+1;
                   if(n==width)
                   {
                       n=0;
                   }

                }
                m=m+1;
                if(m==width)
                {
                    m=0;
                }
            }
            m=0;
            n=0;

            qDebug() << "Image addition7 ";

            for (int i = height; i < height1; i++)
            {
                 for (int j = 0; j < width ; j++)
                {
                   Fin_img[i][j] = three_img[m][n];
                   n=n+1;
                   if(n==width)
                   {
                       n=0;
                   }
                }
                 m=m+1;
                 if(m==width)
                 {
                     m=0;
                 }
            }
            qDebug() << "Image addition8 ";
            m=0;
            n=0;

//            for (int i = height; i < height1; i++)
//            {
//                 for (int j = width; j < width1 ; j++)
//                {
//                   Fin_img[i][j] = four_img[m][n];
//                   n=n+1;
//                   if(n==width)
//                   {
//                       n=0;
//                   }
//                }
//                m=m+1;
//                if(m==width)
//                {
//                    m=0;
//                }
//            }
//            m=0;
//            n=0;
            qDebug() << "Image addition9";
            unsigned short *Fin_img_buffer = new unsigned short[width1*height1];     // Conversion of 2_Dimension to 1_Dimension_________________________
            for(int i=0;i<height1;i++)
            {
                for(int j=0;j<width1;j++)
                {
                    Fin_img_buffer[i*width1+j]=Fin_img[i][j];
                }
            }

            FILE* Fp831_cropped;
            QString cropped1= Simulation_Quad_Raw_Path+QString("\\Stitched original image.raw");
            fopen_s(&Fp831_cropped, cropped1.toStdString().c_str(), "wb+");
            fwrite(Fin_img_buffer, sizeof(unsigned short), width1 * height1, Fp831_cropped);

            fclose(Fp831_cropped);


//            // Assuming you have a vector to store the downsampled image
//            std::vector<unsigned short> downsampledImage(radSize * radSize);

//            // Call the function to downsample the image
//            downsampleImage(Fin_img_buffer, downsampledImage,width1,height1,radSize,radSize);

}

void MainWindow::saveMultiscanImageDicom(unsigned short *image, QString path, int imSize, int croppedheight, int gantrypos)
{
    qDebug()<<"hi, SaveImageToDicom1";
    path="D:\\CapturedImages\\20241218\\RT202402A05\\S22_P1\\FG1_FN1\\Beam1\\DailyImages\\DICOM\\Img_1.dcm";
    int Imagewidth=imSize;
    int ImageHeight=croppedheight;
    unsigned short *buffer = new unsigned short [Imagewidth*ImageHeight];

    buffer=image;

//    FILE* Fp831_cropped;
//    QString cropped1= path+QString("\\Stitched original image.raw");
//    fopen_s(&Fp831_cropped, cropped1.toStdString().c_str(), "wb+");
//    fwrite(buffer, sizeof(unsigned short), Imagewidth * ImageHeight, Fp831_cropped);

//    fclose(Fp831_cropped);

    qDebug()<<"Image size for multiscan"<<path<<imSize<<croppedheight<<gantrypos;

    //    //Create new Dicom Image

    gdcm::ImageWriter writer;
    gdcm::Image &image1 = writer.GetImage();
    image1.SetNumberOfDimensions(2);

    //Create Sequence
    gdcm::File &file = writer.GetFile();
    gdcm::DataSet &ds = file.GetDataSet();

    //    //UID Sequence
    gdcm::UIDGenerator suid;
    //    StudyInstanceUUID1 =suid.Generate();

    gdcm::Attribute<0x0010,0x0010,VR::PN,VM::VM1> PatientName = {"Aravinth"};
    ds.Insert( PatientName.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x0020,VR::LO,VM::VM1> PatientID = {"700"};
    ds.Insert( PatientID.GetAsDataElement() );


    gdcm::Attribute<0x0008,0x0064,VR::CS,VM::VM1> ConversionType = {""};
    ds.Insert( ConversionType.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x0030,VR::DA,VM::VM1> PatBirthDate = {"18-09-1996"};
    ds.Insert( PatBirthDate.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x0040,VR::CS,VM::VM1> PatientSex = {"MALE"};
    ds.Insert( PatientSex.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x1010,VR::AS,VM::VM1> PatientAge = {""};
    ds.Insert( PatientAge.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x1020,VR::DS,VM::VM1> PatientSize = {};
    ds.Insert( PatientSize.GetAsDataElement() );


    gdcm::Attribute<0x0020,0x000D,VR::UI,VM::VM1> StudyUID = {suid.Generate()};
    ds.Insert( StudyUID.GetAsDataElement() );


    QString date = QString(QDate::currentDate().toString("yyyyMMdd"));
    QString time = QString(QTime::currentTime().toString("hhmmss.zzzzzz"));

    gdcm::Attribute<0x0008,0x0020,VR::DA,VM::VM1> StudyDate = {date.toStdString().c_str()};
    ds.Insert( StudyDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0030,VR::TM,VM::VM1> StudyTime = {time.toStdString().c_str()};
    ds.Insert( StudyTime.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0090,VR::PN,VM::VM1> PhysicianName = {""};
    ds.Insert( PhysicianName.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0022,VR::DA,VM::VM1> AcquisitionDate = {date.toStdString().c_str()};
    ds.Insert( AcquisitionDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0032,VR::TM,VM::VM1> AcquisitionTime = {time.toStdString().c_str()};
    ds.Insert( AcquisitionTime.GetAsDataElement() );

    QString studyiD = /*StudyID+QString::number(fGroup)+fracno+beamNumberStr*/213;

    gdcm::Attribute<0x0020,0x0010,VR::SH,VM::VM1> studyID = {studyiD.toStdString().c_str()};
    ds.Insert( studyID.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x1030,VR::LO,VM::VM1> StudyDescriptionN = {"PELVIC"};
    ds.Insert(StudyDescriptionN.GetAsDataElement());

    gdcm::Attribute<0x0008,0x103e,VR::LO,VM::VM1> SeriesDescriptionN = {"ANAtomy"};
    ds.Insert(SeriesDescriptionN.GetAsDataElement());

    gdcm::Attribute<0x0008,0x0050,VR::SH,VM::VM1> AccessionNum = {""};
    ds.Insert( AccessionNum.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0060,VR::CS,VM::VM1> Modality = {"RTIMAGE"};
    ds.Insert( Modality.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1000,VR::LO,VM::VM1> SerialNumber = {"C05"}; //"987654321"
    ds.Insert( SerialNumber.GetAsDataElement() );

//    if(radProjCount==1 || (stereoProjCount1==1 && stereoProjCount2==0)|| (stereoProjCount2==1 && stereoProjCount1==0))
     QString commonSeriesUID = suid.Generate();

    gdcm::Attribute<0x0020,0x000E,VR::UI,VM::VM1> SeriesUID = {commonSeriesUID.toStdString().c_str()/*suid.Generate()*/};  //SeriesInstanceUID.toStdString().c_str()
    ds.Insert( SeriesUID.GetAsDataElement() );
    gdcm::Attribute<0x0020,0x0011,VR::IS,VM::VM1> SeriesNum = {/*1*/};
    ds.Insert( SeriesNum.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x1070,VR::PN,VM::VM1> OperatorName = {"Praveen"};
    ds.Insert( OperatorName.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x0052,VR::UI,VM::VM1> FrameOfReferenceUID = {suid.Generate()};
    ds.Insert( FrameOfReferenceUID.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x1040,VR::LO,VM::VM1> PositionReferenceIndicator = {""};
    ds.Insert( PositionReferenceIndicator.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0070,VR::LO,VM::VM1> Manufacturers = {"Panacea"};
    ds.Insert( Manufacturers.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0080,VR::LO,VM::VM1> InstitutionName = {"Hospital Name"};
    ds.Insert( InstitutionName.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x1090,VR::LO,VM::VM1> ManufacturerModelNames = {"Linac"};
    ds.Insert( ManufacturerModelNames.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1020,VR::LO,VM::VM1> SoftwareVersions = {"1.0.1"};
    ds.Insert( SoftwareVersions.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x0013,VR::IS,VM::VM1> InstanceNumber = {/*1*/};
    ds.Insert( InstanceNumber.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x0020,VR::CS,VM::VM2> PatOrientation = {""};
    ds.Insert( PatOrientation.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0023,VR::DA,VM::VM1> ContentDate = {date.toStdString().c_str()};
    ds.Insert( ContentDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0033,VR::TM,VM::VM1> ContentTime = {time.toStdString().c_str()};
    ds.Insert( ContentTime.GetAsDataElement() );

    ////    gdcm::Attribute<0x0008,0x0008,VR::CS,VM::VM4> ImageType = {"ORIGINAL","PRIMARY","SIMULATOR","SMX_FIELD"};
    gdcm::Attribute<0x0008,0x0008,VR::CS,VM::VM3> ImageType = {"ORIGINAL","PRIMARY","RADIOGRAPH"};
    ds.Insert( ImageType.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0002,VR::US,VM::VM1> SamplesPerPixel = {1};
    ds.Insert( SamplesPerPixel.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0004,VR::CS,VM::VM1> PhotometricInterpretation = {"MONOCHROME2"};
    ds.Insert( PhotometricInterpretation.GetAsDataElement() );

    int imSize1 = radSize;
    int imSize2 = croppedheight;
    ////    qDebug()<<"imSize"<<imSize;
    gdcm::Attribute<0x0028,0x0010,VR::US,VM::VM1> Rows = {imSize2};
    ds.Insert( Rows.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0011,VR::US,VM::VM1> Coloums = {imSize1};
    ds.Insert( Coloums.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0030,VR::DS,VM::VM2> ImgerPixelSpacing = {0.0754829,0.0754829};
    //    gdcm::Attribute<0x0028,0x0030,VR::DS,VM::VM2> ImgerPixelSpacing = {imaginPixelSpacing,imaginPixelSpacing};
    ds.Insert(ImgerPixelSpacing.GetAsDataElement());

    gdcm::Attribute<0x0028,0x0100,VR::US,VM::VM1> BitsAllocated = {16};
    ds.Insert( BitsAllocated.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0101,VR::US,VM::VM1> BitsStored = {16};
    ds.Insert( BitsStored.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0102,VR::US,VM::VM1> HighBit = {15};
    ds.Insert( HighBit.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0103,VR::US,VM::VM1> PixelRepresentation = {0000};
    ds.Insert( PixelRepresentation.GetAsDataElement());

    gdcm::Attribute<0x0028,0x0006,VR::US,VM::VM1> PlanarConfiguration = {};
    ds.Insert( PlanarConfiguration.GetAsDataElement());

    gdcm::Attribute<0x0028,0x0034,VR::IS,VM::VM2> PixelAspectRatio = {1,1};
    ds.Insert( PixelAspectRatio.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x1040,VR::CS,VM::VM1> PixelIntensityRelationship = {"LIN"};
    ds.Insert( PixelIntensityRelationship.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x1041,VR::SS,VM::VM1> PixelIntensityRelationshipSign = {1};
    ds.Insert( PixelIntensityRelationshipSign.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0002,VR::SH,VM::VM1> RTImageLabel = {"Beam"};
    ds.Insert( RTImageLabel.GetAsDataElement() );

    ////    gdcm::Attribute<0x3002,0x0004,VR::ST,VM::VM1> RTImageDescription = {"IMG"};
    ////    ds.Insert( RTImageDescription.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x000A,VR::CS,VM::VM1> ReportedValuesOrigin = {"OPERATOR"};
    ds.Insert( ReportedValuesOrigin.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x000C,VR::CS,VM::VM1> RTImagePlane = {"NORMAL"};
    ds.Insert( RTImagePlane.GetAsDataElement() );

        gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {/*detector1xShift+kV1xShift,detector1yShift+kV1yShift*/0,0,-350};
        //    gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {detectorxShift+imagerXCurrentPosition,detectoryShift+imagerYCurrentPosition};
        ds.Insert( XRayImageReceptorTranslation.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x000E,VR::DS,VM::VM1> XRayImageReceptorAngle = {0};
    ds.Insert( XRayImageReceptorAngle.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0010,VR::DS,VM::VM6> RTImageOrientation = {};
    ds.Insert( RTImageOrientation.GetAsDataElement() );

    float pixSpacing[2];


    double FAD,FID,detectorPixelPitch[2];

    FAD=921;
    FID=1696;
    detectorPixelPitch[0]=0.139;
    detectorPixelPitch[1]=0.139;

    pixSpacing[0]= detectorPixelPitch[0]*FAD/FID;
    pixSpacing[1]= detectorPixelPitch[1]*FAD/FID;

    float isocentre[2];

    isocentre[0] = radSize/2*pixSpacing[0];
//    isocentre[1] = radSize[1]/2*pixSpacing[1];
    isocentre[1] = croppedheight/2*pixSpacing[1];

    float RTimagePosX,RTimagePosY;

    RTimagePosX = -isocentre[0];
//    RTimagePosY = (radSize[1]*pixSpacing[1]) - isocentre[1];
    RTimagePosY = (croppedheight*pixSpacing[1]) - isocentre[1];

    gdcm::Attribute<0x3002,0x0012,VR::DS,VM::VM2> RTImagePosition = {RTimagePosX,RTimagePosY};
    ds.Insert( RTImagePosition.GetAsDataElement() );
    gdcm::Attribute<0x3002,0x0020,VR::SH,VM::VM1> RadiationMachineName = {"LINAC"};
    ds.Insert( RadiationMachineName.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0022,VR::DS,VM::VM1> RadiationMachineSAD = {FAD};
    ds.Insert( RadiationMachineSAD.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0026,VR::DS,VM::VM1> RTImageSID = {FID};
    ds.Insert( RTImageSID.GetAsDataElement() );

    gdcm::MediaStorage msUID = gdcm::MediaStorage::RTImageStorage;
    std::string h=msUID.GetString();
    gdcm::Attribute<0x0008,0x0016,VR::UI,VM::VM1> SOPClassUID = {h};
    ds.Insert( SOPClassUID.GetAsDataElement() );

    gdcm::UIDGenerator gen;
    gdcm::Attribute<0x0008,0x0018,VR::UI,VM::VM1> sOPInstanceUID = {gen.Generate()};
    ds.Insert( sOPInstanceUID.GetAsDataElement() );

    ////    /*********SEQUENCE-START*********/
    gdcm::SmartPointer<gdcm::SequenceOfItems> ReferencedRTPlanSequence = new gdcm::SequenceOfItems();
    ReferencedRTPlanSequence->SetLengthToUndefined();

    gdcm::MediaStorage ms1 = gdcm::MediaStorage::RTImageStorage;
    std::string k=ms1.GetString();
    gdcm::Attribute<0x0008,0x1150,VR::UI,VM::VM1> ReferencedSOPClassUID = {k};
    gdcm::DataElement rfID = ReferencedSOPClassUID.GetAsDataElement();

    gdcm::Attribute<0x0008,0x1155,VR::UI,VM::VM1> ReferencedSOPInstanceUID = {suid.Generate()/*commonReferenceSopInstanceUID.toStdString().c_str()*/};
    gdcm::DataElement refSOPID = ReferencedSOPInstanceUID.GetAsDataElement();

    gdcm::Item ReferencedRTPlanItem;
    gdcm::DataSet &dsReferencedRTPlan = ReferencedRTPlanItem.GetNestedDataSet();
    dsReferencedRTPlan.Insert( rfID );
    dsReferencedRTPlan.Insert(refSOPID);

    ReferencedRTPlanSequence->AddItem(ReferencedRTPlanItem);

    gdcm::DataElement desReferencedRTPlan( gdcm::Tag(0x300C,0x0002) );
    desReferencedRTPlan.SetVR(gdcm::VR::SQ);
    desReferencedRTPlan.SetValue(*ReferencedRTPlanSequence);
    desReferencedRTPlan.SetVLToUndefined();
    ds.Insert(desReferencedRTPlan);
    ////    /*********SEQUENCE-END*********/

    gdcm::Attribute<0x0018,0x0060,VR::DS,VM::VM1> KVP = {80};
    ds.Insert( KVP.GetAsDataElement());

    gdcm::Attribute<0x0018,0x1151,VR::IS,VM::VM1> XRayTubeCurrent = {100};
    ds.Insert( XRayTubeCurrent.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1150,VR::IS,VM::VM1> ExposureTime = {32};
    ds.Insert( ExposureTime.GetAsDataElement() );


    ////    /*********SEQUENCE-END*********/

    gdcm::Attribute<0x300A,0x011E,VR::DS,VM::VM1> GantryAngle = {(gantrypos)};
    ds.Insert(GantryAngle.GetAsDataElement());

    ////    //    gdcm::Attribute<0x300A,0x014A,VR::FL,VM::VM1> GantryPitchAngle = {};
    ////    //    ds.Insert(GantryPitchAngle.GetAsDataElement());

    ////    gdcm::Attribute<0x300A,0x0120,VR::DS,VM::VM1> BeamLimitingDeviceAngle = {(360.0-colliThetaCurrentPosition)};
    ////    ds.Insert(BeamLimitingDeviceAngle.GetAsDataElement());

    gdcm::Attribute<0x300A,0x0122,VR::DS,VM::VM1> PatientSupportAngle = {(0)};
    ds.Insert(PatientSupportAngle.GetAsDataElement());

    gdcm::Attribute<0x300A,0x00B3,VR::CS,VM::VM1> PrimaryDosimeterUnit = {"MU"};
    ds.Insert( PrimaryDosimeterUnit.GetAsDataElement() );

    gdcm::Attribute<0x300A,0x0128,VR::DS,VM::VM1> TableTopVerticalPosition = {(0)};
    ds.Insert(TableTopVerticalPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x0129,VR::DS,VM::VM1> TableTopLongitudinalPosition = {(0)};
    ds.Insert(TableTopLongitudinalPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x012A,VR::DS,VM::VM1> TableTopLateralPosition = {(0)};
    ds.Insert(TableTopLateralPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x012C,VR::DS,VM::VM3> IsocenterPosition = {isocentre[0],isocentre[1],0};
    ds.Insert( IsocenterPosition.GetAsDataElement() );

    gdcm::Attribute<0x300A,0x00F0,VR::IS,VM::VM1> NumberOfBlocks = {0};
    ds.Insert(NumberOfBlocks.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1052,VR::DS,VM::VM1> RescaleIntercept = {0.0};
    ds.Insert(RescaleIntercept.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1053,VR::DS,VM::VM1> RescaleSlope = {1.0};
    ds.Insert(RescaleSlope.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1054,VR::LO,VM::VM1> RescaleType = {"US"};
    ds.Insert(RescaleType.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1050,VR::DS,VM::VM1> WindowCenter = {32768};
    ds.Insert(WindowCenter.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1051,VR::DS,VM::VM1> WindowWidth = {65535};
    ds.Insert(WindowWidth.GetAsDataElement());

    gdcm::Attribute<0x300C,0x0006,VR::IS,VM::VM1> ReferencedBeamNumber = {1};
    ds.Insert(ReferencedBeamNumber.GetAsDataElement());

    gdcm::Attribute<0x300E,0x0002,VR::CS,VM::VM1> ApprovalStatus = {"UNAPPROVED"};
    ds.Insert(ApprovalStatus.GetAsDataElement());

    gdcm::Attribute<0x0008,0x0005,VR::CS,VM::VM1> SpecificCharacterSet = {"ISO_IR_100"};
    ds.Insert(SpecificCharacterSet.GetAsDataElement());

    unsigned int dims[2] = {};
    dims[0] = imSize1;
    dims[1] = imSize2;
    image1.SetDimensions( dims );

    image1.SetOrigin(0,0);
    image1.SetOrigin(1,1);

    ////    // qDebug()<<"PixelSpacing"<<double(int(imaginPixelSpacing*100.0))/100.0<<double(int(imaginPixelSpacing*100.0))/100.0;

    double *spacing1 = new double[2];
    ////    //    spacing1[0]=double(int(imaginPixelSpacing*100.0))/100.0;
    ////    //    spacing1[1]=double(int(imaginPixelSpacing*100.0))/100.0;
    spacing1[0]=pixSpacing[0];
    spacing1[1]=pixSpacing[1];

    image1.SetSpacing(spacing1);
    gdcm::PixelFormat pf = gdcm::PixelFormat::UINT16;
    pf.SetSamplesPerPixel( 1 );
    image1.SetPixelFormat( pf );
    qDebug()<<"hi";

    gdcm::PhotometricInterpretation pi =
            gdcm::PhotometricInterpretation::MONOCHROME2;
    image1.SetPhotometricInterpretation( pi );

    image1.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );

    gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
    pixeldata.SetByteValue( (char*)buffer, imSize*imSize2*sizeof(unsigned short) );
    image1.SetDataElement( pixeldata );

    writer.SetFileName(path.toStdString().c_str());
    writer.SetFile(file);

    if (!writer.Write()) {
        qDebug("Dicom Image Write Error!");
    }
}


void MainWindow::on_ImageMerge_clicked()
{
    int left,top,right,bottom,croppedWidth,croppedHeight;

    int width = 3072;  // Assuming width is 3072
    int height = 3072; // Assuming height is 3072

    QString filename = Simulation_Quad_Raw_Path+QString("\\proj_1.raw");
    if (filename.isEmpty())
    {
        qDebug()<<"Could not open file";
    }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short *dispImg = new unsigned short[width*height];

    fread(dispImg,sizeof(unsigned short),width*height,Img);

    // Find the bounding box of the non-black region
    left = 0;  // Left remains 0 for cropping from upper height
    top = 450;   // Top remains 0 for cropping from upper height
    right = 0;  // Width - 1, assuming width is 3072
    bottom = 3071;  // Adjust bottom for upper height cropping


    // Crop the image using the bounding box
    croppedWidth = right - left + 1;
    croppedHeight = bottom - top + 1;
    unsigned short* croppedImage = new unsigned short[croppedWidth * croppedHeight];

    // Adjusting height for upper height cropping
    height = bottom + 1;

    // Copy upper part of the image to croppedImage
    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            croppedImage[y * croppedWidth + x] = dispImg[(top + y) * width + (left + x)];
        }
    }


    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

    FILE* Fp1_cropped;
    QString cropped1=Simulation_Quad_Raw_Path+QString("\\Quad_1.raw");
    fopen_s(&Fp1_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(croppedImage, sizeof(unsigned short), croppedWidth * croppedHeight, Fp1_cropped);
    fclose(Fp1_cropped);

    fclose(Img);
    delete[] dispImg;
    delete[] croppedImage;


//    QString filename1 = Simulation_Quad_Raw_Path+QString("\\proj_2.raw");
//    if (filename1.isEmpty())
//    {
//        qDebug()<<"Could not open file";
//    }
//    FILE * Img1;
//    Img1= fopen(filename1.toStdString().c_str(),"rb");

//    unsigned short *dispImg1 = new unsigned short[width*height];

//    fread(dispImg1,sizeof(unsigned short),width*height,Img1);

//    // Find the bounding box of the non-black region
//    left = 450;  // Left remains 0 for cropping from upper height
//    top = 0;   // Top remains 0 for cropping from upper height
//    right = 3071;  // Width - 1, assuming width is 3072
//    bottom = 3071-450;  // Adjust bottom for upper height cropping


//    // Crop the image using the bounding box
//    croppedWidth = right - left + 1;
//    croppedHeight = bottom - top + 1;
//    unsigned short* croppedImage1 = new unsigned short[croppedWidth * croppedHeight];

//    // Adjusting height for upper height cropping
////    height = bottom + 1;

//    // Copy upper part of the image to croppedImage
//    for (int y = 0; y < croppedHeight; ++y) {
//        for (int x = 0; x < croppedWidth; ++x) {
//            croppedImage1[y * croppedWidth + x] = dispImg1[(top + y) * width + (left + x)];
//        }
//    }


//    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

//    FILE* Fp2_cropped;
//    QString cropped2=Simulation_Quad_Raw_Path+QString("\\Quad_2.raw");
//    fopen_s(&Fp2_cropped, cropped2.toStdString().c_str(), "wb+");
//    fwrite(croppedImage1, sizeof(unsigned short), croppedWidth * croppedHeight, Fp2_cropped);
//    fclose(Fp2_cropped);

//    fclose(Img1);
//    delete[] dispImg1;
//    delete[] croppedImage1;


//    QString filename2 = Simulation_Quad_Raw_Path+QString("\\proj_3.raw");
//    if (filename2.isEmpty())
//    {
//        qDebug()<<"Could not open file";
//    }
//    FILE * Img2;
//    Img2= fopen(filename2.toStdString().c_str(),"rb");

//    unsigned short *dispImg2 = new unsigned short[width*height];

//    fread(dispImg2,sizeof(unsigned short),width*height,Img2);

//    // Find the bounding box of the non-black region
//    left = 0;  // Left remains 0 for cropping from upper height
//    top = 0;   // Top remains 0 for cropping from upper height
//    right = 3071-450;  // Width - 1, assuming width is 3072
//    bottom = 3071-450;  // Adjust bottom for upper height cropping


//    // Crop the image using the bounding box
//    croppedWidth = right - left + 1;
//    croppedHeight = bottom - top + 1;
//    unsigned short* croppedImage2 = new unsigned short[croppedWidth * croppedHeight];

//    // Adjusting height for upper height cropping
////    height = bottom + 1;

//    // Copy upper part of the image to croppedImage
//    for (int y = 0; y < croppedHeight; ++y) {
//        for (int x = 0; x < croppedWidth; ++x) {
//            croppedImage2[y * croppedWidth + x] = dispImg2[(top + y) * width + (left + x)];
//        }
//    }

//    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

//    FILE* Fp3_cropped;
//    QString cropped3=Simulation_Quad_Raw_Path+QString("\\Quad_3.raw");
//    fopen_s(&Fp3_cropped, cropped3.toStdString().c_str(), "wb+");
//    fwrite(croppedImage2, sizeof(unsigned short), croppedWidth * croppedHeight, Fp3_cropped);
//    fclose(Fp3_cropped);

//    fclose(Img2);
//    delete[] dispImg2;
//    delete[] croppedImage2;


//    ImageStitching();
}

void MainWindow::on_single_crop_clicked()
{
    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = 74; // Starting row
    int crop_end = 2997; // Ending row
    int cropped_height = crop_end - crop_start + 1;


    unsigned short* imagein1 = new unsigned short[width * height];
    QString LoadImg1 = Simulation_Quad_Raw_Path + QString("\\proj_2.raw");

    FILE* Fp_in1;
    fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
    fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
    fclose(Fp_in1);

    unsigned short* cropped_image = new unsigned short[width * cropped_height];
    memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);


    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image + row * width, imagein1 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }


//    QString SaveImg1 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_out1;
//    fopen_s(&Fp_out1, SaveImg1.toStdString().c_str(), "wb+");
//    if (!Fp_out1) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein1;
//        delete[] cropped_image;
////        return -1;
//    }

//    fwrite(cropped_image, sizeof(unsigned short), width * cropped_height, Fp_out1);
//    fclose(Fp_out1);


//    // Clean up


//    QString filename = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");
//    unsigned short* Image=new unsigned short[width * cropped_height];
//    fread(Image,1,width * cropped_height*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[width * cropped_height];
    for(int i=0;i<width * cropped_height;i++)
    {
        arr[i]=((cropped_image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,cropped_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    delete[] imagein1;
    delete[] cropped_image;
    delete[] arr;

}

void MainWindow::on_Two_imagecrop_clicked()
{
    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = /*74*/77.122; // Starting row
    int crop_end = /*2997*/2917.756; // Ending row
    int cropped_height = crop_end - crop_start + 1;

    qDebug()<<"first crop start";


    unsigned short* imagein1 = new unsigned short[width * height];
    QString LoadImg1 = Simulation_Quad_Raw_Path + QString("\\proj_1.raw");

    FILE* Fp_in1;
    fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
    fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
    fclose(Fp_in1);

     qDebug()<<"first crop start---1";


    unsigned short* cropped_image = new unsigned short[width * cropped_height];
    memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);

    qDebug()<<"first crop start---2";

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image + row * width, imagein1 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

    qDebug()<<"first crop start---3";

//    QString SaveImg1 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_out1;
//    fopen_s(&Fp_out1, SaveImg1.toStdString().c_str(), "wb+");
//    if (!Fp_out1) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein1;
//        delete[] cropped_image;
////        return -1;
//    }

//    qDebug()<<"first crop start---4";
//    fwrite(cropped_image, sizeof(unsigned short), width * cropped_height, Fp_out1);
//    fclose(Fp_out1);

    qDebug()<<"first crop start---end";
//    delete[] imagein1;
//    delete[] cropped_image;

    qDebug()<<"second crop start";
    unsigned short* imagein2 = new unsigned short[width * height];
    QString LoadImg2 = Simulation_Quad_Raw_Path + QString("\\proj_2.raw");

    qDebug()<<"second crop start--1";

    FILE* Fp_in2;
    fopen_s(&Fp_in2, LoadImg2.toStdString().c_str(), "rb+");
    fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
    fclose(Fp_in2);

    qDebug()<<"second crop start--2";


    unsigned short* cropped_image_1 = new unsigned short[width * cropped_height];
    memset(cropped_image_1, 0, sizeof(unsigned short) * width * cropped_height);

    qDebug()<<"second crop start--3";

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_1 + row * width, imagein2 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

    qDebug()<<"second crop start--4";

//    QString SaveImg2 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_out2;
//    fopen_s(&Fp_out2, SaveImg2.toStdString().c_str(), "wb+");
//    if (!Fp_out2) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein2;
//        delete[] cropped_image_1;
////        return -1;
//    }
//    qDebug()<<"second crop start--5";
//    fwrite(cropped_image_1, sizeof(unsigned short), width * cropped_height, Fp_out2);
//    fclose(Fp_out2);

    qDebug()<<"second crop start--6";

//    delete[] imagein2;
//    delete[] cropped_image_1;


//    int merged_height = cropped_height * 3; // Total height after merging

//    unsigned short* merged_image = new unsigned short[width * merged_height];
//    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

//    // Load and copy first cropped image
//    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_in4;
//    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
//    fread(merged_image, sizeof(unsigned short), width * cropped_height, Fp_in4);
//    fclose(Fp_in4);

//    // Load and copy second cropped image
//    QString LoadImg5 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_in5;
//    fopen_s(&Fp_in5, LoadImg5.toStdString().c_str(), "rb+");
//    fread(merged_image + width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in5);
//    fclose(Fp_in5);

//    // Load and copy third cropped image
//    QString LoadImg6 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_in6;
//    fopen_s(&Fp_in6, LoadImg6.toStdString().c_str(), "rb+");
//    fread(merged_image + 2 * width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in6);
//    fclose(Fp_in6);

//    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

//    // Clean up
//    delete[] merged_image;

    int merged_height = cropped_height * 2; // Total height after merging

    // Allocate memory for the merged image
    unsigned short* merged_image = new unsigned short[width * merged_height];
    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

    qDebug()<<"first merge"<<merged_height;

    // Copy the first cropped image into the merged buffer
    memcpy(merged_image, cropped_image, sizeof(unsigned short) * width * cropped_height);

    qDebug()<<"first merge---1";

    // Copy the second cropped image into the merged buffer
    memcpy(merged_image + width * cropped_height, cropped_image_1, sizeof(unsigned short) * width * cropped_height);

    qDebug()<<"first merge---2";

//    // Copy the third cropped image into the merged buffer
//    memcpy(merged_image + 2 * width * cropped_height, cropped_image_2, sizeof(unsigned short) * width * cropped_height);

    // Save the merged image
    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
    FILE* Fp_out;
    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
    if (!Fp_out) {
        delete[] merged_image;
        // std::cerr << "Failed to open output file!" << std::endl;
        // return -1;
    }
    qDebug()<<"first merge---3";
    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
    fclose(Fp_out);

//    qDebug()<<"first merge---4";

//    // Clean up

//    qDebug()<<"first merge---5";


//    QString filename = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned short* Image=new unsigned short[width * merged_height];
//    fread(Image,1,width * merged_height*sizeof(unsigned short),Img);
    qDebug()<<"first merge---6";
    unsigned char* arr=new unsigned char[width * merged_height];
    for(int i=0;i<width * merged_height;i++)
    {
        arr[i]=((merged_image[i]*255)/65535);
    }
    qDebug()<<"first merge---7";
//    qDebug()<<arr[20];
    myImage = QImage(arr,width,merged_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);
    qDebug()<<"first merge---8";

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    delete[] imagein1;
    delete[] cropped_image;

    delete[] imagein2;
    delete[] cropped_image_1;

    delete[] merged_image;
    delete[] arr;
}

void MainWindow::on_three_imagecrop_clicked()
{
    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = 74; // Starting row
    int crop_end = 2997; // Ending row
    int cropped_height = crop_end - crop_start + 1;


    unsigned short* imagein1 = new unsigned short[width * height];
    QString LoadImg1 = Simulation_Quad_Raw_Path + QString("\\proj_1.raw");

    FILE* Fp_in1;
    fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
    fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
    fclose(Fp_in1);


    unsigned short* cropped_image = new unsigned short[width * cropped_height];
    memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image + row * width, imagein1 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg1 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_out1;
//    fopen_s(&Fp_out1, SaveImg1.toStdString().c_str(), "wb+");
//    if (!Fp_out1) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein1;
//        delete[] cropped_image;
////        return -1;
//    }
//    fwrite(cropped_image, sizeof(unsigned short), width * cropped_height, Fp_out1);
//    fclose(Fp_out1);

//    delete[] imagein1;
//    delete[] cropped_image;

    unsigned short* imagein2 = new unsigned short[width * height];
    QString LoadImg2 = Simulation_Quad_Raw_Path + QString("\\proj_2.raw");

    FILE* Fp_in2;
    fopen_s(&Fp_in2, LoadImg2.toStdString().c_str(), "rb+");
    fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
    fclose(Fp_in2);


    unsigned short* cropped_image_1 = new unsigned short[width * cropped_height];
    memset(cropped_image_1, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_1 + row * width, imagein2 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg2 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_out2;
//    fopen_s(&Fp_out2, SaveImg2.toStdString().c_str(), "wb+");
//    if (!Fp_out2) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein2;
//        delete[] cropped_image_1;
////        return -1;
//    }
//    fwrite(cropped_image_1, sizeof(unsigned short), width * cropped_height, Fp_out2);
//    fclose(Fp_out2);

//    delete[] imagein2;
//    delete[] cropped_image_1;

    unsigned short* imagein3 = new unsigned short[width * height];
    QString LoadImg3 = Simulation_Quad_Raw_Path + QString("\\proj_3.raw");

    FILE* Fp_in3;
    fopen_s(&Fp_in3, LoadImg3.toStdString().c_str(), "rb+");
    fread(imagein3, sizeof(unsigned short), width * height, Fp_in3);
    fclose(Fp_in3);


    unsigned short* cropped_image_2 = new unsigned short[width * cropped_height];
    memset(cropped_image_2, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_2 + row * width, imagein3 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg3 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_out3;
//    fopen_s(&Fp_out3, SaveImg3.toStdString().c_str(), "wb+");
//    if (!Fp_out3) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein3;
//        delete[] cropped_image_2;
////        return -1;
//    }
//    fwrite(cropped_image_2, sizeof(unsigned short), width * cropped_height, Fp_out3);
//    fclose(Fp_out3);

//    delete[] imagein3;
//    delete[] cropped_image_2;


//    int merged_height = cropped_height * 3; // Total height after merging

//    unsigned short* merged_image = new unsigned short[width * merged_height];
//    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

//    // Load and copy first cropped image
//    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_in4;
//    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
//    fread(merged_image, sizeof(unsigned short), width * cropped_height, Fp_in4);
//    fclose(Fp_in4);

//    // Load and copy second cropped image
//    QString LoadImg5 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_in5;
//    fopen_s(&Fp_in5, LoadImg5.toStdString().c_str(), "rb+");
//    fread(merged_image + width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in5);
//    fclose(Fp_in5);

//    // Load and copy third cropped image
//    QString LoadImg6 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_in6;
//    fopen_s(&Fp_in6, LoadImg6.toStdString().c_str(), "rb+");
//    fread(merged_image + 2 * width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in6);
//    fclose(Fp_in6);

//    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

//    // Clean up
//    delete[] merged_image;

    int merged_height = cropped_height * 3; // Total height after merging

    qDebug()<<"merged height"<<merged_height;

    // Allocate memory for the merged image
    unsigned short* merged_image = new unsigned short[width * merged_height];
    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

    // Copy the first cropped image into the merged buffer
    memcpy(merged_image, cropped_image, sizeof(unsigned short) * width * cropped_height);

    // Copy the second cropped image into the merged buffer
    memcpy(merged_image + width * cropped_height, cropped_image_1, sizeof(unsigned short) * width * cropped_height);

    // Copy the third cropped image into the merged buffer
    memcpy(merged_image + 2 * width * cropped_height, cropped_image_2, sizeof(unsigned short) * width * cropped_height);

    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

    // Clean up


//    QString filename = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned short* Image=new unsigned short[width * merged_height];
//    fread(Image,1,width * merged_height*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[width * merged_height];
    for(int i=0;i<width * merged_height;i++)
    {
        arr[i]=((merged_image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,width,merged_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    delete[] imagein1;
    delete[] cropped_image;

    delete[] imagein2;
    delete[] cropped_image_1;

    delete[] imagein3;
    delete[] cropped_image_2;
    delete[] merged_image;
    delete[] arr;
}

void MainWindow::on_Original_image_clicked()
{
        QString filename = Simulation_Quad_Raw_Path + QString("\\proj_3.raw");
        if (filename.isEmpty())
           {
               qDebug()<<"Could not open file";
           }
        FILE * Img;
        Img= fopen(filename.toStdString().c_str(),"rb");

        unsigned short* Image=new unsigned short[radSize * radSize];
        fread(Image,1,radSize * radSize*sizeof(unsigned short),Img);
        fclose(Img);
        unsigned char* arr=new unsigned char[radSize * radSize];
        for(int i=0;i<radSize * radSize;i++)
        {
            arr[i]=((Image[i]*255)/65535);
        }
    //    qDebug()<<arr[20];
        myImage = QImage(arr,radSize,radSize,QImage::Format_Grayscale8);
        item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
        scene = new QGraphicsScene();
        view = new QGraphicsView(scene);
        //Evt->setSceneRect(200,200,1536,1536);
        ui->graphicsViewAP->setScene(scene);
        //item->setPos(1536-200,1536-200);

       // ui->graphicsView->setSceneRect(-200,400,100,100);
        ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
        scene->addItem(item);

        delete[] arr;
        delete[] Image;
}

void MainWindow::on_Four_Image_crop_clicked()
{
    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = 74; // Starting row
    int crop_end = 2997; // Ending row
    int cropped_height = crop_end - crop_start + 1;


    unsigned short* imagein1 = new unsigned short[width * height];
    QString LoadImg1 = Simulation_Quad_Raw_Path + QString("\\proj_1.raw");

    FILE* Fp_in1;
    fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
    fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
    fclose(Fp_in1);


    unsigned short* cropped_image = new unsigned short[width * cropped_height];
    memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image + row * width, imagein1 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg1 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_out1;
//    fopen_s(&Fp_out1, SaveImg1.toStdString().c_str(), "wb+");
//    if (!Fp_out1) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein1;
//        delete[] cropped_image;
////        return -1;
//    }
//    fwrite(cropped_image, sizeof(unsigned short), width * cropped_height, Fp_out1);
//    fclose(Fp_out1);

//    delete[] imagein1;
//    delete[] cropped_image;

    unsigned short* imagein2 = new unsigned short[width * height];
    QString LoadImg2 = Simulation_Quad_Raw_Path + QString("\\proj_2.raw");

    FILE* Fp_in2;
    fopen_s(&Fp_in2, LoadImg2.toStdString().c_str(), "rb+");
    fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
    fclose(Fp_in2);


    unsigned short* cropped_image_1 = new unsigned short[width * cropped_height];
    memset(cropped_image_1, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_1 + row * width, imagein2 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg2 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_out2;
//    fopen_s(&Fp_out2, SaveImg2.toStdString().c_str(), "wb+");
//    if (!Fp_out2) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein2;
//        delete[] cropped_image_1;
////        return -1;
//    }
//    fwrite(cropped_image_1, sizeof(unsigned short), width * cropped_height, Fp_out2);
//    fclose(Fp_out2);

//    delete[] imagein2;
//    delete[] cropped_image_1;

    unsigned short* imagein3 = new unsigned short[width * height];
    QString LoadImg3 = Simulation_Quad_Raw_Path + QString("\\proj_3.raw");

    FILE* Fp_in3;
    fopen_s(&Fp_in3, LoadImg3.toStdString().c_str(), "rb+");
    fread(imagein3, sizeof(unsigned short), width * height, Fp_in3);
    fclose(Fp_in3);


    unsigned short* cropped_image_2 = new unsigned short[width * cropped_height];
    memset(cropped_image_2, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_2 + row * width, imagein3 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }


    unsigned short* imagein4 = new unsigned short[width * height];
    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\proj_4.raw");

    FILE* Fp_in4;
    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
    fread(imagein4, sizeof(unsigned short), width * height, Fp_in4);
    fclose(Fp_in4);


    unsigned short* cropped_image_3 = new unsigned short[width * cropped_height];
    memset(cropped_image_3, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_3 + row * width, imagein4 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg3 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_out3;
//    fopen_s(&Fp_out3, SaveImg3.toStdString().c_str(), "wb+");
//    if (!Fp_out3) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein3;
//        delete[] cropped_image_2;
////        return -1;
//    }
//    fwrite(cropped_image_2, sizeof(unsigned short), width * cropped_height, Fp_out3);
//    fclose(Fp_out3);

//    delete[] imagein3;
//    delete[] cropped_image_2;


//    int merged_height = cropped_height * 3; // Total height after merging

//    unsigned short* merged_image = new unsigned short[width * merged_height];
//    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

//    // Load and copy first cropped image
//    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_in4;
//    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
//    fread(merged_image, sizeof(unsigned short), width * cropped_height, Fp_in4);
//    fclose(Fp_in4);

//    // Load and copy second cropped image
//    QString LoadImg5 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_in5;
//    fopen_s(&Fp_in5, LoadImg5.toStdString().c_str(), "rb+");
//    fread(merged_image + width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in5);
//    fclose(Fp_in5);

//    // Load and copy third cropped image
//    QString LoadImg6 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_in6;
//    fopen_s(&Fp_in6, LoadImg6.toStdString().c_str(), "rb+");
//    fread(merged_image + 2 * width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in6);
//    fclose(Fp_in6);

//    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

//    // Clean up
//    delete[] merged_image;

    int merged_height = cropped_height * 4; // Total height after merging

    qDebug()<<"merged height"<<merged_height;

    // Allocate memory for the merged image
    unsigned short* merged_image = new unsigned short[width * merged_height];
    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

    // Copy the first cropped image into the merged buffer
    memcpy(merged_image, cropped_image, sizeof(unsigned short) * width * cropped_height);

    // Copy the second cropped image into the merged buffer
    memcpy(merged_image + width * cropped_height, cropped_image_1, sizeof(unsigned short) * width * cropped_height);

    // Copy the third cropped image into the merged buffer
    memcpy(merged_image + 2 * width * cropped_height, cropped_image_2, sizeof(unsigned short) * width * cropped_height);

    // Copy the fourth cropped image into the merged buffer
    memcpy(merged_image + 3 * width * cropped_height, cropped_image_3, sizeof(unsigned short) * width * cropped_height);

    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

    // Clean up


//    QString filename = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned short* Image=new unsigned short[width * merged_height];
//    fread(Image,1,width * merged_height*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[width * merged_height];
    for(int i=0;i<width * merged_height;i++)
    {
        arr[i]=((merged_image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,width,merged_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    delete[] imagein1;
    delete[] cropped_image;

    delete[] imagein2;
    delete[] cropped_image_1;

    delete[] imagein3;
    delete[] cropped_image_2;

    delete[] imagein4;
    delete[] cropped_image_3;
    delete[] merged_image;
    delete[] arr;
}

void MainWindow::on_pushButton_2_clicked()
{
    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = 74; // Starting row
    int crop_end = 2997; // Ending row
    int cropped_height = crop_end - crop_start + 1;


    unsigned short* imagein1 = new unsigned short[width * height];
    QString LoadImg1 = Simulation_Quad_Raw_Path + QString("\\proj_1.raw");

    FILE* Fp_in1;
    fopen_s(&Fp_in1, LoadImg1.toStdString().c_str(), "rb+");
    fread(imagein1, sizeof(unsigned short), width * height, Fp_in1);
    fclose(Fp_in1);


    unsigned short* cropped_image = new unsigned short[width * cropped_height];
    memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image + row * width, imagein1 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg1 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_out1;
//    fopen_s(&Fp_out1, SaveImg1.toStdString().c_str(), "wb+");
//    if (!Fp_out1) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein1;
//        delete[] cropped_image;
////        return -1;
//    }
//    fwrite(cropped_image, sizeof(unsigned short), width * cropped_height, Fp_out1);
//    fclose(Fp_out1);

//    delete[] imagein1;
//    delete[] cropped_image;

    unsigned short* imagein2 = new unsigned short[width * height];
    QString LoadImg2 = Simulation_Quad_Raw_Path + QString("\\proj_2.raw");

    FILE* Fp_in2;
    fopen_s(&Fp_in2, LoadImg2.toStdString().c_str(), "rb+");
    fread(imagein2, sizeof(unsigned short), width * height, Fp_in2);
    fclose(Fp_in2);


    unsigned short* cropped_image_1 = new unsigned short[width * cropped_height];
    memset(cropped_image_1, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_1 + row * width, imagein2 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg2 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_out2;
//    fopen_s(&Fp_out2, SaveImg2.toStdString().c_str(), "wb+");
//    if (!Fp_out2) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein2;
//        delete[] cropped_image_1;
////        return -1;
//    }
//    fwrite(cropped_image_1, sizeof(unsigned short), width * cropped_height, Fp_out2);
//    fclose(Fp_out2);

//    delete[] imagein2;
//    delete[] cropped_image_1;

    unsigned short* imagein3 = new unsigned short[width * height];
    QString LoadImg3 = Simulation_Quad_Raw_Path + QString("\\proj_3.raw");

    FILE* Fp_in3;
    fopen_s(&Fp_in3, LoadImg3.toStdString().c_str(), "rb+");
    fread(imagein3, sizeof(unsigned short), width * height, Fp_in3);
    fclose(Fp_in3);


    unsigned short* cropped_image_2 = new unsigned short[width * cropped_height];
    memset(cropped_image_2, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_2 + row * width, imagein3 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }


    unsigned short* imagein4 = new unsigned short[width * height];
    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\proj_4.raw");

    FILE* Fp_in4;
    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
    fread(imagein4, sizeof(unsigned short), width * height, Fp_in4);
    fclose(Fp_in4);


    unsigned short* cropped_image_3 = new unsigned short[width * cropped_height];
    memset(cropped_image_3, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_3 + row * width, imagein4 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }


    unsigned short* imagein5 = new unsigned short[width * height];
    QString LoadImg5 = Simulation_Quad_Raw_Path + QString("\\proj_5.raw");

    FILE* Fp_in5;
    fopen_s(&Fp_in5, LoadImg5.toStdString().c_str(), "rb+");
    fread(imagein5, sizeof(unsigned short), width * height, Fp_in5);
    fclose(Fp_in5);

    unsigned short* cropped_image_4 = new unsigned short[width * cropped_height];
    memset(cropped_image_4, 0, sizeof(unsigned short) * width * cropped_height);

    // Copy the central region
    for (int row = 0; row < cropped_height; ++row) {
        memcpy(cropped_image_4 + row * width, imagein5 + (crop_start + row) * width, sizeof(unsigned short) * width);
    }

//    QString SaveImg3 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_out3;
//    fopen_s(&Fp_out3, SaveImg3.toStdString().c_str(), "wb+");
//    if (!Fp_out3) {
////        std::cerr << "Failed to open output file!" << std::endl;
//        delete[] imagein3;
//        delete[] cropped_image_2;
////        return -1;
//    }
//    fwrite(cropped_image_2, sizeof(unsigned short), width * cropped_height, Fp_out3);
//    fclose(Fp_out3);

//    delete[] imagein3;
//    delete[] cropped_image_2;


//    int merged_height = cropped_height * 3; // Total height after merging

//    unsigned short* merged_image = new unsigned short[width * merged_height];
//    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

//    // Load and copy first cropped image
//    QString LoadImg4 = Simulation_Quad_Raw_Path + QString("\\Multi_1.raw");
//    FILE* Fp_in4;
//    fopen_s(&Fp_in4, LoadImg4.toStdString().c_str(), "rb+");
//    fread(merged_image, sizeof(unsigned short), width * cropped_height, Fp_in4);
//    fclose(Fp_in4);

//    // Load and copy second cropped image
//    QString LoadImg5 = Simulation_Quad_Raw_Path + QString("\\Multi_2.raw");
//    FILE* Fp_in5;
//    fopen_s(&Fp_in5, LoadImg5.toStdString().c_str(), "rb+");
//    fread(merged_image + width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in5);
//    fclose(Fp_in5);

//    // Load and copy third cropped image
//    QString LoadImg6 = Simulation_Quad_Raw_Path + QString("\\Multi_3.raw");
//    FILE* Fp_in6;
//    fopen_s(&Fp_in6, LoadImg6.toStdString().c_str(), "rb+");
//    fread(merged_image + 2 * width * cropped_height, sizeof(unsigned short), width * cropped_height, Fp_in6);
//    fclose(Fp_in6);

//    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

//    // Clean up
//    delete[] merged_image;

    int merged_height = cropped_height * 5; // Total height after merging

    qDebug()<<"merged height"<<merged_height;

    // Allocate memory for the merged image
    unsigned short* merged_image = new unsigned short[width * merged_height];
    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

    // Copy the first cropped image into the merged buffer
    memcpy(merged_image, cropped_image, sizeof(unsigned short) * width * cropped_height);

    // Copy the second cropped image into the merged buffer
    memcpy(merged_image + width * cropped_height, cropped_image_1, sizeof(unsigned short) * width * cropped_height);

    // Copy the third cropped image into the merged buffer
    memcpy(merged_image + 2 * width * cropped_height, cropped_image_2, sizeof(unsigned short) * width * cropped_height);

    // Copy the fourth cropped image into the merged buffer
    memcpy(merged_image + 3 * width * cropped_height, cropped_image_3, sizeof(unsigned short) * width * cropped_height);

    // Copy the fifth cropped image into the merged buffer
    memcpy(merged_image + 4 * width * cropped_height, cropped_image_4, sizeof(unsigned short) * width * cropped_height);


    // Save the merged image
//    QString SaveMergedImg = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    FILE* Fp_out;
//    fopen_s(&Fp_out, SaveMergedImg.toStdString().c_str(), "wb+");
//    if (!Fp_out) {
//        delete[] merged_image;
//        // std::cerr << "Failed to open output file!" << std::endl;
//        // return -1;
//    }
//    fwrite(merged_image, sizeof(unsigned short), width * merged_height, Fp_out);
//    fclose(Fp_out);

    // Clean up


//    QString filename = Simulation_Quad_Raw_Path + QString("\\Merged.raw");
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned short* Image=new unsigned short[width * merged_height];
//    fread(Image,1,width * merged_height*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[width * merged_height];
    for(int i=0;i<width * merged_height;i++)
    {
        arr[i]=((merged_image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,width,merged_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    delete[] imagein1;
    delete[] cropped_image;

    delete[] imagein2;
    delete[] cropped_image_1;

    delete[] imagein3;
    delete[] cropped_image_2;

    delete[] imagein4;
    delete[] cropped_image_3;

    delete[] imagein5;
    delete[] cropped_image_4;
    delete[] merged_image;
    delete[] arr;
}

void MainWindow::on_Two_Dicom_crop_clicked()
{
//    typedef unsigned short img;
//    typedef itk::Image< img,2>Img;
//    typedef itk::ImageFileReader<Img>Reader;
//    Reader::Pointer reader=Reader::New();
//    Img::Pointer image;
    QString AP_Multidicompath = "D:\\CapturedImages\\20241218\\RT202402A05\\S22_P1\\FG1_FN1\\Beam1\\DailyImages\\MultiScanDicom\\Gantry 0";

    QDir m= QDir(AP_Multidicompath);
    QStringList filters;
    filters << "*.dcm" ;
    m.setNameFilters(filters);
    QStringList dcmList=m.entryList(filters);


    using PixelType = unsigned short;
    using ImageType = itk::Image< PixelType, 2 >;

    using ReaderType = itk::ImageFileReader< ImageType >;
    ReaderType::Pointer reader = ReaderType::New();

    typedef itk::GDCMImageIO ImageIOType;

    ImageIOType::Pointer imgio = ImageIOType::New();

//    std::string data;
    QString dicom_path;
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;

    Img::Pointer image;

    std::vector<std::vector<unsigned short>> allImageBuffers;

    for(int i = 0; i < dcmList.length(); ++i){

        dicom_path=AP_Multidicompath+"/"+dcmList.at(i);

        qDebug()<<"pathofDicom "<<dicom_path;

        reader->SetFileName(dicom_path.toStdString());
        reader->SetImageIO(imgio);

        try{
            reader->Update();
        }
        catch (itk::ExceptionObject &err){
            std::cout << "err" << err;
        }


        itk::MetaDataDictionary dict;
        dict = reader->GetMetaDataDictionary();

        std::string Rows1;
        itk::ExposeMetaData(dict,"0028|0010",Rows1);

        std::string Cols1;
        itk::ExposeMetaData(dict,"0028|0011",Cols1);

        QString Rows=Rows1.c_str();
        QString Cols=Cols1.c_str();
        qDebug()<<"rows"<<Rows;
        qDebug()<<"cols"<<Cols;

        int height = Rows.toInt();
        int width = Cols.toInt();

        image = reader->GetOutput();

        const unsigned short *pixelBuffer = image->GetBufferPointer();

        std::vector<unsigned short> currentImageBuffer(pixelBuffer, pixelBuffer + height * width);

//        QString filename2="D:\\CapturedImages\\20241218\\RT202402A05\\S22_P1\\FG1_FN1\\Beam1\\DailyImages\\MultiScanDicom";
//        std::string fileName3 = filename2.toStdString() + "\\proj_" + std::to_string(i) + ".raw";
//        FILE *fp;
//        fopen_s(&fp,fileName3.c_str(),"wb+");
//        fwrite(pixelBuffer,sizeof(unsigned short),height*width,fp);
//        fclose(fp);

        allImageBuffers.push_back(currentImageBuffer);

//        QString filename2="D:\\CapturedImages\\20241218\\RT202402A05\\S22_P1\\FG1_FN1\\Beam1\\DailyImages\\MultiScanDicom";
//        std::string fileName3 = filename2.toStdString() + "\\proj_" + std::to_string(i) + ".raw";
//        FILE *fp;
//        fopen_s(&fp,fileName3.c_str(),"wb+");
//        fwrite(allImageBuffers[i].data(),sizeof(unsigned short),height*width,fp);
//        fclose(fp);


    }

    qDebug()<<"image size"<<allImageBuffers.size();

    int width = 3072;
    int height = 3072;

    // Cropping calculations
    int crop_start = 74; // Starting row
    int crop_end = 2997; // Ending row
    int cropped_height = crop_end - crop_start + 1;

    qDebug()<<"first crop start";

    // Create vector for cropped images
    std::vector<unsigned short*> cropped_images;

    for (int i = 0; i < allImageBuffers.size(); ++i) {
        unsigned short* cropped_image = new unsigned short[width * cropped_height];
        memset(cropped_image, 0, sizeof(unsigned short) * width * cropped_height);

        // Copy the central region
        for (int row = 0; row < cropped_height; ++row) {
            memcpy(cropped_image + row * width, allImageBuffers[i].data() + (crop_start + row) * width, sizeof(unsigned short) * width);
        }

        cropped_images.push_back(cropped_image);
    }

    int merged_height = cropped_height * allImageBuffers.size(); // Total height after merging

    // Allocate memory for the merged image
    unsigned short* merged_image = new unsigned short[width * merged_height];
    memset(merged_image, 0, sizeof(unsigned short) * width * merged_height);

    qDebug()<<"first merge";

    // Copy each cropped image into the merged buffer
    for (int i = 0; i < cropped_images.size(); ++i) {
        memcpy(merged_image + i * cropped_height * width, cropped_images[i], sizeof(unsigned short) * width * cropped_height);
    }
    QString Pathimg="D:\\CapturedImages\\20241218\\RT202402A05\\S22_P1\\FG1_FN1\\Beam1\\DailyImages\\DICOM";
    saveMultiscanImageDicom(merged_image,Pathimg,3072,merged_height,0);

    qDebug()<<"first merge---6";
    unsigned char* arr=new unsigned char[width * merged_height];
    for(int i=0;i<width * merged_height;i++)
    {
        arr[i]=((merged_image[i]*255)/65535);
    }

    myImage = QImage(arr,width,merged_height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsViewAP->setScene(scene);
    //item->setPos(1536-200,1536-200);
    qDebug()<<"first merge---8";

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsViewAP->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

    for (auto& cropped_image : cropped_images) {
        delete[] cropped_image;
    }
    delete[] merged_image;
    delete[] arr;
    allImageBuffers.clear();

}
