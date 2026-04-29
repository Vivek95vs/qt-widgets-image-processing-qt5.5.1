#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVTKWidget.h>

float lowerThreshold;
float upperThreshold;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene1=new customscene(this);
    scene2=new customscene(this);
    scene3=new customscene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Rendering_clicked()
{
    QString fPath = "D:\\CBCT"; // Path for the DICOM Image Folder in "fPath" of QString
    if(fPath == 0||fPath == "")
    {
        QMessageBox::critical(this,"Error","No path found !!");
    }
    QDir dir(fPath);
    QStringList filters;
    QStringList dcmList;

    if(!dir.exists())
    {
        QMessageBox::critical(this,"Error","Directory does not exists !!");
    }
    filters << "*.dcm";
    dir.setNameFilters(filters);
    dcmList = dir.entryList(filters);

    qDebug()<<"Number of CBCT dicom files : "<<dcmList.length()<<" *** ";

    if(dcmList.length()==0)
    {
        QMessageBox::critical(this, "Error","No Images Found..");
        return;
    }

    vtkSmartPointer<vtkDICOMReader> CBCTReader;
    CBCTReader = vtkSmartPointer<vtkDICOMReader>::New();
    QString path1 = "D:\\CBCT";
    CBCTReader = dicomRead(path1);

    dimension =  CBCTReader->GetOutput()->GetDimensions();
    qDebug()<<"CBCT Dimension[0] :"<<dimension[0];
    qDebug()<<"CBCT Dimension[1] :"<<dimension[1];
    qDebug()<<"CBCT Dimension[2] :"<<dimension[2];

    vtkImageData* imageData = CBCTReader->GetOutput();
    int scalarType = imageData->GetScalarType();

    // Print scalar type
    std::cout << "Scalar Type: " << imageData->GetScalarTypeAsString() << std::endl;

    if (scalarType == VTK_UNSIGNED_SHORT) {
        std::cout << "The image is 16-bit unsigned short." << std::endl;
    } else if (scalarType == VTK_SHORT) {
        std::cout << "The image is 16-bit signed short." << std::endl;
    } else {
        std::cout << "The image is of a different type: " << imageData->GetScalarTypeAsString() << std::endl;
    }



    volSize1 = dimension[0];
    volSize2 = dimension[1];
    volSize3 = dimension[2];
    qDebug()<<volSize1;
    qDebug()<<volSize2;
    qDebug()<<volSize3;

    float x;
    x = volSize1*volSize2*volSize3;
    qDebug()<<"Volume of 3D ImageS: "<<x;
    cbctvolume = new float[dimension[0]*dimension[1]*dimension[2]];

    cbctslice = new unsigned char[dimension[0]*dimension[1]];

    qDebug()<<"volume export function call in the main function";
    setVtkVolumeToC(cbctvolume); // commen for a while

    lowerThreshold = cbctvolume[0];
    upperThreshold = cbctvolume[0];

    for (int j = 1; j < 512 * 512 * 512; j++) {
        if (cbctvolume[j] < lowerThreshold) {
            lowerThreshold = cbctvolume[j];
        }
        if (cbctvolume[j] > upperThreshold) {
            upperThreshold = cbctvolume[j];
        }
    }

    qDebug() << "Lower Threshold:" << lowerThreshold;
    qDebug() << "Upper Threshold:" << upperThreshold;
    if(cbctvolume!= NULL)
    {
        qDebug()<<"VOLUME PRESENT";

    }
    qDebug()<<"volume export function performed successfully";

    scaleFactor=1024/dimension[0];
    double pixPitch=(static_cast<double>(dimension[0])/volSize1)/scaleFactor; /*only 1/scalefactor*/
    pixSpacingCBCT.clear();
    pixSpacingCBCT<<pixPitch;
    pixSpacingCBCT<<pixPitch;
    pixSpacingCBCT<<pixPitch;
    qDebug()<<"Hello Debug 1 ";
    qDebug()<<"Pixel Spacing : "<<pixPitch;
    qDebug()<<"Pixel Spacing : "<<pixPitch;
    qDebug()<<"Pixel Spacing : "<<pixPitch;

    this->display3D(cbctvolume,dimension,pixPitch);
    if(cbctvolume!= NULL)
    {
        qDebug()<<"VOLUME PRESENT";

    }
    qDebug()<<"display3D function performed successfully";

    ui->Lowerthresh->setRange(lowerThreshold,upperThreshold);
    ui->Upperthresh->setRange(lowerThreshold,upperThreshold);
    ui->Lowerthresh->setValue(lowerThreshold);
    ui->Upperthresh->setValue(upperThreshold);

}

vtkSmartPointer<vtkDICOMReader> MainWindow::dicomRead(QString path)
{
    vtkSmartPointer<vtkDICOMDirectory>dicomdir = vtkSmartPointer<vtkDICOMDirectory>::New();
    dicomdir->SetDirectoryName(/*dicomFolder*/path.toStdString().c_str());
    try
    {
        dicomdir->Update();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        return 0;
    }
    qDebug()<<"Dicom reader directry updated";
    vtkSmartPointer<vtkDICOMReader>reader1 = vtkSmartPointer<vtkDICOMReader>::New();
    int numSeries=dicomdir->GetNumberOfSeries();
    vtkStringArray *sortedFiles;
    QString rtStructFile;
    qDebug()<<"Number of Series found :"<<numSeries;
    sortedFiles = dicomdir->GetFileNamesForSeries(numSeries-1);
    for(int i=0;i<sortedFiles->GetNumberOfValues();i++)
    {
        qDebug()<<"Image "<<i;
        if(reader1->CanReadFile(sortedFiles->GetValue(i)))
        {
            reader1->SetFileName(sortedFiles->GetValue(i));
            reader1->SetGlobalWarningDisplay(false);
            try
            {
                reader1->Update();
            }
            catch(...)
            {
                qDebug()<<"Exception  reading dicom files";
                return 0;
            }
            if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTSTRUCT")==0)
            {
                rtStructFile = sortedFiles->GetValue(i);
            }
        }
    }
    qDebug()<<"reader1 updated that shorted the files";
    reader1=NULL;

    reader =vtkSmartPointer<vtkDICOMReader>::New();

    reader->SetFileNames(sortedFiles);
    reader->SetDataScalarTypeToShort();
    reader->SetMemoryRowOrderToFileNative();
    qDebug()<<"reached here ";
    try
    {
        reader->Update();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        return 0;
    }

    qDebug()<<"reader updated";
    return reader;
    qDebug()<<"reader returned as output of the function";
}

void MainWindow::setVtkVolumeToC(float *Vol)
{
    vtkSmartPointer<vtkImageExport>exporter = vtkSmartPointer<vtkImageExport>::New();
    exporter->SetInputData(reader->GetOutput());
    qDebug()<<"Test #first";
    exporter->ImageLowerLeftOn();//default
    try
    {
        exporter->Update();
        qDebug()<<"cbctreconexporter->Update()";

    }
    catch(...)
    {
        return;
    }
    v=(short*)exporter->GetPointerToData();//since data is huge get only pointer to memory

    for(int j=0; j<512*512*512; j++)
    {

        Vol[j]=static_cast<float>(v[j]);
    }
    qDebug()<<"Volume exporter funtion executed successfully";

}

void MainWindow::display3D(float *volume, const int *dimension, double pixPitch)
{
//    vtkWidget = new QVTKWidget(this);

    Scene=new MyWidget(this);

    volumeImport = vtkImageImport::New();
    ui->verticalLayout->addWidget(Scene);

    // volume Import
    volumeImport->CopyImportVoidPointer(volume, sizeof(float)*dimension[0]*dimension[1]*dimension[2]);
    volumeImport->SetWholeExtent(0,dimension[0]-1, 0,dimension[1]-1, 0,dimension[2]-1);

    volumeImport->SetDataScalarTypeToFloat();
    volumeImport->SetNumberOfScalarComponents(1);

    volumeImport->SetDataExtentToWholeExtent();
    volumeImport->SetDataSpacing(double(pixPitch), double(pixPitch), double(pixPitch));

    // 3D GAUSSIAN FILTER
    qDebug()<<"Mapper is initialized";
    vtkImageGaussianSmooth *gaussFilter = vtkImageGaussianSmooth::New();  // for smoothening of the Image
    gaussFilter->SetInputConnection(volumeImport->GetOutputPort());
    gaussFilter->SetRadiusFactors(1.5, 1.5, 1.5);
    gaussFilter->SetStandardDeviations(1.0, 1.0, 1.0);
    gaussFilter->Update();
    qDebug()<<"we are not using GPU int this case";

    vtkGPUVolumeRayCastMapper *volumeGPUmapper = vtkGPUVolumeRayCastMapper::New();

    volumeGPUmapper->SetInputConnection(gaussFilter->GetOutputPort());
    //Actor

    vtkVolume *VTKvolume = vtkVolume::New();

    VTKvolume->SetMapper(volumeGPUmapper);

    double skinOnBlueMap[8][5] =
    {
        {-923, 0.987853825092316, 1.0,               1.0,               0.0},
        {-733, 0.987853825092316, 1.0,               1.0,               0.00750770070067319},
        {-531, 0.987853825092316, 1.0,               1.0,               0.0733569149832789},
        {-372, 0.987853825092316, 1.0,               1.0,               0.0},
        { 142, 0.0,               0.0,               0.0,               0.0},
        { 332, 1.0,               0.0,               0.0,               0.132020258336102},
        { 534, 1.0,               0.999206542968750, 0.0,               0.317781232734010},
        { 679, 1.0,               1.0,               1.0,               0.940655276334784}
    };

    // Apply colormap
    alphaChannelFunc = vtkPiecewiseFunction::New();
    colorFunc = vtkColorTransferFunction::New();
    for(int i = 0; i < sizeof(skinOnBlueMap)/(5*sizeof(double)); i++)
    {
        colorFunc->AddRGBPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][1], skinOnBlueMap[i][2], skinOnBlueMap[i][3]);
        alphaChannelFunc->AddPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][4]);
    }

    // PropertyEditor
    vtkVolumeProperty  *volumeProperty = vtkVolumeProperty::New();
    volumeProperty->SetColor(colorFunc);
    volumeProperty->SetScalarOpacity(alphaChannelFunc);
    VTKvolume->SetProperty(volumeProperty);

    //Renderer
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();

    camera->Pitch(180);
    camera->Roll(180);
    camera->Yaw(180);

    ren = vtkRenderer::New();
    ren->AddVolume(VTKvolume);
    ren->SetBackground(0, 0, 0);

    //Renderer window
//    vtkWidget->GetRenderWindow()->AddRenderer(ren);
    Scene->GetRenderWindow()->AddRenderer(ren);

    ren->SetActiveCamera(camera);
    qDebug()<<"Rendering Initiated";
    ren->ResetCamera();
    qDebug()<<" Renderer Window operation in the display3D Function";

//    vtkWidget->GetRenderWindow()->Render();
//    vtkWidget->update();
    Scene->GetRenderWindow()->Render();
    Scene->update();
    qDebug()<<"Rendering applied successfully";
}

void MainWindow::on_Sagital_clicked()
{
    int value=256;

    cbctslice = getSagitalSlice(cbctvolume,value);
    scene1->clear();

    QImage img(cbctslice, 512, 512, QImage::Format_Indexed8);

    pixMap=new QGraphicsPixmapItem;
    pixMap->setPixmap(QPixmap::fromImage(img));
    pixMap->setFlag(QGraphicsItem::ItemIsSelectable,false);
    scene1->addItem(pixMap);
    ui->graphicsView_SAG->setScene(scene1);
    ui->graphicsView_SAG->fitInView(pixMap);
}

void MainWindow::on_Axial_clicked()
{
    int value=256;

    cbctslice = getAxialSlice(cbctvolume,value);
    scene2->clear();

    QImage img(cbctslice, 512, 512, QImage::Format_Indexed8);

    pixMap=new QGraphicsPixmapItem;
    pixMap->setPixmap(QPixmap::fromImage(img));
    pixMap->setFlag(QGraphicsItem::ItemIsSelectable,false);
    scene2->addItem(pixMap);
    ui->graphicsView_AX->setScene(scene2);
    ui->graphicsView_AX->fitInView(pixMap);

}

void MainWindow::on_Frontal_clicked()
{
    int value=256;

    cbctslice = getFrontalSlice(cbctvolume,value);
    scene3->clear();

    QImage img(cbctslice, 512, 512, QImage::Format_Indexed8);

    pixMap=new QGraphicsPixmapItem;
    pixMap->setPixmap(QPixmap::fromImage(img));
    pixMap->setFlag(QGraphicsItem::ItemIsSelectable,false);
    scene3->addItem(pixMap);
    ui->graphicsView_FRONT->setScene(scene3);
    ui->graphicsView_FRONT->fitInView(pixMap);
}

unsigned char * MainWindow::getAxialSlice(float* vol,int value)
{
    axialSliceCT=new unsigned char[512*512];
    for(int iPixel = 0; iPixel < vDIM*vDIM; iPixel++)
    {
        // clip values < LT to LT, values > UT to UT
        if(vol[(value) * vDIM * vDIM + iPixel] <= lowerThreshold)
        {
            axialSliceCT[iPixel] = 0;
        }
        else if(vol[(value) * vDIM * vDIM + iPixel] >= upperThreshold)
        {
            axialSliceCT[iPixel] = 255;
        }
        // scale the image such that LT = 0 and UT = 255
        else
        {
            axialSliceCT[iPixel] = (unsigned char)(((vol[(value) * vDIM * vDIM + iPixel]- lowerThreshold) * 255.0f)/(upperThreshold - lowerThreshold));
        }
    }
    return axialSliceCT;
}

unsigned char * MainWindow::getFrontalSlice(float* vol,int value)
{
    frontalSliceCT= new unsigned char[512*512];
    int index = 0;
    for(int iRow = 0; iRow < vDIM; iRow++)
    {
        for(int iCol = 0; iCol < vDIM; iCol++)
        {
            index = (vDIM-value-1) * vDIM + vDIM * vDIM * (vDIM-iRow-1) + iCol;
            // clip values < LT to LT, values > UT to UT
            if(vol[index] <= lowerThreshold)
            {
                frontalSliceCT[iRow * vDIM + iCol] = 0;
            }
            else if(vol[index] >= upperThreshold)
            {
                frontalSliceCT[iRow * vDIM + iCol] = 255;
            }
            // scale the image such that LT = 0 and UT = 255
            else
            {
                frontalSliceCT[iRow * vDIM + iCol] = (unsigned char)(((vol[index] - lowerThreshold) * 255.0f) /(upperThreshold - lowerThreshold));
            }
        }
    }

    return frontalSliceCT;
}

unsigned char * MainWindow::getSagitalSlice(float* vol,int value)
{
    sagitalSliceCT = new unsigned char[512*512];
    int index = 0;
    for(int iRow = 0; iRow < vDIM; iRow++)
    {
        for(int iCol = 0; iCol < vDIM; iCol++)
        {
            index = (/*vDIM-*/value/*-1*/) + vDIM * iCol + vDIM * vDIM * (/*vDIM-*/iRow/*-1*/);
            // clip values < LT to LT, values > UT to UT
            if(vol[index] <= lowerThreshold)
            {
                sagitalSliceCT[iRow * vDIM+ iCol] = 0;
            }
            //                    sagitalSliceCT[iRow  +iCol* vDIM ] = 0;
            else if(vol[index] >= upperThreshold)
            {
                sagitalSliceCT[iRow * vDIM  +iCol ] = 255;
            }
            // scale the image such that LT = 0 and UT = 255
            else
            {
                sagitalSliceCT[iRow * vDIM  +iCol ] = (unsigned char)(((vol[index] - lowerThreshold) * 255.0f) /(upperThreshold - lowerThreshold));
            }
        }
    }

    return sagitalSliceCT;
}

void MainWindow::on_PB_Ellipse_clicked()
{
    Scene->selectedTool=1;
}

void MainWindow::on_PB_Rectangle_clicked()
{
    Scene->selectedTool=2;
}

void MainWindow::on_PB_Freehand_clicked()
{
    scene1->selectedDraw=3;
    scene2->selectedDraw=3;
    scene3->selectedDraw=3;
}

void MainWindow::on_PB_Circle_clicked()
{
    scene1->selectedDraw=2;
    scene2->selectedDraw=2;
    scene3->selectedDraw=2;
}

void MainWindow::on_PB_Rect_clicked()
{
    scene1->selectedDraw=1;
    scene2->selectedDraw=1;
    scene3->selectedDraw=1;

}

void MainWindow::on_PB_Clear_clicked()
{
    scene1->clear();
    scene2->clear();
    scene3->clear();
}

void MainWindow::on_PB_clear_clicked()
{
    Scene->deleteLater();
}

void MainWindow::on_PB_Delete_clicked()
{
    QList<QGraphicsItem *>Items1=scene1->selectedItems();
    foreach(QGraphicsItem *item, Items1)
    {
               scene1->removeItem(item);
               delete(item);

    }

    QList<QGraphicsItem *>Items2=scene2->selectedItems();
    foreach(QGraphicsItem *item, Items2)
    {
               scene2->removeItem(item);
               delete(item);

    }

    QList<QGraphicsItem *>Items3=scene3->selectedItems();
    foreach(QGraphicsItem *item, Items3)
    {
               scene3->removeItem(item);
               delete(item);

    }
}

void MainWindow::on_Lowerthresh_valueChanged(int value)
{
    lowerThreshold=value;

    ui->MInThresh->setText(QString::number(lowerThreshold));

    qDebug()<<"Lower thresh value"<<lowerThreshold;
    on_Axial_clicked();
    on_Frontal_clicked();
    on_Sagital_clicked();
}

void MainWindow::on_Upperthresh_valueChanged(int value)
{
    upperThreshold=value;

    ui->MaxThresh->setText(QString::number(upperThreshold));
    qDebug()<<"Upper thresh value"<<value;
    on_Axial_clicked();
    on_Frontal_clicked();
    on_Sagital_clicked();
}
