#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
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
#include <QAxObject>

#include <itkResampleImageFilter.h>
#include <itkIdentityTransform.h>
#include <itkNearestNeighborInterpolateImageFunction.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkNRRDImageIO.h>

#include <QSqlQueryModel>
#include <QtSql>

//#include <QCryptographicHash>
//#include <openssl/aes.h>
//#include <openssl/evp.h>

#include <QCryptographicHash>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>

HHOOK hKeyboardHook;
HHOOK hMouseHook;

// Keyboard Hook Procedure
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        return 1; // Block input
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// Mouse Hook Procedure
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        return 1; // Block input
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    char uid[100];

//    write();
//    read();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read()
{
    DcmFileFormat fileformat;

    QString filename = ("D:/P1/RP_60d188b3ee70d5e9.dcm");
    fileformat.loadFile(filename.toStdString().c_str());

    DcmDataset *dataset = fileformat.getDataset();

    qDebug()<<"image loaded for Read";

    dataset->putAndInsertString(DCM_PatientName,"majsbd");
    dataset->putAndInsertString(DCM_PatientID,"569");
    dataset->putAndInsertString(DCM_PatientSex,"M");
    dataset->putAndInsertString(DCM_PatientAge,"50");

//    for(int i=0;i<1;i++)
//    {
//        DcmItem *item=NULL;
//        if(dataset->findOrCreateSequenceItem(DCM_DoseReferenceSequence,item,i).good())
//        {
//            item->putAndInsertString(DCM_DoseReferenceNumber,"1");
//            item->putAndInsertString(DCM_DoseReferenceUID,"1.2345.22");
//            item->putAndInsertString(DCM_DoseReferenceType,"Cancer Tissue");
//            item->putAndInsertString(DCM_DoseReferenceDescription,"goog");
//            item->putAndInsertString(DCM_DeliveryMaximumDose,"20 KV");
//            item->putAndInsertString(DCM_TargetPrescriptionDose,"10 KV");
//            item->putAndInsertString(DCM_TargetMaximumDose,"40 KV");
//        }
//    }

//    for(int k=0;k<1;k++)
//    {
//        DcmItem *itemF,*itemRB=NULL;
//        if(dataset->findOrCreateSequenceItem(DCM_FractionGroupSequence,itemF,k).good())
//        {
//            strlist=QString::number(k+1);
//            itemF->putAndInsertString(DCM_FractionGroupNumber,strlist.toStdString().c_str());
//            itemF->putAndInsertString(DCM_NumberOfFractionsPlanned,strlist.toStdString().c_str());
//            itemF->putAndInsertString(DCM_NumberOfBeams,strlist.toStdString().c_str());

//            for(int l=0;l<13;l++)
//            {
//                if(itemF->findOrCreateSequenceItem(DCM_ReferencedBeamSequence,itemRB,l).good())
//                {
//                    strlist=QString::number(l+1);
//                    itemRB->putAndInsertString(DCM_ReferencedBeamNumber,strlist.toStdString().c_str());
//                    strlist=tags[1][l][10];
//                    itemRB->putAndInsertString(DCM_BeamDose,strlist.toStdString().c_str());
//                    strlist=tags[1][l][11];
//                    itemRB->putAndInsertString(DCM_BeamMeterset,strlist.toStdString().c_str());
//                }
//            }
//        }
//    }

        QString filename1("D:/P1/RP_60d188b3ee70d5e9.dcm");
        fileformat.saveFile(filename1.toStdString().c_str(),EXS_LittleEndianExplicit);
        //    fileformat.saveFile(filename.toStdString().c_str(),EXS_LittleEndianExplicit);
}

void MainWindow::stitchlateral()
{
    int singleWidth = 2622;
    int height = 3072;
    int totalWidth = singleWidth * 2;

    // Allocate buffers for left, right, and stitched images
    unsigned short* leftImage = new unsigned short[singleWidth * height];
    unsigned short* rightImage = new unsigned short[singleWidth * height];
    unsigned short* stitchedImage = new unsigned short[totalWidth * height];

    // Load left image
    QString leftPath = "D:\\RAD\\Imagin Quad working\\Right_crop.raw";
    FILE* fLeft = fopen(leftPath.toStdString().c_str(), "rb");
    if (!fLeft) {
        qDebug() << "Could not open left image.";
        return;
    }
    fread(leftImage, sizeof(unsigned short), singleWidth * height, fLeft);
    fclose(fLeft);

    // Load right image
    QString rightPath = "D:\\RAD\\Imagin Quad working\\left_crop.raw";;
    FILE* fRight = fopen(rightPath.toStdString().c_str(), "rb");
    if (!fRight) {
        qDebug() << "Could not open right image.";
        delete[] leftImage;
        return;
    }
    fread(rightImage, sizeof(unsigned short), singleWidth * height, fRight);
    fclose(fRight);

    // Stitch: Copy left and right images side-by-side
    for (int y = 0; y < height; ++y) {
        // Copy left part
        memcpy(&stitchedImage[y * totalWidth],
               &leftImage[y * singleWidth],
               singleWidth * sizeof(unsigned short));

        // Copy right part
        memcpy(&stitchedImage[y * totalWidth + singleWidth],
               &rightImage[y * singleWidth],
               singleWidth * sizeof(unsigned short));
    }

    // Save stitched image
    qDebug()<<"Total width"<<totalWidth<<height;
    QString stitchedPath = "D:\\RAD\\Imagin Quad working\\Stitched_Horizontal.raw";
    FILE* fOut = fopen(stitchedPath.toStdString().c_str(), "wb+");
    if (fOut) {
        fwrite(stitchedImage, sizeof(unsigned short), totalWidth * height, fOut);
        fclose(fOut);
        qDebug() << "Stitched image saved as" << stitchedPath;
    } else {
        qDebug() << "Failed to write stitched image.";
    }

    // Clean up
    delete[] leftImage;
    delete[] rightImage;
//    delete[] stitchedImage;

    int radSize=3072;
    // Assuming you have a vector to store the downsampled image
    std::vector<unsigned short> downsampledImage(radSize * radSize);

    // Call the function to downsample the image
    downsampleImageHorizontal(stitchedImage, downsampledImage,totalWidth,height,radSize,radSize);


}

void MainWindow::stitchlogitudinal()
{
    int width = 3072;
    int singleHeight = 2622;
    int totalHeight = singleHeight * 2;

    // Allocate memory
    unsigned short* topImage = new unsigned short[width * singleHeight];
    unsigned short* bottomImage = new unsigned short[width * singleHeight];
    unsigned short* stitchedImage = new unsigned short[width * totalHeight];

    // Load top image
    QString topPath = "D:\\RAD\\Imagin Quad working\\down_crop.raw";
    FILE* fTop = fopen(topPath.toStdString().c_str(), "rb");
    if (!fTop) {
        qDebug() << "Could not open top image.";
        return;
    }
    fread(topImage, sizeof(unsigned short), width * singleHeight, fTop);
    fclose(fTop);

    // Load bottom image
    QString bottomPath = "D:\\RAD\\Imagin Quad working\\up_crop.raw";
    FILE* fBottom = fopen(bottomPath.toStdString().c_str(), "rb");
    if (!fBottom) {
        qDebug() << "Could not open bottom image.";
        delete[] topImage;
        return;
    }
    fread(bottomImage, sizeof(unsigned short), width * singleHeight, fBottom);
    fclose(fBottom);

    // Stitch vertically
    for (int y = 0; y < singleHeight; ++y) {
        // Top part
        memcpy(&stitchedImage[y * width],
               &topImage[y * width],
               width * sizeof(unsigned short));

        // Bottom part
        memcpy(&stitchedImage[(y + singleHeight) * width],
               &bottomImage[y * width],
               width * sizeof(unsigned short));
    }

    // Save stitched image
    QString stitchedPath = "D:\\RAD\\Imagin Quad working\\Stitched_Vertical.raw";
    FILE* fOut = fopen(stitchedPath.toStdString().c_str(), "wb+");
    if (fOut) {
        fwrite(stitchedImage, sizeof(unsigned short), width * totalHeight, fOut);
        fclose(fOut);
        qDebug() << "Stitched image saved as" << stitchedPath;
    } else {
        qDebug() << "Failed to write stitched image.";
    }

    // Cleanup
    delete[] topImage;
    delete[] bottomImage;
//    delete[] stitchedImage;
    int radSize=3072;
    // Assuming you have a vector to store the downsampled image
    std::vector<unsigned short> downsampledImage(radSize * radSize);

    // Call the function to downsample the image
    downsampleImageVertical(stitchedImage, downsampledImage,width,totalHeight,radSize,radSize);

}

void MainWindow::stitchlogitudinalfive()
{
    int width = 3072;
    int singleHeight = 3072;
    int totalHeight = singleHeight * 3;

    // Allocate memory
    unsigned short* topImage = new unsigned short[width * singleHeight];
    unsigned short* bottomImage = new unsigned short[width * singleHeight];
    unsigned short* bottomImage1 = new unsigned short[width * singleHeight];
//    unsigned short* bottomImage2 = new unsigned short[width * singleHeight];
//    unsigned short* bottomImage3 = new unsigned short[width * singleHeight];
    unsigned short* stitchedImage = new unsigned short[width * totalHeight];

    // Load top image
    QString topPath = "D:\\RAD\\proj_1.raw";
    FILE* fTop = fopen(topPath.toStdString().c_str(), "rb");
    if (!fTop) {
        qDebug() << "Could not open top image.";
        return;
    }
    fread(topImage, sizeof(unsigned short), width * singleHeight, fTop);
    fclose(fTop);

    // Load bottom image
    QString bottomPath = "D:\\RAD\\proj_1.raw";
    FILE* fBottom = fopen(bottomPath.toStdString().c_str(), "rb");
    if (!fBottom) {
        qDebug() << "Could not open bottom image.";
        delete[] topImage;
        return;
    }
    fread(bottomImage, sizeof(unsigned short), width * singleHeight, fBottom);
    fclose(fBottom);

    //============================================================================

    QString bottomPath1 = "D:\\RAD\\proj_1.raw";
    FILE* fBottom1 = fopen(bottomPath1.toStdString().c_str(), "rb");
    if (!fBottom1) {
        qDebug() << "Could not open bottom image.";
        delete[] topImage;
        return;
    }
    fread(bottomImage1, sizeof(unsigned short), width * singleHeight, fBottom1);
    fclose(fBottom1);

    // Stitch vertically
    for (int y = 0; y < singleHeight; ++y) {
        // Top part
        memcpy(&stitchedImage[y * width],
               &topImage[y * width],
               width * sizeof(unsigned short));

        // Bottom part
        memcpy(&stitchedImage[(y + singleHeight) * width],
               &bottomImage[y * width],
               width * sizeof(unsigned short));

        // Bottom image (third part)
        memcpy(&stitchedImage[(y + 2 * singleHeight) * width],
               &bottomImage1[y * width],
               width * sizeof(unsigned short));
    }

//=================================================================================

    // Save stitched image
    QString stitchedPath = "D:\\RAD\\proj_1.raw";
    FILE* fOut = fopen(stitchedPath.toStdString().c_str(), "wb+");
    if (fOut) {
        fwrite(stitchedImage, sizeof(unsigned short), width * totalHeight, fOut);
        fclose(fOut);
        qDebug() << "Stitched image saved as" << stitchedPath;
    } else {
        qDebug() << "Failed to write stitched image.";
    }

    // Cleanup
    delete[] topImage;
    delete[] bottomImage;
    delete[] bottomImage1;
//    delete[] stitchedImage;
    int radSize=3072;
    // Assuming you have a vector to store the downsampled image
    std::vector<unsigned short> downsampledImage(radSize * radSize);

    // Call the function to downsample the image
    downsampleImageVertical(stitchedImage, downsampledImage,width,totalHeight,radSize,radSize);

}

void MainWindow::downsampleImageVertical(unsigned short* originalImage, std::vector<unsigned short>& downsampledImage,int Originalwidth,int Originalheight,int downsampledWidth,int downsampledHeight)
{
    float scaleY = static_cast<float>(Originalheight) / downsampledHeight;
    int scaleX = 1; // No downsampling in X, width remains the same

    for (int j = 0; j < downsampledHeight; ++j) {
        int startY = static_cast<int>(j * scaleY);
        int endY = static_cast<int>((j + 1) * scaleY);
        if (endY > Originalheight) endY = Originalheight;

        for (int i = 0; i < downsampledWidth; ++i) {
            // Since no downsampling in X
            int startX = i;
            int endX = i + 1;

            unsigned int sum = 0;
            int count = 0;

            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    sum += originalImage[y * Originalwidth + x];
                    ++count;
                }
            }

            unsigned short avg = count > 0 ? static_cast<unsigned short>(sum / count) : 0;
            downsampledImage[j * downsampledWidth + i] = avg;
        }
    }

    FILE* Fp831_cropped;
    QString cropped1 = "D:\\RAD\\Downsampled_Vert1.raw";
    fopen_s(&Fp831_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(downsampledImage.data(), sizeof(unsigned short), downsampledWidth * downsampledHeight, Fp831_cropped);
    fclose(Fp831_cropped);

}

void MainWindow::downsampleImageHorizontal(unsigned short *originalImage, std::vector<unsigned short> &downsampledImage, int OriginalWidth, int OriginalHeight, int downsampledWidth, int downsampledHeight)
{
    // Calculate scale to fit within 3072x3072 while maintaining aspect ratio

    int targetWidth=3072;
    int targetHeight=3072;

    float scaleX = static_cast<float>(OriginalWidth) / targetWidth;
    float scaleY = static_cast<float>(OriginalHeight) / targetHeight;

    float scale = std::max(scaleX, scaleY);  // Keep aspect ratio

    int resizedWidth = static_cast<int>(OriginalWidth / scale);
    int resizedHeight = static_cast<int>(OriginalHeight / scale);

    std::vector<unsigned short> downsampled(resizedWidth * resizedHeight);

    for (int j = 0; j < resizedHeight; ++j) {
        int startY = static_cast<int>(j * scale);
        int endY = static_cast<int>((j + 1) * scale);
        if (endY > OriginalHeight) endY = OriginalHeight;

        for (int i = 0; i < resizedWidth; ++i) {
            int startX = static_cast<int>(i * scale);
            int endX = static_cast<int>((i + 1) * scale);
            if (endX > OriginalWidth) endX = OriginalWidth;

            unsigned int sum = 0;
            int count = 0;

            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    sum += originalImage[y * OriginalWidth + x];
                    ++count;
                }
            }

            unsigned short avg = count > 0 ? static_cast<unsigned short>(sum / count) : 0;
            downsampled[j * resizedWidth + i] = avg;
        }
    }

    // ⚠️ Now resize to exactly 3072x3072 with black padding
    downsampledImage.resize(targetWidth * targetHeight, 0);  // black filled

    int offsetX = (targetWidth - resizedWidth) / 2;
    int offsetY = (targetHeight - resizedHeight) / 2;

    for (int y = 0; y < resizedHeight; ++y) {
        for (int x = 0; x < resizedWidth; ++x) {
            downsampledImage[(y + offsetY) * targetWidth + (x + offsetX)] = downsampled[y * resizedWidth + x];
        }
    }

    // Save output to raw file
    FILE* Fp831_cropped;
    QString outputFile = "D:\\RAD\\Downsampled_hori.raw";
    fopen_s(&Fp831_cropped, outputFile.toStdString().c_str(), "wb+");
    fwrite(downsampledImage.data(), sizeof(unsigned short), downsampledWidth * downsampledHeight, Fp831_cropped);
    fclose(Fp831_cropped);

    qDebug() << "Downsampled to: " << downsampledWidth << " x " << downsampledHeight;
}

void MainWindow::write()
{
    DcmFileFormat fileformat;

    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/p1/*.dcm",QDir::currentPath());

    typedef unsigned short img;
    typedef unsigned short out_img;

    typedef itk::Image< img,2>Img;
//    Img::Pointer image;
    typedef itk::ImageFileReader<Img>ReaderType;
    ReaderType::Pointer reader = ReaderType::New();
    typedef itk::GDCMImageIO  ImageType;
    reader->SetFileName(filename.toStdString().c_str());
    ImageType::Pointer gdcmImage = ImageType::New();

    reader->SetImageIO( gdcmImage);
    reader->Update();
    const Img * image = reader->GetOutput();

//    Img::SpacingType spacing;
//    spacing[0]=0.33;
//    spacing[1]=0.33;
//    spacing[2]=1.20;
//    image->SetSpacing(spacing);

//    const ImageType::SpacingType& sp = image->GetSpacing();

    typedef itk::Image<out_img,2>outImg1;

    typedef itk::ResampleImageFilter<Img,outImg1>FilterType;
    outImg1::Pointer out=outImg1::New();
    FilterType::Pointer filter=FilterType::New();

    typedef itk::AffineTransform<double,2>TransformType;
    TransformType::Pointer transform =TransformType::New();
    filter->SetTransform(transform);

    typedef itk::NearestNeighborInterpolateImageFunction<Img,double>InterpolaratorType;
    InterpolaratorType::Pointer interpolar =InterpolaratorType::New();
    filter->SetInterpolator(interpolar);

    filter->SetDefaultPixelValue(0.3);

//    const double spacing[2]={1.0,1.0};
//    float pixelspacing = 0.092;
//    filter->SetOutputSpacing(spacing);

//    const double origin[2]={0.0,0.0};
//    filter->SetOutputOrigin(origin);


    const Img::SpacingType & spacing=image->GetSpacing();
    const Img::PointType & origin=image->GetOrigin();
    Img::SizeType size=image->GetLargestPossibleRegion().GetSize();

    filter->SetOutputOrigin(origin);
    filter->SetOutputSpacing(spacing);
    filter->SetOutputDirection(image->GetDirection());
    filter->SetSize(size);

//    Img::DirectionType direction;
//    direction.SetIdentity();
//    filter->SetOutputDirection(direction);

//    Img::SizeType size;

//    size[0]=300;
//    size[1]=300;

//    filter->SetSize(size);

//    TransformType::OutputVectorType translation1;
//    const double imageCenterX=origin[0]+spacing[0]*size[0]/2.0;
//    const double imageCenterY=origin[1]+spacing[1]*size[1]/2.0;


//    translation1[0]=-imageCenterX;
//    translation1[1]=-imageCenterY;
//    transform->Translate(translation1);

//    TransformType::OutputVectorType translation2;
//    translation2[0]=imageCenterX;
//    translation2[1]=imageCenterY;
//    transform->Translate(translation2,false);
//    filter->SetTransform(transform);


    filter->SetInput(reader->GetOutput());
    filter->Update();

    out=filter->GetOutput();

    itk::MetaDataDictionary dict2;
    dict2 = reader->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict2,"0028|0010",Rows1);
    Rows =  std::stoi(Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict2,"0028|0011",Cols1);
    Cols = std::stoi(Cols1);

    std::string pixs;
    itk::ExposeMetaData(dict2,"0028|0030",pixs);
    fileformat.loadFile(filename.toStdString().c_str());

    QString RowS=Rows1.c_str();
    QString ColS=Cols1.c_str();
    qDebug()<<"R"<<RowS;
    qDebug()<<"c"<<ColS;

    Rows=RowS.toInt();
    Cols=ColS.toInt();

    qDebug()<<"Row"<<Rows;
    qDebug()<<"col"<<Cols;

//    std::string PixelPitch; //Added By KM

//    try
//    {
//        itk::ExposeMetaData(dict2,"3002|0011",PixelPitch); // Iso Centric Pixel Pitch
//        throw PixelPitch;
//    }
//    catch(std::string PixelPitch)
//    {
//        // qDebug() << "Exception Caught";
//    }

//    PixelPitch1.rx() = PixelX;
//    PixelPitch1.ry() = PixelY;

    Size.clear();
    Size<<QPoint(RowS.toDouble(),ColS.toDouble());

//    DcmDataset *dataset;
//    DcmFileFormat fileformate;
//    DcmElement *dcmIso;

//    fileformate.loadFile(filename.toStdString().c_str());
//    dataset=fileformate.getDataset();

    qDebug()<<"image loaded for write";

//    if(dataset->findAndGetElement(DCM_IsocenterPosition,dcmIso).good())
//    {
//        itk::MetaDataDictionary dict2;
//        dict2 = reader->GetMetaDataDictionary();
//        std::string isocen;
//        itk::ExposeMetaData(dict2,"300a|012c",isocen);

 //    dataset->putAndInsertString(DCM_PatientName,"Test123");
 //    dataset->putAndInsertString(DCM_IsocenterPosition,300,300,-18.0);
 //    dataset->putAndInsertString(DCM_PatientID,"1234");
 //    dataset->putAndInsertString(DCM_PatientSex,"M");
 //    dataset->putAndInsertString(DCM_PatientAge,"24");

//        QString Cen = isocen.c_str();QString c1;
//        if(Cen==" "||Cen=="")
//        {
//            PointCen.setX(Size[0].rx()/2+1);
//            PointCen.setY(Size[0].ry()/2+1);
//            Cancer_center.append(PointCen);
//        }
//        else
//        {
//            QStringList Cen1 = Cen.split("\\");
//            c1 =Cen1.at(0);
//            PointCen.setX(c1.toFloat()/PixelPitch1.rx());
//            c1 =Cen1.at(1);
//            PointCen.setY(c1.toFloat()/PixelPitch1.ry());
//            Cancer_center.append(PointCen);
//        }
//    }
//    else
//    {
//        PointCen.setX(Size[0].rx()/2+1);
//        PointCen.setY(Size[0].ry()/2+1);
//        Cancer_center.append(PointCen);
//    }

//    Contentlist2.append(TagList1);
//    IsoCentres.removeAt(i);

//    IsoCentres.insert(i,QPointF(PointCen.x()*PixelPitch1.rx(),PointCen.y()*PixelPitch1.ry()));

//    height = Rows;
//    width = Cols;

    slice = new unsigned char[Rows*Cols];

    image = reader->GetOutput();

    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[Rows*Cols];

    for(int i=0;i<Rows*Cols;++i)
    {
//        if(pixelBuffer[i]!=0)
//        {
//        qDebug()<<pixelBuffer[i];
//        }

//        dispImg[i] = pixelBuffer[i]*255.0/65535.0; //convert 16 bit image to 8 bit image for display in qt
//        if(dispImg[i]!=0)
//        {
//        qDebug()<<dispImg[i];
//        }
        dispImg[i] = (pixelBuffer[i]*255.0/65535.0)*100.0;
    }
    qDebug()<<"disp2"<<pixelBuffer[1200];
    qDebug()<<"disp"<<dispImg[1200];

//    if(dispImg[i]>0)
//    {
    //    if(MirrorAddToggle!=1)
    //    {
    ////            //load buffer to qImage
    q_image = QImage(dispImg,Rows,Cols,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    view = new QGraphicsView(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->setScene(scene);
//    }
//    else
//    {
//        qDebug()<<"Image is not displayed";
//    }

//    QString filename1("D:/P1/RP_60d188b3ee70d5e9.dcm");
//    fileformat.saveFile(filename1.toStdString().c_str(),EXS_LittleEndianExplicit);

}

void MainWindow::on_Dicomtoraw_clicked()
{

    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());

    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    reader->SetImageIO(gdcmImage);
    try
    {
        reader->Update();

    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
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

//    // Resample
//    double spacing[ 2 ];
//    spacing[0] = 0.3945;    // along X direction
//    spacing[1] = 0.3945;

//    typedef itk::NearestNeighborInterpolateImageFunction<InputImageType, double > InterpolatorType;
//    InterpolatorType::Pointer interpolator = InterpolatorType::New();

//    double newSpacingX = 0.3945; // New pixel spacing in the X dimension (in millimeters)
//    double newSpacingY = 0.3945; // New pixel spacing in the Y dimension (in millimeters)

//    // Calculate the scaling factors for resizing the image
//    double scalingFactorX = inputImage->GetSpacing()[0] / newSpacingX;
//    double scalingFactorY = inputImage->GetSpacing()[1] / newSpacingY;

//    typedef itk::ResampleImageFilter<InputImageType, InputImageType> ResampleFilterType;
//    ResampleFilterType::Pointer resampler = ResampleFilterType::New();

//    // Set the input (original) image
//    resampler->SetInput(inputImage);

//    // Calculate the new size based on the scaling factors
//    InputImageType::SizeType newSize;
//    newSize[0] = static_cast<unsigned int>(inputImage->GetLargestPossibleRegion().GetSize()[0] * scalingFactorX*1.74356);
//    newSize[1] = static_cast<unsigned int>(inputImage->GetLargestPossibleRegion().GetSize()[1] * scalingFactorY*1.74356);

//    // Set the size and spacing of the output image
//    resampler->SetSize(newSize);
//    resampler->SetOutputSpacing(spacing);

//    // Interpolation options (e.g., Linear, NearestNeighbor, etc.)
//    resampler->SetInterpolator(interpolator);

////    using ResampleFilterType = itk::ResampleImageFilter<InputImageType, OutputImageType>;
////    ResampleFilterType::Pointer resampler = ResampleFilterType::New();

////    resampler->SetInput(inputImage);
////    resampler->SetSize({1024, 1024});
//    resampler->Update();
//    outputImage = resampler->GetOutput();

//    const double newSpacingX = 0.3945;  //changing pixelspacing vivek
//    const double newSpacingY = 0.3945;  //changing pixelspacing vivek

//    // Set the new pixel spacing in the image's metadata
//    Img::SpacingType newSpacing;  //changing pixelspacing vivek
//    newSpacing[0] = newSpacingX;        //changing pixelspacing vivek
//    newSpacing[1] = newSpacingY;        //changing pixelspacing vivek
//    image->SetSpacing(newSpacing);      //changing pixelspacing vivek

//    ImageType::Pointer inputImage = reader->GetOutput();

    // Define the resampling filter
//    typedef itk::ResampleImageFilter<ImageType, ImageType> ResampleFilterType;
//    ResampleFilterType::Pointer resampler = ResampleFilterType::New();

//    // Set the input image for resampling
//    resampler->SetInput(image);

//    // Define the output size (1024x1024)
//    ImageType::SizeType outputSize;
//    outputSize[0] = 1024;
//    outputSize[1] = 1024;
//    resampler->SetSize(outputSize);


    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];

//    qDebug()<<pixelBuffer[0];
//    for(int i=0;i<width*height;++i)
//    {
//        dispImg[i] = pixelBuffer[i]*255/65535.0;
//    }
//    qDebug()<<dispImg[0];



    QString filename2=ui->lineEdit->text();
    int number=ui->lineEdit_2->text().toInt();
    std::string fileName3 = filename2.toStdString() + "\\proj_" + std::to_string(number) + ".raw";
    FILE *fp;
    fopen_s(&fp,fileName3.c_str(),"wb+");
    fwrite(pixelBuffer,sizeof(unsigned short),width*height,fp);
    fclose(fp);
    qDebug()<<"write finished";
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"entered excel";

    ImageTypes="['DERIVED','SECONDARY','OTHER']";

    InstanceCreationDate=QString(QDate::currentDate().toString("yyyyMMdd"));
    InstanceCreationTime=QString(QTime::currentTime().toString("hhmmss.zzzzzz"));
    SOPClassUIDs="CT Image Storage";
    StudyDate=QString(QDate::currentDate().toString("yyyyMMdd"));
    SeriesDate=QString(QDate::currentDate().toString("yyyyMMdd"));
    AcquisitionDate=QString(QDate::currentDate().toString("yyyyMMdd"));
    ContentDate=QString(QDate::currentDate().toString("yyyyMMdd"));
    StudyTime=QString(QTime::currentTime().toString("hhmmss.zzzzzz"));
    SeriesTime=QString(QTime::currentTime().toString("hhmmss.zzzzzz"));
    AcquisitionTime=QString(QTime::currentTime().toString("hhmmss.zzzzzz"));
    ContentTime=QString(QTime::currentTime().toString("hhmmss.zzzzzz"));
    AccessionNumber="";
    Modality="CT";
    Manufacturer="Panacea";
    InstitutionName="PanaceaMedicalTechnologies";
    ReferringPhysiciansName="";
    StationName="";
    SeriesDescription="";
    PerformingPhysiciansName="";
    OperatorsName="";
    ManufacturersModelName="";
    ScanOptions  ="";

    //SliceThickness  = ""  ;
    DataCollectionDiameter="";
    DeviceSerialNumber="S/N license key";
    SoftwareVersions="3";
    ProtocolName  ="";
    ReconstructionDiameter="";
    GantryDetectorTilt="";
    TableHeight="";
    RotationDirection="CW";
    ExposureTime='40';
    XRayTubeCurrent='60';
    ExposureInuAs="";
    FilterType="";
    GeneratorPower="";
    FocalSpots="";
    DateofLastCalibration="";
    TimeofLastCalibration="";
    ConvolutionKernel="";
    PatientPosition="";
    StudyInstanceUID="1.4255524.55666";
    SeriesInstanceUID="1.4255524.555566665666";
    //  StudyID=StudyID;
    SeriesNumber="1";
    AcquisitionNumber="933";
    InstanceNumber="12";
    ImagePositionPatients<<"-127.5"<<"127.5"<<"-122";
    ImageOrientationPatient<<"1"<<"0"<<"0"<<"0"<<"1"<<"0";
    FrameofReferenceUID="1.76.380.42.1";
    PositionReferenceIndicator="";
    SliceLocation="-122";
    SamplesperPixel="1";
    PhotometricInterpretation="MONOCHROME2";
    Rows1="512";
    Columns="512";
    //  PixelSpacing<<"0.5"<<"0.5";
    BitsAllocated="16";
    BitsStored="16";
    HighBit="15";
    PixelRepresentation="1";
    SmallestImagePixelValue="-2598";
    LargestImagePixelValue="696";
    SmallestPixelValueinSeries="-16336";
    LargestPixelValueinSeries="29056";
    QualityControlImage="NO";
    RescaleIntercept="0";
    RescaleSlope="1";
    PixelData="Array of 524288 bytes";
    WindowCenter="32768";
    WindowWidth="65535";
    SliceThickness2= 0.5;

    QAxObject *pApplication;
    QAxObject *pWorkBooks;
    QAxObject *pWorkBook;
    QAxObject *pSheets;
    QAxObject *pSheet;
    QString fileName2 = qApp->applicationDirPath()+"\\CBCTWriteTagstoExcel.xlsx";
    pApplication = new QAxObject("Excel.Application");
    if (pApplication == nullptr) {
        qWarning("pApplication\n");
        return;
    }
    pApplication->dynamicCall("SetVisible(bool)",false);// false does not display the form
    pApplication->setProperty("DisplayAlerts",false);// Do not display any warning information
    pWorkBooks = pApplication->querySubObject("Workbooks");
    QFile file(fileName2);
    if (file.exists()) {
        qDebug()<<"exist";
        pWorkBook = pWorkBooks->querySubObject("Open(const QString&)",fileName2);
    } else {
        qDebug()<<"exist1";
        pWorkBooks->dynamicCall("Add");
        pWorkBook = pApplication->querySubObject("ActiveWorkBook");
    }
    pSheets = pWorkBook->querySubObject("Sheets");
    pSheet = pSheets->querySubObject("Item(int)",1);
    qDebug()<<"exist44";
    QAxObject *pRange1 = pSheet->querySubObject("Cells(int,int)",1,1);
    pRange1->dynamicCall("Value","ImageType");
    qDebug()<<"exist22";
    QAxObject *pRange2 = pSheet->querySubObject("Cells(int,int)",2,1);
    pRange2->dynamicCall("Value","InstanceCreationDate");
    QAxObject *pRange3 = pSheet->querySubObject("Cells(int,int)",3,1);
    pRange3->dynamicCall("Value","InstanceCreationTime");
    QAxObject *pRange4 = pSheet->querySubObject("Cells(int,int)",4,1);
    pRange4->dynamicCall("Value","SOPClassUID");
    QAxObject *pRange5 = pSheet->querySubObject("Cells(int,int)",5,1);
    pRange5->dynamicCall("Value","SOPInstanceUID");
    QAxObject *pRange6 = pSheet->querySubObject("Cells(int,int)",6,1);
    pRange6->dynamicCall("Value","StudyDate");
    QAxObject *pRange7 = pSheet->querySubObject("Cells(int,int)",7,1);
    pRange7->dynamicCall("Value","SeriesDate");
    QAxObject *pRange8 = pSheet->querySubObject("Cells(int,int)",8,1);
    pRange8->dynamicCall("Value","Acquisition Date");
    QAxObject *pRange9 = pSheet->querySubObject("Cells(int,int)",9,1);
    pRange9->dynamicCall("Value","Content Date");
    QAxObject *pRange10 = pSheet->querySubObject("Cells(int,int)",10,1);
    pRange10->dynamicCall("Value","Study Time");
    QAxObject *pRange11 = pSheet->querySubObject("Cells(int,int)",11,1);
    pRange11->dynamicCall("Value","Series Time");
    QAxObject *pRange12 = pSheet->querySubObject("Cells(int,int)",12,1);
    pRange12->dynamicCall("Value","Acquisition Time");
    QAxObject *pRange13 = pSheet->querySubObject("Cells(int,int)",13,1);
    pRange13->dynamicCall("Value","Content Time");
    QAxObject *pRange14 = pSheet->querySubObject("Cells(int,int)",14,1);
    pRange14->dynamicCall("Value","Accession Number");
    QAxObject *pRange15 = pSheet->querySubObject("Cells(int,int)",15,1);
    pRange15->dynamicCall("Value","Modality");
    QAxObject *pRange16 = pSheet->querySubObject("Cells(int,int)",16,1);
    pRange16->dynamicCall("Value","Manufacturer");
    QAxObject *pRange17 = pSheet->querySubObject("Cells(int,int)",17,1);
    pRange17->dynamicCall("Value","Institution Name");
    QAxObject *pRange18 = pSheet->querySubObject("Cells(int,int)",18,1);
    pRange18->dynamicCall("Value","Referring Physician's Name");
    QAxObject *pRange19 = pSheet->querySubObject("Cells(int,int)",19,1);
    pRange19->dynamicCall("Value","Station Name");
    QAxObject *pRange20 = pSheet->querySubObject("Cells(int,int)",20,1);
    pRange20->dynamicCall("Value","Study Description");
    QAxObject *pRange21 = pSheet->querySubObject("Cells(int,int)",21,1);
    pRange21->dynamicCall("Value","Series Description");
    QAxObject *pRange22 = pSheet->querySubObject("Cells(int,int)",22,1);
    pRange22->dynamicCall("Value","Performing Physician's Name");
    QAxObject *pRange23 = pSheet->querySubObject("Cells(int,int)",23,1);
    pRange23->dynamicCall("Value","Operator's Name");
    QAxObject *pRange24 = pSheet->querySubObject("Cells(int,int)",24,1);
    pRange24->dynamicCall("Value","Manufacturer's Model Name");
    QAxObject *pRange25 = pSheet->querySubObject("Cells(int,int)",25,1);
    pRange25->dynamicCall("Value","Patient's Name");
    QAxObject *pRange26 = pSheet->querySubObject("Cells(int,int)",26,1);
    pRange26->dynamicCall("Value","Patient ID");
    QAxObject *pRange27 = pSheet->querySubObject("Cells(int,int)",27,1);
    pRange27->dynamicCall("Value","patient's Birth Date");
    QAxObject *pRange28 = pSheet->querySubObject("Cells(int,int)",28,1);
    pRange28->dynamicCall("Value","Patient's Sex");
    QAxObject *pRange29 = pSheet->querySubObject("Cells(int,int)",29,1);
    pRange29->dynamicCall("Value","Scan Options");
    QAxObject *pRange30 = pSheet->querySubObject("Cells(int,int)",30,1);
    pRange30->dynamicCall("Value","Slice Thickness");
    QAxObject *pRange31 = pSheet->querySubObject("Cells(int,int)",31,1);
    pRange31->dynamicCall("Value","KVP");
    QAxObject *pRange32 = pSheet->querySubObject("Cells(int,int)",32,1);
    pRange32->dynamicCall("Value","Data Collection Diameter");
    QAxObject *pRange33 = pSheet->querySubObject("Cells(int,int)",33,1);
    pRange33->dynamicCall("Value","Device Serial Number");
    QAxObject *pRange34 = pSheet->querySubObject("Cells(int,int)",34,1);
    pRange34->dynamicCall("Value","Software Version(s)");
    QAxObject *pRange35 = pSheet->querySubObject("Cells(int,int)",35,1);
    pRange35->dynamicCall("Value","Protocol Name");
    QAxObject *pRange36 = pSheet->querySubObject("Cells(int,int)",36,1);
    pRange36->dynamicCall("Value","Reconstruction Diameter");
    QAxObject *pRange37 = pSheet->querySubObject("Cells(int,int)",37,1);
    pRange37->dynamicCall("Value","Gantry/Detector Tilt");
    QAxObject *pRange38 = pSheet->querySubObject("Cells(int,int)",38,1);
    pRange38->dynamicCall("Value","Table Height");
    QAxObject *pRange39 = pSheet->querySubObject("Cells(int,int)",39,1);
    pRange39->dynamicCall("Value","Rotation Direction ");
    QAxObject *pRange40 = pSheet->querySubObject("Cells(int,int)",40,1);
    pRange40->dynamicCall("Value","Exposure Time");
    QAxObject *pRange41 = pSheet->querySubObject("Cells(int,int)",41,1);
    pRange41->dynamicCall("Value","X-Ray Tube Current");
    QAxObject *pRange42 = pSheet->querySubObject("Cells(int,int)",42,1);
    pRange42->dynamicCall("Value","ExposureInuAs");
    QAxObject *pRange43 = pSheet->querySubObject("Cells(int,int)",43,1);
    pRange43->dynamicCall("Value","Filter Type");
    QAxObject *pRange44 = pSheet->querySubObject("Cells(int,int)",44,1);
    pRange44->dynamicCall("Value","Generator Power");
    QAxObject *pRange45 = pSheet->querySubObject("Cells(int,int)",45,1);
    pRange45->dynamicCall("Value","Focal Spot(s)");
    QAxObject *pRange46 = pSheet->querySubObject("Cells(int,int)",46,1);
    pRange46->dynamicCall("Value","Date of Last Calibration");
    QAxObject *pRange47 = pSheet->querySubObject("Cells(int,int)",47,1);
    pRange47->dynamicCall("Value","Time of Last Calibration");
    QAxObject *pRange48 = pSheet->querySubObject("Cells(int,int)",48,1);
    pRange48->dynamicCall("Value","Convolution Kernel");
    QAxObject *pRange49 = pSheet->querySubObject("Cells(int,int)",49,1);
    pRange49->dynamicCall("Value","Patient Position");
    QAxObject *pRange50 = pSheet->querySubObject("Cells(int,int)",50,1);
    pRange50->dynamicCall("Value","Study Instance UID");
    QAxObject *pRange51 = pSheet->querySubObject("Cells(int,int)",51,1);
    pRange51->dynamicCall("Value","Series Instance UID");
    QAxObject *pRange52 = pSheet->querySubObject("Cells(int,int)",52,1);
    pRange52->dynamicCall("Value","Study ID");
    QAxObject *pRange53 = pSheet->querySubObject("Cells(int,int)",53,1);
    pRange53->dynamicCall("Value","Series Number");
    QAxObject *pRange54 = pSheet->querySubObject("Cells(int,int)",54,1);
    pRange54->dynamicCall("Value","Acquisition Number");
    QAxObject *pRange55 = pSheet->querySubObject("Cells(int,int)",55,1);
    pRange55->dynamicCall("Value","Instance Number");
    QAxObject *pRange56 = pSheet->querySubObject("Cells(int,int)",56,1);
    pRange56->dynamicCall("Value","Image Position(Patient)");
    QAxObject *pRange57 = pSheet->querySubObject("Cells(int,int)",57,1);
    pRange57->dynamicCall("Value","Image Position(Patient)");
    QAxObject *pRange58 = pSheet->querySubObject("Cells(int,int)",58,1);
    pRange58->dynamicCall("Value","Image Position(Patient)");
    QAxObject *pRange59 = pSheet->querySubObject("Cells(int,int)",59,1);
    pRange59->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange60 = pSheet->querySubObject("Cells(int,int)",60,1);
    pRange60->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange61 = pSheet->querySubObject("Cells(int,int)",61,1);
    pRange61->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange62 = pSheet->querySubObject("Cells(int,int)",62,1);
    pRange62->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange63 = pSheet->querySubObject("Cells(int,int)",63,1);
    pRange63->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange64 = pSheet->querySubObject("Cells(int,int)",64,1);
    pRange64->dynamicCall("Value","Image Orientation(Patient)");
    QAxObject *pRange65 = pSheet->querySubObject("Cells(int,int)",65,1);
    pRange65->dynamicCall("Value","Frame of Reference UID");
    QAxObject *pRange66 = pSheet->querySubObject("Cells(int,int)",66,1);
    pRange66->dynamicCall("Value","Position Reference Indicator");
    QAxObject *pRange67 = pSheet->querySubObject("Cells(int,int)",67,1);
    pRange67->dynamicCall("Value","Slice Location");
    QAxObject *pRange68 = pSheet->querySubObject("Cells(int,int)",68,1);
    pRange68->dynamicCall("Value","Samples per Pixel");
    QAxObject *pRange69 = pSheet->querySubObject("Cells(int,int)",69,1);
    pRange69->dynamicCall("Value","Photometric Interpretation");
    QAxObject *pRange70 = pSheet->querySubObject("Cells(int,int)",70,1);
    pRange70->dynamicCall("Value","Rows");
    QAxObject *pRange71 = pSheet->querySubObject("Cells(int,int)",71,1);
    pRange71->dynamicCall("Value","Columns");
    QAxObject *pRange72 = pSheet->querySubObject("Cells(int,int)",72,1);
    pRange72->dynamicCall("Value","Pixel Spacing");
    QAxObject *pRange73 = pSheet->querySubObject("Cells(int,int)",73,1);
    pRange73->dynamicCall("Value","Pixel Spacing");
    QAxObject *pRange74 = pSheet->querySubObject("Cells(int,int)",74,1);
    pRange74->dynamicCall("Value","Bits Allocated");
    QAxObject *pRange75 = pSheet->querySubObject("Cells(int,int)",75,1);
    pRange75->dynamicCall("Value","Bits Stored");
    QAxObject *pRange76 = pSheet->querySubObject("Cells(int,int)",76,1);
    pRange76->dynamicCall("Value","High Bit");
    QAxObject *pRange77 = pSheet->querySubObject("Cells(int,int)",77,1);
    pRange77->dynamicCall("Value","Pixel Representation");
    QAxObject *pRange78 = pSheet->querySubObject("Cells(int,int)",78,1);
    pRange78->dynamicCall("Value","Smallest Image Pixel Value");
    QAxObject *pRange79 = pSheet->querySubObject("Cells(int,int)",79,1);
    pRange79->dynamicCall("Value","Largest Image Pixel Value");
    QAxObject *pRange80 = pSheet->querySubObject("Cells(int,int)",80,1);
    pRange80->dynamicCall("Value","Smallest Pixel Value in Series");
    QAxObject *pRange81 = pSheet->querySubObject("Cells(int,int)",81,1);
    pRange81->dynamicCall("Value","Largest Pixel Value in Series");
    QAxObject *pRange82 = pSheet->querySubObject("Cells(int,int)",82,1);
    pRange82->dynamicCall("Value","Quality Control Image");
    QAxObject *pRange83 = pSheet->querySubObject("Cells(int,int)",83,1);
    pRange83->dynamicCall("Value","Rescale Intercept");
    QAxObject *pRange84 = pSheet->querySubObject("Cells(int,int)",84,1);
    pRange84->dynamicCall("Value","Rescale Slope");
    QAxObject *pRange85 = pSheet->querySubObject("Cells(int,int)",85,1);
    pRange85->dynamicCall("Value","Pixel Data");
    QAxObject *pRange86 = pSheet->querySubObject("Cells(int,int)",86,1);
    pRange86->dynamicCall("Value","Window Center");
    QAxObject *pRange87 = pSheet->querySubObject("Cells(int,int)",87,1);
    pRange87->dynamicCall("Value","Window Width");

    QAxObject *sRange1 = pSheet->querySubObject("Cells(int,int)",1,2);
    sRange1->dynamicCall("Value",ImageTypes);

    QAxObject *sRange2 = pSheet->querySubObject("Cells(int,int)",2,2);
    sRange2->dynamicCall("Value",InstanceCreationDate);

    QAxObject *sRange3 = pSheet->querySubObject("Cells(int,int)",3,2);
    sRange3->dynamicCall("Value",InstanceCreationTime);
    QAxObject *sRange4 = pSheet->querySubObject("Cells(int,int)",4,2);
    sRange4->dynamicCall("Value",SOPClassUIDs);
    QAxObject *sRange5 = pSheet->querySubObject("Cells(int,int)",5,2);
    sRange5->dynamicCall("Value","12.522523.552665656");

    QAxObject *sRange6 = pSheet->querySubObject("Cells(int,int)",6,2);
    sRange6->dynamicCall("Value",StudyDate);
    QAxObject *sRange7 = pSheet->querySubObject("Cells(int,int)",7,2);
    sRange7->dynamicCall("Value",SeriesDate);
    QAxObject *sRange8 = pSheet->querySubObject("Cells(int,int)",8,2);
    sRange8->dynamicCall("Value",AcquisitionDate);
    QAxObject *sRange9 = pSheet->querySubObject("Cells(int,int)",9,2);
    sRange9->dynamicCall("Value",ContentDate);
    QAxObject *sRange10 = pSheet->querySubObject("Cells(int,int)",10,2);
    sRange10->dynamicCall("Value",StudyTime);

    QAxObject *sRange11 = pSheet->querySubObject("Cells(int,int)",11,2);
    sRange11->dynamicCall("Value",SeriesTime);
    QAxObject *sRange12 = pSheet->querySubObject("Cells(int,int)",12,2);
    sRange12->dynamicCall("Value",AcquisitionTime);
    QAxObject *sRange13 = pSheet->querySubObject("Cells(int,int)",13,2);
    sRange13->dynamicCall("Value",ContentTime);
    QAxObject *sRange14 = pSheet->querySubObject("Cells(int,int)",14,2);
    sRange14->dynamicCall("Value",AccessionNumber);
    QAxObject *sRange15 = pSheet->querySubObject("Cells(int,int)",15,2);
    sRange15->dynamicCall("Value",Modality);

    QAxObject *sRange16 = pSheet->querySubObject("Cells(int,int)",16,2);
    sRange16->dynamicCall("Value",Manufacturer);
    QAxObject *sRange17 = pSheet->querySubObject("Cells(int,int)",17,2);
    sRange17->dynamicCall("Value",InstitutionName);
    QAxObject *sRange18 = pSheet->querySubObject("Cells(int,int)",18,2);
    sRange18->dynamicCall("Value",ReferringPhysiciansName);
    QAxObject *sRange19 = pSheet->querySubObject("Cells(int,int)",19,2);
    sRange19->dynamicCall("Value",StationName);
    QAxObject *sRange20 = pSheet->querySubObject("Cells(int,int)",20,2);
    sRange20->dynamicCall("Value","StudyDescription");

    QAxObject *sRange21 = pSheet->querySubObject("Cells(int,int)",21,2);
    sRange21->dynamicCall("Value","SeriesDescription");
    QAxObject *sRange22 = pSheet->querySubObject("Cells(int,int)",22,2);
    sRange22->dynamicCall("Value",PerformingPhysiciansName);
    QAxObject *sRange23 = pSheet->querySubObject("Cells(int,int)",23,2);
    sRange23->dynamicCall("Value",OperatorsName);
    QAxObject *sRange24 = pSheet->querySubObject("Cells(int,int)",24,2);
    sRange24->dynamicCall("Value",ManufacturersModelName);
    QAxObject *sRange25 = pSheet->querySubObject("Cells(int,int)",25,2);
    sRange25->dynamicCall("Value","patientName");

    QAxObject *sRange26 = pSheet->querySubObject("Cells(int,int)",26,2);
    sRange26->dynamicCall("Value","RTID");
    QAxObject *sRange27 = pSheet->querySubObject("Cells(int,int)",27,2);
    sRange27->dynamicCall("Value","patientAge");
    QAxObject *sRange28 = pSheet->querySubObject("Cells(int,int)",28,2);
    sRange28->dynamicCall("Value","patientGender");
    QAxObject *sRange29 = pSheet->querySubObject("Cells(int,int)",29,2);
    sRange29->dynamicCall("Value",ScanOptions);
    QAxObject *sRange30 = pSheet->querySubObject("Cells(int,int)",30,2);
    sRange30->dynamicCall("Value",SliceThickness2);

    QAxObject *sRange31 = pSheet->querySubObject("Cells(int,int)",31,2);
    sRange31->dynamicCall("Value",KVP);
    QAxObject *sRange32 = pSheet->querySubObject("Cells(int,int)",32,2);
    sRange32->dynamicCall("Value",DataCollectionDiameter);
    QAxObject *sRange33 = pSheet->querySubObject("Cells(int,int)",33,2);
    sRange33->dynamicCall("Value",DeviceSerialNumber);
    QAxObject *sRange34 = pSheet->querySubObject("Cells(int,int)",34,2);
    sRange34->dynamicCall("Value",SoftwareVersions);
    QAxObject *sRange35 = pSheet->querySubObject("Cells(int,int)",35,2);
    sRange35->dynamicCall("Value",ProtocolName);

    QAxObject *sRange36 = pSheet->querySubObject("Cells(int,int)",36,2);
    sRange36->dynamicCall("Value",ReconstructionDiameter);
    QAxObject *sRange37 = pSheet->querySubObject("Cells(int,int)",37,2);
    sRange37->dynamicCall("Value",GantryDetectorTilt);
    QAxObject *sRange38 = pSheet->querySubObject("Cells(int,int)",38,2);
    sRange38->dynamicCall("Value",TableHeight);
    QAxObject *sRange39 = pSheet->querySubObject("Cells(int,int)",39,2);
    sRange39->dynamicCall("Value",RotationDirection );
    QAxObject *sRange40 = pSheet->querySubObject("Cells(int,int)",40,2);
    sRange40->dynamicCall("Value",ExposureTime);


    QAxObject *sRange41 = pSheet->querySubObject("Cells(int,int)",41,2);
    sRange41->dynamicCall("Value",XRayTubeCurrent);
    QAxObject *sRange42 = pSheet->querySubObject("Cells(int,int)",42,2);
    sRange42->dynamicCall("Value",ExposureInuAs);
    QAxObject *sRange43 = pSheet->querySubObject("Cells(int,int)",43,2);
    sRange43->dynamicCall("Value",FilterType);
    QAxObject *sRange44 = pSheet->querySubObject("Cells(int,int)",44,2);
    sRange44->dynamicCall("Value",GeneratorPower);
    QAxObject *sRange45 = pSheet->querySubObject("Cells(int,int)",45,2);
    sRange45->dynamicCall("Value",FocalSpots);

    QAxObject *sRange46 = pSheet->querySubObject("Cells(int,int)",46,2);
    sRange46->dynamicCall("Value",DateofLastCalibration);
    QAxObject *sRange47 = pSheet->querySubObject("Cells(int,int)",47,2);
    sRange47->dynamicCall("Value",TimeofLastCalibration);
    QAxObject *sRange48 = pSheet->querySubObject("Cells(int,int)",48,2);
    sRange48->dynamicCall("Value",ConvolutionKernel);
    QAxObject *sRange49 = pSheet->querySubObject("Cells(int,int)",49,2);
    sRange49->dynamicCall("Value",PatientPosition);
    QAxObject *sRange50 = pSheet->querySubObject("Cells(int,int)",50,2);
    sRange50->dynamicCall("Value",StudyInstanceUID);

    QAxObject *sRange51 = pSheet->querySubObject("Cells(int,int)",51,2);
    sRange51->dynamicCall("Value", SeriesInstanceUID);
    QAxObject *sRange52 = pSheet->querySubObject("Cells(int,int)",52,2);
    sRange52->dynamicCall("Value","StudyID");
    QAxObject *sRange53 = pSheet->querySubObject("Cells(int,int)",53,2);
    sRange53->dynamicCall("Value",SeriesNumber);
    QAxObject *sRange54 = pSheet->querySubObject("Cells(int,int)",54,2);
    sRange54->dynamicCall("Value",AcquisitionNumber);
    QAxObject *sRange55 = pSheet->querySubObject("Cells(int,int)",55,2);
    sRange55->dynamicCall("Value",InstanceNumber);

    QAxObject *sRange56 = pSheet->querySubObject("Cells(int,int)",56,2);
    sRange56->dynamicCall("Value",ImagePositionPatients[0]);
    QAxObject *sRange57 = pSheet->querySubObject("Cells(int,int)",57,2);
    sRange57->dynamicCall("Value",ImagePositionPatients[1]);
    QAxObject *sRange58 = pSheet->querySubObject("Cells(int,int)",58,2);
    sRange58->dynamicCall("Value",ImagePositionPatients[2]);
    QAxObject *sRange59 = pSheet->querySubObject("Cells(int,int)",59,2);
    sRange59->dynamicCall("Value",ImageOrientationPatient[0]);
    QAxObject *sRange60 = pSheet->querySubObject("Cells(int,int)",60,2);
    sRange60->dynamicCall("Value",ImageOrientationPatient[1]);

    QAxObject *sRange61 = pSheet->querySubObject("Cells(int,int)",61,2);
    sRange61->dynamicCall("Value",ImageOrientationPatient[2]);
    QAxObject *sRange62 = pSheet->querySubObject("Cells(int,int)",62,2);
    sRange62->dynamicCall("Value",ImageOrientationPatient[3]);
    QAxObject *sRange63 = pSheet->querySubObject("Cells(int,int)",63,2);
    sRange63->dynamicCall("Value",ImageOrientationPatient[4]);
    QAxObject *sRange64 = pSheet->querySubObject("Cells(int,int)",64,2);
    sRange64->dynamicCall("Value",ImageOrientationPatient[5]);
    QAxObject *sRange65 = pSheet->querySubObject("Cells(int,int)",65,2);
    sRange65->dynamicCall("Value",FrameofReferenceUID);

    QAxObject *sRange66 = pSheet->querySubObject("Cells(int,int)",66,2);
    sRange66->dynamicCall("Value",PositionReferenceIndicator);
    QAxObject *sRange67 = pSheet->querySubObject("Cells(int,int)",67,2);
    sRange67->dynamicCall("Value",SliceLocation);
    QAxObject *sRange68 = pSheet->querySubObject("Cells(int,int)",68,2);
    sRange68->dynamicCall("Value",SamplesperPixel);
    QAxObject *sRange69 = pSheet->querySubObject("Cells(int,int)",69,2);
    sRange69->dynamicCall("Value",PhotometricInterpretation);
    QAxObject *sRange70 = pSheet->querySubObject("Cells(int,int)",70,2);
    sRange70->dynamicCall("Value",Rows);

    QAxObject *sRange71 = pSheet->querySubObject("Cells(int,int)",71,2);
    sRange71->dynamicCall("Value",Columns);
    QAxObject *sRange72 = pSheet->querySubObject("Cells(int,int)",72,2);
    sRange72->dynamicCall("Value",SliceThickness2);
    QAxObject *sRange73 = pSheet->querySubObject("Cells(int,int)",73,2);
    sRange73->dynamicCall("Value",SliceThickness2);
    QAxObject *sRange74 = pSheet->querySubObject("Cells(int,int)",74,2);
    sRange74->dynamicCall("Value",BitsAllocated);
    QAxObject *sRange75 = pSheet->querySubObject("Cells(int,int)",75,2);
    sRange75->dynamicCall("Value",BitsStored);

    QAxObject *sRange76 = pSheet->querySubObject("Cells(int,int)",76,2);
    sRange76->dynamicCall("Value",HighBit);
    QAxObject *sRange77 = pSheet->querySubObject("Cells(int,int)",77,2);
    sRange77->dynamicCall("Value",PixelRepresentation);
    QAxObject *sRange78 = pSheet->querySubObject("Cells(int,int)",78,2);
    sRange78->dynamicCall("Value",SmallestImagePixelValue);
    QAxObject *sRange79 = pSheet->querySubObject("Cells(int,int)",79,2);
    sRange79->dynamicCall("Value",LargestImagePixelValue);
    QAxObject *sRange80 = pSheet->querySubObject("Cells(int,int)",80,2);
    sRange80->dynamicCall("Value",SmallestPixelValueinSeries);

    QAxObject *sRange81 = pSheet->querySubObject("Cells(int,int)",81,2);
    sRange81->dynamicCall("Value",LargestPixelValueinSeries);
    QAxObject *sRange82 = pSheet->querySubObject("Cells(int,int)",82,2);
    sRange82->dynamicCall("Value",QualityControlImage);
    QAxObject *sRange83 = pSheet->querySubObject("Cells(int,int)",83,2);
    sRange83->dynamicCall("Value",RescaleIntercept);
    QAxObject *sRange84 = pSheet->querySubObject("Cells(int,int)",84,2);
    sRange84->dynamicCall("Value",RescaleSlope);
    QAxObject *sRange85 = pSheet->querySubObject("Cells(int,int)",85,2);
    sRange85->dynamicCall("Value",PixelData);

    QAxObject *sRange86 = pSheet->querySubObject("Cells(int,int)",86,2);
    sRange86->dynamicCall("Value",WindowCenter);
    QAxObject *sRange87 = pSheet->querySubObject("Cells(int,int)",87,2);
    sRange87->dynamicCall("Value",WindowWidth);

    pWorkBook->dynamicCall("SaveAs(const QString &)",QDir::toNativeSeparators(fileName2));
    if (pApplication != nullptr) {
        pApplication->dynamicCall("Quit()");
        delete pApplication;
        pApplication = nullptr;
    }
}

void MainWindow::on_Access_clicked()
{
    QString remoteFilePath = R"(\\192.168.10.31\d\JawOffset_offline.txt)";

    QFile file(remoteFilePath);

    // Attempt to open the file in read-only mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line; // Process each line as needed
    }

    file.close();
}

void MainWindow::on_Blank_raw_clicked()
{
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());

    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    reader->SetImageIO(gdcmImage);
    try
    {
        reader->Update();

    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
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

//    image = reader->GetOutput();

//    const unsigned short *pixelBuffer = image->GetBufferPointer();

//    dispImg= new unsigned char[width*height];

    // Create a blank image with the same dimensions and pixel type
       Img::Pointer blankImage = Img::New();
       Img::RegionType region;
       Img::SizeType size = {width, height};
       region.SetSize(size);
       blankImage->SetRegions(region);
       blankImage->Allocate();

       // Set all pixel values to 0 (black), or 255 (white) if you prefer white
       itk::ImageRegionIterator<Img> it(blankImage, blankImage->GetLargestPossibleRegion());
       for (it.GoToBegin(); !it.IsAtEnd(); ++it) {
           it.Set(255);  // Set pixel value to 0 (black), use 255 for white
       }

       // Get the pixel buffer of the blank image
       const unsigned short* pixelBuffer = blankImage->GetBufferPointer();

    QString filename2=ui->lineEdit->text();
    int number=ui->lineEdit_2->text().toInt();
    std::string fileName3 = filename2.toStdString() + "\\proj_" + std::to_string(number) + ".raw";
    FILE *fp;
    fopen_s(&fp,fileName3.c_str(),"wb+");
    fwrite(pixelBuffer,sizeof(unsigned short),3072*3072,fp);
    fclose(fp);
    qDebug()<<"write finished";
}

void MainWindow::on_compress_CBCT_clicked()
{
    qDebug()<<"Enter 1";
    const unsigned int Dimension = 3;
    using PixelType = float;
    using ImageType = itk::Image<PixelType, Dimension>;

    qDebug()<<"Enter 2";
    QString Path="D:\\RTStructure Check shubam\\RT202411A23-Checked FF-Head Work\\S12_P2\\FG1_FN1\\Beam0\\ReferenceImages\\CT\\FF\\Updated";
    // Read DICOM series from a directory
    using NamesGeneratorType = itk::GDCMSeriesFileNames;
    auto namesGenerator = NamesGeneratorType::New();
    namesGenerator->SetDirectory(Path.toStdString());

    qDebug()<<"Enter 3";
    auto fileNames = namesGenerator->GetInputFileNames();
    for (const auto& fileName : fileNames) {
        std::cout << "DICOM file: " << fileName << std::endl;
    }

    using ReaderType = itk::ImageSeriesReader<ImageType>;
    auto reader = ReaderType::New();
    reader->SetFileNames(fileNames);

    auto gdcmIO = itk::GDCMImageIO::New();
    reader->SetImageIO(gdcmIO);

    reader->Update();

    qDebug()<<"Enter 4";



    auto inputImage = reader->GetOutput();

    qDebug()<<"Enter 5";

    // Get input image size and spacing
    ImageType::SizeType inputSize = inputImage->GetLargestPossibleRegion().GetSize();
    ImageType::SpacingType inputSpacing = inputImage->GetSpacing();

    qDebug()<<"Enter 6";

    // Define new size and spacing
    ImageType::SizeType outputSize;
    outputSize[0] = 256;
    outputSize[1] = 256;
    outputSize[2] = 256;

    qDebug()<<"Enter 7";

    ImageType::SpacingType outputSpacing;
    outputSpacing[0] = inputSpacing[0] * static_cast<double>(inputSize[0]) / outputSize[0];
    outputSpacing[1] = inputSpacing[1] * static_cast<double>(inputSize[1]) / outputSize[1];
    outputSpacing[2] = inputSpacing[2] * static_cast<double>(inputSize[2]) / outputSize[2];

    qDebug()<<"Enter 8";

    // Resample the image
    using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
    auto resampleFilter = ResampleFilterType::New();
    resampleFilter->SetInput(inputImage);
    resampleFilter->SetSize(outputSize);
    resampleFilter->SetOutputSpacing(outputSpacing);
    resampleFilter->SetOutputOrigin(inputImage->GetOrigin());
    resampleFilter->SetOutputDirection(inputImage->GetDirection());
    resampleFilter->SetTransform(itk::IdentityTransform<double, Dimension>::New());
    resampleFilter->SetInterpolator(itk::LinearInterpolateImageFunction<ImageType, double>::New());
    resampleFilter->Update();

    qDebug()<<"Enter 9";


    // Define your pixel type and image type
//    typedef itk::Image<PixelType3D, 3> ImageType;

    // Setup the ITK NIfTI writer
    typedef itk::ImageFileWriter<ImageType> WriterType;
    WriterType::Pointer writer = WriterType::New();

    // Set the NIfTI image IO
    itk::NiftiImageIO::Pointer niftiIO = itk::NiftiImageIO::New();
    writer->SetImageIO(niftiIO);

    // Set the output file name
    writer->SetFileName("D:\\RTStructure Check shubam\\output.nii");

    // Set the ITK image as input (assuming orienter_out is an itk::Image<PixelType3D, 3>::Pointer)
    writer->SetInput(resampleFilter->GetOutput());

    qDebug() << "Writing NIfTI file...";

    // Write the file
    try {
        writer->Update();
        qDebug() << "NIfTI file written successfully.";
    }
    catch (itk::ExceptionObject & error) {
        qDebug() << "Error writing NIfTI file: " << error.what();
    }

}



void MainWindow::on_on_crop_raw_clicked()
{


    int left,top,right,bottom,croppedWidth,croppedHeight;

    int width = 3072;  // Assuming width is 3072
    int height = 3072; // Assuming height is 3072

    QString filename = "D:\\RAD\\Imagin Quad working\\proj_3.raw";
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
    top = 0;   // Top remains 0 for cropping from upper height
    right = 3071-450;  // Width - 1, assuming width is 3072
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
    QString cropped1="D:\\RAD\\Imagin Quad working\\Right_crop.raw";
    fopen_s(&Fp1_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(croppedImage, sizeof(unsigned short), croppedWidth * croppedHeight, Fp1_cropped);
    fclose(Fp1_cropped);

    fclose(Img);
    delete[] dispImg;
    delete[] croppedImage;


    QString filename1 = "D:\\RAD\\Imagin Quad working\\proj_2.raw";
    if (filename1.isEmpty())
    {
        qDebug()<<"Could not open file";
    }
    FILE * Img1;
    Img1= fopen(filename1.toStdString().c_str(),"rb");

    unsigned short *dispImg1 = new unsigned short[width*height];

    fread(dispImg1,sizeof(unsigned short),width*height,Img1);

    // Find the bounding box of the non-black region
    left = 450;  // Left remains 0 for cropping from upper height
    top = 0;   // Top remains 0 for cropping from upper height
    right = 3071;  // Width - 1, assuming width is 3072
    bottom = 3071;  // Adjust bottom for upper height cropping

    // Crop the image using the bounding box
    croppedWidth = right - left + 1;
    croppedHeight = bottom - top + 1;
    unsigned short* croppedImage1 = new unsigned short[croppedWidth * croppedHeight];

    // Adjusting height for upper height cropping
    height = bottom + 1;

    // Copy upper part of the image to croppedImage
    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            croppedImage1[y * croppedWidth + x] = dispImg1[(top + y) * width + (left + x)];
        }
    }


    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

    FILE* Fp1_cropped1;
    QString cropped2="D:\\RAD\\Imagin Quad working\\left_crop.raw";
    fopen_s(&Fp1_cropped1, cropped2.toStdString().c_str(), "wb+");
    fwrite(croppedImage1, sizeof(unsigned short), croppedWidth * croppedHeight, Fp1_cropped1);
    fclose(Fp1_cropped1);

    fclose(Img1);
    delete[] dispImg1;
    delete[] croppedImage1;


    stitchlateral();
    qDebug() << "Left and Right side cropped images saved.";




}

void MainWindow::on_vertical_crop_clicked()
{
    int left,top,right,bottom,croppedWidth,croppedHeight;

    int width = 3072;  // Assuming width is 3072
    int height = 3072; // Assuming height is 3072

    QString filename = "D:\\RAD\\Imagin Quad working\\proj_2.raw";
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
    top = 0;   // Top remains 0 for cropping from upper height
    right = 3071;  // Width - 1, assuming width is 3072
    bottom = 3071-450;  // Adjust bottom for upper height cropping


    // Crop the image using the bounding box
    croppedWidth = right - left + 1;
    croppedHeight = bottom - top + 1;
    unsigned short* croppedImage = new unsigned short[croppedWidth * croppedHeight];

    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

    // Adjusting height for upper height cropping
//    height = bottom + 1;

    // Copy upper part of the image to croppedImage
    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            croppedImage[y * croppedWidth + x] = dispImg[(top + y) * width + (left + x)];
        }
    }

    FILE* Fp1_cropped;
    QString cropped1="D:\\RAD\\Imagin Quad working\\down_crop.raw";
    fopen_s(&Fp1_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(croppedImage, sizeof(unsigned short), croppedWidth * croppedHeight, Fp1_cropped);
    fclose(Fp1_cropped);

    fclose(Img);
    delete[] dispImg;
    delete[] croppedImage;

    QString filename1 = "D:\\RAD\\Imagin Quad working\\proj_1.raw";
    if (filename1.isEmpty())
    {
        qDebug()<<"Could not open file";
    }


    FILE * Img1;
    Img1= fopen(filename1.toStdString().c_str(),"rb");

    unsigned short *dispImg1 = new unsigned short[width*height];

    fread(dispImg1,sizeof(unsigned short),width*height,Img1);

    // Find the bounding box of the non-black region
    left = 0;  // Left remains 0 for cropping from upper height
    top = 450;   // Top remains 0 for cropping from upper height
    right = 3071;  // Width - 1, assuming width is 3072
    bottom = 3071;  // Adjust bottom for upper height cropping

    // Crop the image using the bounding box
    croppedWidth = right - left + 1;
    croppedHeight = bottom - top + 1;
    unsigned short* croppedImage1 = new unsigned short[croppedWidth * croppedHeight];

    qDebug()<<"Cropped width and height 2"<<croppedWidth<<croppedHeight;

    // Adjusting height for upper height cropping
//    height = bottom + 1;

    // Copy upper part of the image to croppedImage
    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            croppedImage1[y * croppedWidth + x] = dispImg1[(top + y) * width + (left + x)];
        }
    }

    qDebug()<<"Cropped width and height"<<croppedWidth<<croppedHeight;

    FILE* Fp1_cropped1;
    QString cropped2="D:\\RAD\\Imagin Quad working\\up_crop.raw";
    fopen_s(&Fp1_cropped1, cropped2.toStdString().c_str(), "wb+");
    fwrite(croppedImage1, sizeof(unsigned short), croppedWidth * croppedHeight, Fp1_cropped1);
    fclose(Fp1_cropped1);

    fclose(Img1);
    delete[] dispImg1;
    delete[] croppedImage1;

    stitchlogitudinal();

}
QByteArray MainWindow::imageToByteArray(const QString &imagePath) {
    QImage image(imagePath);
    if (image.isNull()) {
        qWarning() << "Error: Image could not be loaded.";
        return QByteArray();
    }

    // Use a buffer to convert the image to QByteArray in JPG format
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");  // save the image as a JPG in the buffer
    return byteArray;

}

void MainWindow::on_Converttobinary_clicked()
{
    qDebug()<<"Enter value";
    QString filename = "D:\\DR Screens\\Exposure screen ref images\\Exposure screen ref images\\7.LOWER PART\\Lower Part.png";
    QByteArray byteArray = imageToByteArray(filename);

    qDebug()<<"bytearray"<<byteArray;
    qDebug()<<"byte array is not empty"<<byteArray.size();

    if(byteArray.isEmpty())
    {
        qDebug()<<"byte array is empty";

    }
    QString dbName = "DR";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");
    if(db.open())
    {
        QSqlQuery query;
        query.prepare("UPDATE ReferenceImages SET ReferencedImage = ? "
                     "WHERE MainStudyListRefId = 7 AND ReferencedPosition = 'HIP'");
        query.addBindValue(byteArray);

        if(!query.exec()) {
            qDebug() << "Update failed:" << query.lastError().text();
        } else {
            qDebug() << "Successfully updated image data for MainStudyListRefId 2, LAT position";
            qDebug() << "Rows affected:" << query.numRowsAffected();
        }

        db.close();
    }


}

void MainWindow::on_Block_input_clicked()
{
        hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
        hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);

        if (!hKeyboardHook || !hMouseHook) {
            std::cerr << "Failed to install hooks." << std::endl;
//            return 1;
        }

        std::cout << "Keyboard and mouse input blocked for 5 seconds..." << std::endl;

        // Message loop (needed for hooks to stay alive)
        DWORD start = GetTickCount();
        MSG msg;
        while (GetTickCount() - start < 5000) {
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            Sleep(1); // Don't hog CPU
        }

        // Unhook
        UnhookWindowsHookEx(hKeyboardHook);
        UnhookWindowsHookEx(hMouseHook);

        std::cout << "Input unblocked." << std::endl;

}

//QByteArray decryptAES(QByteArray encryptedBase64, QByteArray key, QByteArray iv) {
//    QByteArray encrypted = QByteArray::fromBase64(encryptedBase64);
//    QByteArray decrypted(encrypted.size(), 0);

//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    int outLen1 = 0;
//    int outLen2 = 0;

//    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, (unsigned char*)key.data(), (unsigned char*)iv.data());
//    EVP_DecryptUpdate(ctx, (unsigned char*)decrypted.data(), &outLen1, (unsigned char*)encrypted.data(), encrypted.size());
//    EVP_DecryptFinal_ex(ctx, (unsigned char*)decrypted.data() + outLen1, &outLen2);

//    EVP_CIPHER_CTX_free(ctx);
//    decrypted.resize(outLen1 + outLen2);
//    return decrypted;
//}

QByteArray decryptAesFromCSharp(const QString &base64Encrypted, const QString &password) {
    QByteArray salt = QByteArray::fromHex("4976616e204d65647665646576");

    const int keyLength = 32;
    const int ivLength = 16;
    const int iterations = 10000;

    QByteArray keyIv(keyLength + ivLength, 0);
    int result = PKCS5_PBKDF2_HMAC(password.toUtf8().data(), password.size(),
                      reinterpret_cast<const unsigned char*>(salt.data()), salt.size(),
                      iterations, EVP_sha512(),
                      keyIv.size(),
                      reinterpret_cast<unsigned char*>(keyIv.data()));

    if (result != 1) {
        qWarning() << "PBKDF2 derivation failed.";
        return {};
    }

    QByteArray aesKey = keyIv.left(keyLength);
    QByteArray aesIv  = keyIv.mid(keyLength, ivLength);

    QByteArray encrypted = QByteArray::fromBase64(base64Encrypted.toUtf8());

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return {};

    QByteArray decrypted(encrypted.size() + AES_BLOCK_SIZE, 0);
    int outlen1 = 0, outlen2 = 0;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
        reinterpret_cast<const unsigned char*>(aesKey.constData()),
        reinterpret_cast<const unsigned char*>(aesIv.constData()))) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    if (!EVP_DecryptUpdate(ctx,
        reinterpret_cast<unsigned char*>(decrypted.data()), &outlen1,
        reinterpret_cast<const unsigned char*>(encrypted.constData()), encrypted.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    if (EVP_DecryptFinal_ex(ctx,
        reinterpret_cast<unsigned char*>(decrypted.data()) + outlen1, &outlen2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        qWarning() << "EVP_DecryptFinal_ex failed. Possible wrong key or corrupted input.";
        return {};
    }

    EVP_CIPHER_CTX_free(ctx);
    decrypted.resize(outlen1 + outlen2);
    return decrypted;
}

void MainWindow::on_Decrypt_clicked()
{
//    QString username="m";
//    QStringList temp;
//    QString pwd;
//    QString dbName = "Offline_Siddharth_Hospital";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
//    db.setDatabaseName("DRIVER={SQL Server};Server=192.168.10.103;Database="+dbName+";Uid=sa;Pwd=panacea");
//    if(db.open())
//    {
//        qDebug()<<"db is open";
//        QSqlQuery* Query = new QSqlQuery();

//        Query->prepare("SELECT * from UserModels  where UserId='"+username.trimmed()+"' ");
//        Query->exec();

//        while(Query->next())
//        {
//            for(int i=0;i<Query->record().count();i++)
//            {
//                temp.append(Query->value(i).toString());
//            }
//            qDebug()<<"temp"<<temp;
////            uname = temp[0];
//            pwd = temp.at(3) ;
//        }

//        db.close();
//    }

//    qDebug()<<"PWD"<<pwd;

    QString encryptedBase64 = "g587oy681OJlUs688mYpEF6sNy5Lszy2";
    QString password = "V6ZxaUQv8XKufvyQdtk1ZQ==";
    QByteArray decrypted = decryptAesFromCSharp(password, encryptedBase64);

    if (decrypted.size() % 2 != 0) {
        qWarning() << "Invalid UTF-16 data (not even length)";
//        return "";
    }
    qDebug() << "Decrypted text:" << QString::fromUtf16(reinterpret_cast<const ushort*>(decrypted.constData()));
}

void MainWindow::on_Dicom_lateral_crop_clicked()
{
    int left,top,right,bottom;

    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = "D:\\CapturedImages\\78946\\17-06-2025\\DICOM\\Simulation\\LATFOV\\DICOM\\proj_1.dcm";
    reader->SetFileName(fileName.toStdString().c_str());

    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    reader->SetImageIO(gdcmImage);
    try
    {
        reader->Update();

    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
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

    unsigned short *dispImg = new unsigned short[width*height];

    for(int i=0;i<width*height;++i)
    {
        //dispImg[i]=table_att[pixelBuffer[i]];
        dispImg[i] = pixelBuffer[i]*255/65535; //convert 16 bit image to 8 bit image for display in qt
    }

    left = 450;  // Left remains 0 for cropping from upper height
    top = 0;   // Top remains 0 for cropping from upper height
    right = width-1;  // Width - 1, assuming width is 3072
    bottom = height-1;  // Adjust bottom for upper height cropping

    // Crop the image using the bounding box
    int croppedWidth = right - left + 1;
    int croppedHeight = bottom - top + 1;
    unsigned short* croppedImage = new unsigned short[croppedWidth * croppedHeight];

    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            croppedImage[y * croppedWidth + x] = dispImg[(top + y) * width + (left + x)];
        }
    }

//   QString cropped1=Simulation_late_DICOM_Path+QString("\\Crop_1.dcm");

//   saveImageToDicomcropRT(croppedImage, cropped1,croppedWidth,croppedHeight);

   delete[] dispImg;

    Reader::Pointer reader1=Reader::New();
    Img::Pointer image1;
    QString fileName1 = "D:\\CapturedImages\\78946\\17-06-2025\\DICOM\\Simulation\\LATFOV\\DICOM\\proj_2.dcm";
    reader1->SetFileName(fileName1.toStdString().c_str());

    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage1=ImageType::New();
    reader1->SetImageIO(gdcmImage1);
    try
    {
        reader1->Update();

    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
    }
    itk::MetaDataDictionary dict1;
    dict1 = reader1->GetMetaDataDictionary();

    std::string Rows2;
    itk::ExposeMetaData(dict1,"0028|0010",Rows2);

    std::string Cols2;
    itk::ExposeMetaData(dict1,"0028|0011",Cols2);


    QString Rows3=Rows2.c_str();
    QString Cols3=Cols2.c_str();
    qDebug()<<"rows"<<Rows3;
    qDebug()<<"cols"<<Cols3;

    int height1 = Rows3.toInt();
    int width1 = Cols3.toInt();

    image1 = reader1->GetOutput();

    const unsigned short *pixelBuffer1 = image1->GetBufferPointer();

    unsigned short *dispImg1 = new unsigned short[width1*height1];

    for(int i=0;i<width1*height1;++i)
    {
        //dispImg[i]=table_att[pixelBuffer[i]];
        dispImg1[i] = pixelBuffer1[i]*255/65535; //convert 16 bit image to 8 bit image for display in qt
    }

    qDebug()<<"check1";

    left = 0;  // Left remains 0 for cropping from upper height
    top = 0;   // Top remains 0 for cropping from upper height
    right = width1-1-450;  // Width - 1, assuming width is 3072
    bottom = height1-1;  // Adjust bottom for upper height cropping

    qDebug()<<"check2";


    // Crop the image using the bounding box
    int croppedWidth1 = right - left + 1;
    int croppedHeight1 = bottom - top + 1;
    unsigned short* croppedImage1 = new unsigned short[croppedWidth1 * croppedHeight1];

    // Adjusting height for upper height cropping
//            height = bottom + 1;

    qDebug()<<"check3";

    // Copy upper part of the image to croppedImage
    for (int y = 0; y < croppedHeight1; ++y) {
        for (int x = 0; x < croppedWidth1; ++x) {
            croppedImage1[y * croppedWidth1 + x] = dispImg1[(top + y) * width1 + (left + x)];
        }
    }

//    QString cropped2="D:\\CapturedImages\\78946\\17-06-2025\\DICOM\\Simulation\\LATFOV\\DICOM\\Crop_2.dcm";

//    saveImageToDicomcropRT(croppedImage1, cropped2,croppedWidth1,croppedHeight1);

    delete[] dispImg1;


    int finalHeight = std::max(croppedHeight, croppedHeight1);
    int finalWidth = croppedWidth + croppedWidth1;

    unsigned short* stitchedImage = new unsigned short[finalWidth * finalHeight];

    // Initialize with black pixels (optional)
//       std::fill(stitchedImage, stitchedImage + finalWidth * finalHeight, 0);

    // Copy first image
    for (int y = 0; y < croppedHeight; ++y) {
        for (int x = 0; x < croppedWidth; ++x) {
            stitchedImage[y * finalWidth + x] = croppedImage[y * croppedWidth + x];
        }
    }

    // Copy second image
    for (int y = 0; y < croppedHeight1; ++y) {
        for (int x = 0; x < croppedWidth1; ++x) {
            stitchedImage[y * finalWidth + (x + croppedWidth)] = croppedImage1[y * croppedWidth1 + x];
        }
    }


    FILE* Fp831_cropped;
    QString cropped1 = "D:\\CapturedImages\\78946\\17-06-2025\\DICOM\\Simulation\\LATFOV\\DICOM\\Stitched_horizontal.raw";
    fopen_s(&Fp831_cropped, cropped1.toStdString().c_str(), "wb+");
    fwrite(stitchedImage, sizeof(unsigned short), finalWidth * finalHeight, Fp831_cropped);
    fclose(Fp831_cropped);



        qDebug()<<"Stitched image width and height"<<finalWidth<<finalHeight;
    // Save stitched image
//    QString stitchedPath = Simulation_late_DICOM_Path + QString("\\Stitched_Image.dcm");
//    saveImageToDicomcropRT(stitchedImage, stitchedPath, finalWidth, finalHeight);

    delete[] croppedImage1;
    delete[] croppedImage;

        int radSize=3072;
        // Assuming you have a vector to store the downsampled image
        std::vector<unsigned short> downsampledImage(radSize * radSize);

        // Call the function to downsample the image
        downsampleImageHorizontal(stitchedImage, downsampledImage,finalWidth,finalHeight,radSize,radSize);



}

void MainWindow::on_longitudinalfive_clicked()
{

    int width = 3072;
    int singleHeight = 3072;
    int totalHeight = singleHeight * 5;

    // Allocate memory
    unsigned short* topImage = new unsigned short[width * singleHeight];
    unsigned short* bottomImage = new unsigned short[width * singleHeight];
    unsigned short* bottomImage1 = new unsigned short[width * singleHeight];
    unsigned short* bottomImage2 = new unsigned short[width * singleHeight];
    unsigned short* bottomImage3 = new unsigned short[width * singleHeight];
    unsigned short* stitchedImage = new unsigned short[width * totalHeight];

    // Load top image
    QString topPath = "D:\\RAD\\DR.raw";
    FILE* fTop = fopen(topPath.toStdString().c_str(), "rb");
    if (!fTop) {
        qDebug() << "Could not open top image.";
        return;
    }
    fread(topImage, sizeof(unsigned short), width * singleHeight, fTop);
    fclose(fTop);

    //============================================================================
    // Load bottom image
    QString bottomPath = "D:\\RAD\\DR.raw";
    FILE* fBottom = fopen(bottomPath.toStdString().c_str(), "rb");
    if (!fBottom) {
        qDebug() << "Could not open bottom image.";
        delete[] topImage;
        return;
    }
    fread(bottomImage, sizeof(unsigned short), width * singleHeight, fBottom);
    fclose(fBottom);

    //============================================================================

    QString bottomPath1 = "D:\\RAD\\DR.raw";
    FILE* fBottom1 = fopen(bottomPath1.toStdString().c_str(), "rb");
    if (!fBottom1) {
        qDebug() << "Could not open bottom image.";
        delete[] fBottom;
        return;
    }
    fread(bottomImage1, sizeof(unsigned short), width * singleHeight, fBottom1);
    fclose(fBottom1);

    //===========================================================================

    QString bottomPath2 = "D:\\RAD\\DR.raw";
    FILE* fBottom2 = fopen(bottomPath2.toStdString().c_str(), "rb");
    if (!fBottom2) {
        qDebug() << "Could not open bottom image.";
        delete[] fBottom1;
        return;
    }
    fread(bottomImage2, sizeof(unsigned short), width * singleHeight, fBottom2);
    fclose(fBottom2);


    //==========================================================================

    QString bottomPath3 = "D:\\RAD\\DR.raw";
    FILE* fBottom3 = fopen(bottomPath3.toStdString().c_str(), "rb");
    if (!fBottom3) {
        qDebug() << "Could not open bottom image.";
        delete[] fBottom2;
        return;
    }
    fread(bottomImage3, sizeof(unsigned short), width * singleHeight, fBottom3);
    fclose(fBottom3);
    //=========================================================================

    // Stitch vertically
    for (int y = 0; y < singleHeight; ++y) {
        // Top part
        memcpy(&stitchedImage[y * width],
               &topImage[y * width],
               width * sizeof(unsigned short));

        // Bottom part
        memcpy(&stitchedImage[(y + singleHeight) * width],
               &bottomImage[y * width],
               width * sizeof(unsigned short));

        // Bottom image (third part)
        memcpy(&stitchedImage[(y + 2 * singleHeight) * width],
               &bottomImage1[y * width],
               width * sizeof(unsigned short));

        memcpy(&stitchedImage[(y + 3 * singleHeight) * width],
               &bottomImage2[y * width],
               width * sizeof(unsigned short));

        memcpy(&stitchedImage[(y + 4 * singleHeight) * width],
               &bottomImage3[y * width],
               width * sizeof(unsigned short));
    }

//=================================================================================

//    // Save stitched image
//    QString stitchedPath = "D:\\RAD\\DR.raw";
//    FILE* fOut = fopen(stitchedPath.toStdString().c_str(), "wb+");
//    if (fOut) {
//        fwrite(stitchedImage, sizeof(unsigned short), width * totalHeight, fOut);
//        fclose(fOut);
//        qDebug() << "Stitched image saved as" << stitchedPath;
//    } else {
//        qDebug() << "Failed to write stitched image.";
//    }

    // Cleanup
    delete[] topImage;
    delete[] bottomImage;
    delete[] bottomImage1;
    delete[] bottomImage2;
    delete[] bottomImage3;
//    delete[] stitchedImage;
    int radSize=3072;
    // Assuming you have a vector to store the downsampled image
    std::vector<unsigned short> downsampledImage(radSize * radSize);

    // Call the function to downsample the image
    downsampleImageVertical(stitchedImage, downsampledImage,width,totalHeight,radSize,radSize);
}

void MainWindow::on_lateralfive_clicked()
{
    int singleWidth = 3072;
    int height = 3072;
    int totalWidth = singleWidth * 5;

    // Allocate buffers for left, right, and stitched images
    unsigned short* leftImage = new unsigned short[singleWidth * height];
    unsigned short* rightImage = new unsigned short[singleWidth * height];
    unsigned short* rightImage1 = new unsigned short[singleWidth * height];
    unsigned short* rightImage2 = new unsigned short[singleWidth * height];
    unsigned short* rightImage3 = new unsigned short[singleWidth * height];
    unsigned short* stitchedImage = new unsigned short[totalWidth * height];

    // Load left image
    QString leftPath = "D:\\RAD\\DR.raw";
    FILE* fLeft = fopen(leftPath.toStdString().c_str(), "rb");
    if (!fLeft) {
        qDebug() << "Could not open left image.";
        return;
    }
    fread(leftImage, sizeof(unsigned short), singleWidth * height, fLeft);
    fclose(fLeft);

    //=================================================================
    // Load right image
    QString rightPath = "D:\\RAD\\DR.raw";;
    FILE* fRight = fopen(rightPath.toStdString().c_str(), "rb");
    if (!fRight) {
        qDebug() << "Could not open right image.";
        delete[] leftImage;
        return;
    }
    fread(rightImage, sizeof(unsigned short), singleWidth * height, fRight);
    fclose(fRight);
    //=================================================================

    // Load right image 1
    QString rightPath1 = "D:\\RAD\\DR.raw";;
    FILE* fRight1 = fopen(rightPath1.toStdString().c_str(), "rb");
    if (!fRight1) {
        qDebug() << "Could not open right image.";
        delete[] rightImage;
        return;
    }
    fread(rightImage1, sizeof(unsigned short), singleWidth * height, fRight1);
    fclose(fRight1);


    //=================================================================
    // Load right image 2
    QString rightPath2 = "D:\\RAD\\DR.raw";;
    FILE* fRight2 = fopen(rightPath2.toStdString().c_str(), "rb");
    if (!fRight2) {
        qDebug() << "Could not open right image.";
        delete[] rightImage1;
        return;
    }
    fread(rightImage2, sizeof(unsigned short), singleWidth * height, fRight2);
    fclose(fRight2);


    //=================================================================
    // Load right image 3
    QString rightPath3 = "D:\\RAD\\DR.raw";;
    FILE* fRight3 = fopen(rightPath3.toStdString().c_str(), "rb");
    if (!fRight3) {
        qDebug() << "Could not open right image.";
        delete[] rightImage2;
        return;
    }
    fread(rightImage3, sizeof(unsigned short), singleWidth * height, fRight3);
    fclose(fRight3);

    //==================================================================

    // Stitch: Copy left and right images side-by-side
    for (int y = 0; y < height; ++y) {
        // Copy left part
        memcpy(&stitchedImage[y * totalWidth],
               &leftImage[y * singleWidth],
               singleWidth * sizeof(unsigned short));

        // Copy right part
        memcpy(&stitchedImage[y * totalWidth + singleWidth],
               &rightImage[y * singleWidth],
               singleWidth * sizeof(unsigned short));

        // Third image
        memcpy(&stitchedImage[y * totalWidth + 2 * singleWidth],
               &rightImage1[y * singleWidth],
               singleWidth * sizeof(unsigned short));

        // Fourth image
        memcpy(&stitchedImage[y * totalWidth + 3 * singleWidth],
               &rightImage2[y * singleWidth],
               singleWidth * sizeof(unsigned short));

        // Fifth image
        memcpy(&stitchedImage[y * totalWidth + 4 * singleWidth],
               &rightImage3[y * singleWidth],
               singleWidth * sizeof(unsigned short));
    }

//    // Save stitched image
//    qDebug()<<"Total width"<<totalWidth<<height;
//    QString stitchedPath = "D:\\RAD\\DR.raw";
//    FILE* fOut = fopen(stitchedPath.toStdString().c_str(), "wb+");
//    if (fOut) {
//        fwrite(stitchedImage, sizeof(unsigned short), totalWidth * height, fOut);
//        fclose(fOut);
//        qDebug() << "Stitched image saved as" << stitchedPath;
//    } else {
//        qDebug() << "Failed to write stitched image.";
//    }

    // Clean up
    delete[] leftImage;
    delete[] rightImage;
    delete[] rightImage1;
    delete[] rightImage2;
    delete[] rightImage3;

//    delete[] stitchedImage;

    int radSize=3072;
    // Assuming you have a vector to store the downsampled image
    std::vector<unsigned short> downsampledImage(radSize * radSize);

    // Call the function to downsample the image
    downsampleImageHorizontal(stitchedImage, downsampledImage,totalWidth,height,radSize,radSize);
}
