#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVTKWidget.h>
double xS;
double yS;
double wS;
double hS;

int ctDIM1;
int ctDIM2;
int ctDIM3;

int axialSliderValue;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ascene = new customescene;
    fscene = new customescene;
    sscene = new customescene;

    ascene->setScene(ascene,fscene,sscene,customescene::Mode::NoMode);

    ui->axialSlider->setMaximum(511);
    ui->axialSlider->setMinimum(0);

    xS=-4;
    yS=-4;
    wS=8;
    hS=8;

    ui->sagitalSlider->setMaximum(511);
    ui->sagitalSlider->setMinimum(0);

    ui->frontalSlider->setMaximum(511);
    ui->frontalSlider->setMinimum(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /* ----- ***** Using QWidget Here ***** ----- */
    QProgressDialog progressDialog("Please Wait", "", 0, INT_MAX, this); // ProgressBar Dialog initiated
    progressDialog.setWindowTitle("Loading Images...");  // ProgressBar action
    progressDialog.setCancelButton(0);

    QProgressBar * bar = new QProgressBar(&progressDialog);
    progressDialog.setBar(bar);

    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.show();
    bar->setValue(0);  // have to see because it is of Public Slot

    QApplication::processEvents();

    _sleep(2000);  // Set Dealy of 2000 ms
    QString fPath = "D:\\CBCT"; // Path for the DICOM Image Folder in "fPath" of QString
    if(fPath == 0||fPath == "")
    {
        QMessageBox::critical(this,"Error","No path found !!");
    }
    bar->setValue(100); // Max Progress Value
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
        //QMessageBox::warning(this,"Error","No Images Found..");
        QMessageBox::critical(this, "Error","No Images Found..");
        return;
    }

// ---------- ********** above code find no. of files in the 3D Image ********** -----------
    qDebug()<<"## Starting Process Image Display ##";
    //vtkSmartPointer<vtkDICOMReader> CBCTReader; //moving AP dicom image reader
    CBCTReader = vtkSmartPointer<vtkDICOMReader>::New();
    QString path1 = "D:\\CBCT";
    CBCTReader = dicomRead(path1);
   //const int *dimension;
   qDebug()<<" *** Image path Read *** ";
    dimension =  CBCTReader->GetOutput()->GetDimensions();
    qDebug()<<"CBCT Dimension[0] :"<<dimension[0];
    qDebug()<<"CBCT Dimension[1] :"<<dimension[1];
    qDebug()<<"CBCT Dimension[2] :"<<dimension[2];

    volSize1 = dimension[0];
    volSize2 = dimension[1];
    volSize3 = dimension[2];
    qDebug()<<volSize1;
    qDebug()<<volSize2;
    qDebug()<<volSize3;
    float x;
    x = volSize1*volSize2*volSize3;
    qDebug()<<"Volume of 3D ImageS: "<<x;
  cbctvolume = new float[ dimension[0]*dimension[1]*dimension[2]];
//    qDebug()<<"Volume of the CBCT:"<<cbctvolume; // same things as "X"
// // // // // // // // // // /// //// // // // // // // /// // // // // /// // // // // //
    cbctslice = new unsigned char[ dimension[0]*dimension[1]];

    qDebug()<<"volume export function call in the main function";
    setVtkVolumeToC(cbctvolume);
    if(cbctvolume!= NULL)
    {
         qDebug()<<"VOLUME PRESENT";

    }
    qDebug()<<"volume export function performed successfully";

    scaleFactor=1024/dimension[0] ;
    double pixPitch=(static_cast<double>(dimension[0])/volSize1)/scaleFactor; /*only 1/scalefactor*/
    pixSpacingCBCT.clear();
    pixSpacingCBCT<<pixPitch;
    pixSpacingCBCT<<pixPitch;
    pixSpacingCBCT<<pixPitch;
    qDebug()<<"Hello Debug 1 ";
    qDebug()<<"Pixel Spacing : "<<pixPitch;
    qDebug()<<"Pixel Spacing : "<<pixPitch;
    qDebug()<<"Pixel Spacing : "<<pixPitch;

 /* ----- ***** Displaying the slices and 3D ***** ----- */

 //ui->stackedWidget_dynamic->setCurrentWidget(ctCbctScreen); // ********
   //   display3D(cbctvolume,dimension,pixPitch);

    qDebug()<<"display3D function call here in the main function";
    this->display3D(cbctvolume,dimension,pixPitch);
    if(cbctvolume!= NULL)
    {
         qDebug()<<"VOLUME PRESENT";

    }
    qDebug()<<"display3D function performed successfully";

 //ctCbctScreen->ui->threeDslider->setValue(ctCbctScreen->ui->threeDslider->maximum()/2);  // ********

    // Steps performed; Read the 3D Image Data through it's path, then read now its need to read volume for that we create another function to read volume
    // and reader should be exported to there as well as the function of volume should be called in the main function by giving cbctvolume
    // input and now also call the display3D function in the main function so that it will call and perform the printing operation in the
    // Widget window

//    /*get scale factor for scaling images into the display dimensions*/
//    axialScene->setpixelPitch(pixPitch);
//    sagitalScene->setpixelPitch(pixPitch);
//    frontalScene->setpixelPitch(pixPitch);

      /* set the dimension to the scaling orientation*/
//    axialScene->setSceneRect(0,0,dimension[0],dimension[1]);
//    frontalScene->setSceneRect(0,0,dimension[0],dimension[2]);
//    sagitalScene->setSceneRect(0,0,dimension[1],dimension[2]);

      /* print the orientation scaling*/
//    qDebug()<<"axialScene pointer"<<axialScene;
//    qDebug()<<"frontalScene pointer"<<frontalScene;
//    qDebug()<<"sagitalScene pointer"<<sagitalScene;

//    bar->setValue(100); // set default bar value

}


// ------------------------ *************************** ------------------
vtkSmartPointer<vtkDICOMReader> MainWindow::dicomRead(QString path)
{
    qDebug()<<"programme in the dicom reader function";

    vtkSmartPointer <vtkDICOMDirectory> dicomdir = vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir -> SetDirectoryName (/*dicomFolder*/path.toStdString().c_str());
    try
    {
     dicomdir ->Update ();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        return 0;
    }
    qDebug()<<"Dicom reader directry updated";
    vtkSmartPointer<vtkDICOMReader> reader1 = vtkSmartPointer<vtkDICOMReader>::New();
    int numSeries=dicomdir->GetNumberOfSeries();
    vtkStringArray *sortedFiles;
    QString rtStructFile;
    qDebug()<<"Number of Series found :"<<numSeries;
    sortedFiles = dicomdir -> GetFileNamesForSeries (numSeries-1);
 for(int i=0;i<sortedFiles->GetNumberOfValues();i++)
 {
  qDebug()<<"Image #--->"<<sortedFiles->GetValue(i);
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
//    vtkSmartPointer<vtkDICOMReader> reader = NULL;  // put it in public in .h file
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

// ------------------------ ******************* ------------------------------

// -------------------- ************************ ----------------------------
void MainWindow::setVtkVolumeToC(float *Vol) // cVol -> changed to Vol
{
    /* Assumes data exists. Exports the vtk image to the c volume and converts the the data to float */
//    vtkSmartPointer<vtkImageReslice> flip = vtkSmartPointer<vtkImageReslice>::New();
//    flip->SetInputConnection(reader->GetOutputPort());
//    flip->SetResliceAxesDirectionCosines( 1,0,0, 0,-1,0, 0,0,-1);//dispanp
//    flip->Update();
    qDebug()<<"##### ***** Programme intered inside the SetVTKVolumeTOc ***** ##### ";
    qDebug()<<" Programme it is the volume exporter funtion";
    vtkSmartPointer<vtkImageExport> exporter =vtkSmartPointer<vtkImageExport>::New();
    exporter->SetInputData(reader->GetOutput());
    qDebug()<<"Test #first";
    exporter->ImageLowerLeftOn();//default
    try{
        exporter->Update();
        qDebug()<<"cbctreconexporter->Update()";
       // v=(short*)exporter->GetPointerToData();//since data is huge get only pointer to memory

    }catch(...){
        return;
    }
     v=(short*)exporter->GetPointerToData();//since data is huge get only pointer to memory
  //   qDebug()<<"v = exporter completed";
  //   qDebug()<<"v = "<<v;
//    for(int i=0;i<dimension[0]*dimension[1]*dimension[2];i++)
    for(int j=0; j<512*512*512; j++)
    {
       // qDebug()<<j;
       // qDebug()<<"Vol----->"<<(i%100);
        Vol[j]=static_cast<float>(v[j]);
      // qDebug()<<"volume :"<<Vol[i];
    }
    qDebug()<<"Volume exporter funtion executed successfully";
}

// ------------------------------------- ********************** ------------------------

void MainWindow::display3D(float* volume,const int *dimension,double pixPitch)
{
    qDebug()<<"##### ***** programme is in side the display3D function ***** #####";
    //QVTKWidget *vtkWidget;
    //vtkWidget = new QVTKWidget;

    // get the parameters from the input class
    // scale vol from float to uchar, assume min = -1000, find max
    //float volMax = 2000.0f;
    /******************************************************** SOURCE ***********************************************************/
    qDebug()<<"#2 source is initialized";
    vtkWidget = new QVTKWidget(this);

    volumeImport = vtkImageImport::New();
    ui->verticalLayout->addWidget(vtkWidget);

    // volume Import
    volumeImport->CopyImportVoidPointer(volume, sizeof(float)*dimension[0]*dimension[1]*dimension[2]);
    qDebug()<<"YY";
    volumeImport->SetWholeExtent(0,dimension[0]-1, 0,dimension[1]-1, 0,dimension[2]-1);
    qDebug()<<"QQ";

    volumeImport->SetDataScalarTypeToFloat();
    volumeImport->SetNumberOfScalarComponents(1);

    volumeImport->SetDataExtentToWholeExtent();
    volumeImport->SetDataSpacing(double(pixPitch), double(pixPitch), double(pixPitch));
    /******************************************************** MAPPER ***********************************************************/
    // 3D GAUSSIAN FILTER
    qDebug()<<"Mapper is initialized";
    vtkImageGaussianSmooth *gaussFilter = vtkImageGaussianSmooth::New();  // for smoothening of the Image
    gaussFilter->SetInputConnection(volumeImport->GetOutputPort());
    gaussFilter->SetRadiusFactors(1.5, 1.5, 1.5);
    gaussFilter->SetStandardDeviations(1.0, 1.0, 1.0);
    gaussFilter->Update();
    qDebug()<<"we are not using GPU int this case";
       // vtkGPUVolumeRayCastMapper *volumeGPUmapper = vtk;
    // Map data on GPU   "Here I Don't have to use the GPU, It is commented here"
    vtkGPUVolumeRayCastMapper *volumeGPUmapper = vtkGPUVolumeRayCastMapper::New();
//       //vtkVolumeRayCastMapper *volumeGPUmapper=vtkVolumeRayCastMapper::New();
   volumeGPUmapper->SetInputConnection(gaussFilter->GetOutputPort());
    /******************************************************** ACTOR ***********************************************************/
    qDebug()<<"Volume is Initialized i.e equivalent to Actor is initialized (as per vtk library)";

    vtkVolume *VTKvolume = vtkVolume::New();

    VTKvolume->SetMapper(volumeGPUmapper);  // Actually I am not using Volume GPU mapper Here
    // RGB and alpha funcions
    qDebug()<<"Mapping created";
    /* ------------------------------------------------------------------------------------------- */
    double skinOnBlueMap[28][5] =
    {
        {-923, 0.987853825092316, 1.0,               1.0,               0.0},
        {-733, 0.987853825092316, 1.0,               1.0,               0.00750770070067319},
        {-531, 0.987853825092316, 1.0,               1.0,               0.0733569149832789},
        {-372, 0.987853825092316, 1.0,               1.0,               0.0},
        {142,  0.0,               0.0,               0.0,               0.0},
        {332,  1.0,               0.0,               0.0,               0.132020258336102},
        {534,  1.0,               0.999206542968750, 0.0,               0.317781232734010},
        {679,  1.0,               1.0,               1.0,               0.940655276334784}
    };
    /* --------------------------------------------------------------------------------------------- */

    // Apply colormap
    alphaChannelFunc = vtkPiecewiseFunction::New();
    colorFunc = vtkColorTransferFunction::New();
    for(int i = 0; i < sizeof(skinOnBlueMap)/(5*sizeof(double)); i++)
    {
        colorFunc->AddRGBPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][1], skinOnBlueMap[i][2], skinOnBlueMap[i][3]);
        alphaChannelFunc->AddPoint(skinOnBlueMap[i][0], skinOnBlueMap[i][4]);
    }

    /* ----------------------------------------------------------------------------------------------- */

    // PropertyEditor
    vtkVolumeProperty   *volumeProperty = vtkVolumeProperty::New();
    volumeProperty->SetColor(colorFunc);
    volumeProperty->SetScalarOpacity(alphaChannelFunc);
    VTKvolume->SetProperty(volumeProperty);

    /* ------------------------------------------------------------------------------------------------ */

    /******************************************************** RENDERER ***********************************************************/
    qDebug()<<" ##### ***** programme is in side the Renderer section of display3D Function ******* #######";

    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();

    camera->Pitch(180);
    camera->Roll(180);
    camera->Yaw(180);

    qDebug()<<"** -- rendering crated -- **";
    ren = vtkRenderer::New();
    ren->AddVolume(VTKvolume);
    ren->SetBackground(0, 0, 0);
    /**************************************************** RENDERER WINDOW *******************************************************/
    qDebug()<<" Renderer Window operation in the display3D Function";
    vtkWidget->GetRenderWindow()->AddRenderer(ren);

    ren->SetActiveCamera(camera);
    qDebug()<<"Rendering Initiated";
    ren->ResetCamera();
    qDebug()<<" Renderer Window operation in the display3D Function";

//    alphaChannelFunc->RemoveAllPoints();
//    alphaChannelFunc->AddPoint(-1000, 0.0);
//    alphaChannelFunc->AddPoint(-500, 0.0);
//    alphaChannelFunc->AddPoint(1500, double(256)/500.0);

    vtkWidget->GetRenderWindow()->Render();
    vtkWidget->update();
    qDebug()<<"Rendering applied successfully";
    // Cleaning.
//    qDebug()<<" Clear process of pointer started";
//    gaussFilter->Delete();
//    // volumeGPUmapper->Delete();
//    VTKvolume->Delete();
//    volumeProperty->Delete();
//    volumeImport->Delete();
    colorFunc->Delete();
//    alphaChannelFunc->Delete();
//    ren->Delete();
//    qDebug()<<"#11 display3D function Executed";

    ui->axialSlider->setValue(256);
    ui->sagitalSlider->setValue(256);
    ui->frontalSlider->setValue(256);

    on_pushButton_3_clicked();  // for Axial
    on_pushButton_2_clicked(); // for Sagital
    on_pushButton_4_clicked(); // for Sagital
}

void MainWindow::on_pushButton_2_clicked()
{
  // Sagital Slice, GraphicsView

    unsigned char *sagit = new unsigned char[512*512];
    unsigned char *sagImage = new unsigned char[dimension[1]*dimension[2]];
    int index;

//    for(int i = 0; i < dimension[2]; i++)  // commented for check (it is correct)
//    {
//        for(int j = 0; j < dimension[1]; j++)
//        {
//            index = ui->sagitalSlider->value()+j*dimension[0]+i*dimension[0]*dimension[1];
//            //                index = value + (int)ctDIM2 * iCol + (int)ctDIM1 * (int)ctDIM2 * iRow;

//            if(cbctvolume[index]<-1000)
//                sagit[j+i*dimension[1]] =0;

//            else if(cbctvolume[index]>1000)
//                sagit[j+i*dimension[1]] = 255;

//            else
//                sagit[j+i*dimension[1]] = ((cbctvolume[index]-(-1000))*(255.0-0.0))/(1000-(-1000));
//        }
//    }
   /*  -------------------   */
    for(int h = 0; h < dimension[2]; ++h)//z
    {
    for(int n = 0; n < dimension[1]; ++n) //0 1  y
    {
//        for(int r = 0; r < dimension[0]; ++r)//0 1 x
//        {
            index = /*r*//*256*/ ui->sagitalSlider->value()+n*dimension[1]+h*dimension[0]*dimension[2];
//        }
            if(cbctvolume[index]<-1000)
            sagit[n+h*dimension[1]] =0;

            else if(cbctvolume[index]>1000)
            sagit[n+h*dimension[1]] = 255;

            else
           sagit[n+h*dimension[1]] = ((cbctvolume[index]-(-1000))*(255.0-0.0))/(1000-(-1000));
    }
    }
/*   */

    //  //  //  //  //  //  //
//    for(int k = 0; k < dimension[2]; k++)  // added for test
//    {
//        for(int l = 0; l < dimension[1]; l++)
//        {
//            index = 256+dimension[1]+dimension[2];

//            if(cbctvolume[index] < -1000)
//                sagit[l+k+256] = 0;
//            else if(cbctvolume[index]>1000)
//                sagit[l+k+256] = 255;
//            else
//                sagit[l+k+256] =  ((cbctvolume[index]-(-1000))*(255.0-0.0))/(1000-(-1000));
//        }
//    }
   //  //  //  //  //  //  //

    QImage *Image2 = new QImage(sagit, dimension[1], dimension[2], QImage::Format_Indexed8);
    QGraphicsPixmapItem *Image3= new QGraphicsPixmapItem(QPixmap::fromImage(*Image2));
    sscene->addItem(Image3);
    sscene->setSceneRect(0,0,512,512);
    ui->graphicsView->setScene(sscene);
    ui->graphicsView->fitInView(0,0,dimension[1], dimension[2]);
    qDebug()<<"Program Exicuted Successfully"<<endl;
    qDebug()<<"Sagital Image";

}


void MainWindow::on_pushButton_3_clicked()
{
    ctDIM1=512;
    ctDIM2=512;
    ctDIM3=512;

    axialSliderValue=ui->axialSlider->value();
// Axial Slice, GraphicsView
    unsigned char *axial = new unsigned char[512*512];
    unsigned char *Image = new unsigned char[dimension[0]*dimension[1]];
    int index;

    for(int i=0;i<dimension[1];i++)
    {
        for(int j=0;j<dimension[0];j++)
        {
            index=j+i*dimension[0]+(ui->axialSlider->value())*dimension[0]*dimension[1];
            if(cbctvolume[index]<-1000)
                axial[j+i*dimension[0]]=0;
            else if(cbctvolume[index]>1000)
                    axial[j+i*dimension[0]]=255;
            else
             axial[j+i*dimension[0]]=((cbctvolume[index]-(-1000))*(255.0-0.0))/(1000-(-1000));
        }
    }
//    for(int i = 0; i < dimension[0]*dimension[1]; ++i)
//    {
//        index = dimension[0]+
////        int m;
////        m = dimension[2].at(256);
////        int index;
////        for(int index == dimension[2])
//        Image[i] = axial[i]/*[m]*/*255.0/65535.0;
//    }
    QImage *Image1 = new QImage(axial, dimension[0], dimension[1], QImage::Format_Indexed8);
    QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));
    ascene->addItem(Image2);
    ascene->setSceneRect(0,0,512,512);
    ui->graphicsView_2->setScene(ascene);
    ui->graphicsView_2->fitInView(Image2);
    qDebug()<<"Program Exicuted Successfully"<<endl;
    qDebug()<<"Axial Image";



//   // float *axvol;
  // axial  = getAxialSlice( cbctvolume,511,1);
////getAxialSlice(float* vol,int value,int type)
////QImage axImg(axial, );
//// QImage axImg = new QImage(axial,512, 512, QImage.Format_Indexed8);
// const unsigned int Dimension = 2;
// typedef float PixelType;
// typedef itk::Image< PixelType, 2 > OutputImageType;
// typedef itk::ImageFileReader <OutputImageType > ReaderType;
// ReaderType::Pointer axisImageread = ReaderType::New();
//// typedef itk::ImageFileReader< axisImageread > ReaderType;
// //ReaderType::Pointer axisImageread = ReaderType::New();
// typedef itk::GDCMImageIO ImageIOType;
// ImageIOType::Pointer gdcmImageIO = ImageIOType::New();
// axisImageread->SetImageIO( gdcmImageIO );
// //axisImageread->GetInput(path1);
// //axisImageread->GetOutput(path1);
//  //Fixedreader->SetFileName("D:/3D Image/CT DRR/Image_0.dcm");
//  axisImageread->SetFileName(path1.toStdString().c_str());
// try
// {
//     axisImageread->Update();
// }
// catch (itk::ExceptionObject &e)
// {
//     std::cerr << " Exception in File reader " << std::endl;
//     std::cerr << e << std::endl;
// }

// typedef itk::ResampleImageFilter< OutputImageType, OutputImageType > ResampleFilterType;
// ResampleFilterType::Pointer resampler = ResampleFilterType::New();
// resampler->SetInput(axisImageread->GetOutput());
// try
// {
//     resampler->Update();
// }
// catch (itk::ExceptionObject &e)
// {
//     std::cerr << " Exception in File reader " << std::endl;
//     std::cerr << e << std::endl;
// }

// qDebug()<<resampler;
// unsigned char *Image = new unsigned char[512*512]; /*[size[0]*size[1]];*/
// for(int i = 0; i < /*size[0]*size[1]*/ 512*512; ++i)
// {
//     Image[i] = resampler->GetOutput()->GetBufferPointer()[i]*255.0/65535.0;
// }
// QImage *Image1 = new QImage(Image, /*size[0], size[1]*/ 512,512, QImage::Format_Indexed8);
// QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));
// scene->addItem(Image2);
// scene->setSceneRect(0,0,3072,3072);
// ui->graphicsView->setScene(scene);
// ui->graphicsView->fitInView(Image2);

//qDebug()<<"Axial Image slices are displayed"<<endl;

}

void MainWindow::on_pushButton_4_clicked()
{
    // Frontal Slice, GraphicsView
//    unsigned char *front;
//    float *vol;
//    front = getFrontalSlice(vol,255, 1);

//    unsigned char *frontImg = new unsigned char[dimension[0]*dimension[2];


    // **** // ****
    unsigned char *frontImg = new unsigned char[512*512];
    int index;
    for(int i = 0; i < dimension[2]; ++i)
    {
        for(int j = 0; j < dimension[0]; ++j)
        {
            index = j+ui->frontalSlider->value()*dimension[2] +i*dimension[0]*dimension[2];
          // index = ui->sagitalSlider->value()+j*dimension[0]+i*dimension[0]*dimension[1];
         // index=j+i*dimension[0]+(ui->axialSlider->value())*dimension[0]*dimension[1];
            if(cbctvolume[index]<-1000)
                frontImg[j+i*dimension[2]]=0;
            else if(cbctvolume[index]>1000)
                    frontImg[j+i*dimension[2]]=255;
            else

             frontImg[j+i*dimension[2]]=((cbctvolume[index]-(-1000))*(255.0-0.0))/(1000-(-1000));

        }
    }

    QImage *Image4 = new QImage(frontImg, dimension[0], dimension[1], QImage::Format_Indexed8);
    QGraphicsPixmapItem *Image5= new QGraphicsPixmapItem(QPixmap::fromImage(*Image4));
    fscene->addItem(Image5);
    fscene->setSceneRect(0,0,512,512);
    ui->graphicsView_3->setScene(fscene);
    ui->graphicsView_3->fitInView(Image5);
    qDebug()<<"Program Exicuted Successfully"<<endl;
    qDebug()<<"Frontal Image";
  // **** // ****

}


//unsigned char * MainWindow::getAxialSlice(float* vol,int value,int type)
//{
//    // Get Axial Slice Function
//    int ctDIM1 = 512;
//    int ctDIM2 = 512;
//    int ctDIM3 = 512;
//    type = 1;
//    unsigned char *axial = new unsigned char[1536*1536];

////
////    CBCTReader = vtkSmartPointer<vtkDICOMReader>::New();
////    QString path1 = "D:\\CBCT";
////    CBCTReader = dicomRead(path1);

////    dimension =  CBCTReader->GetOutput()->GetDimensions();
////    qDebug()<<"CBCT Dimension[0] :"<<dimension[0];
////    qDebug()<<"CBCT Dimension[1] :"<<dimension[1];
////    qDebug()<<"CBCT Dimension[2] :"<<dimension[2];

////    volSize1 = dimension[0];
////    volSize2 = dimension[1];
////    volSize3 = dimension[2];
////    qDebug()<<volSize1;
////    qDebug()<<volSize2;
////    qDebug()<<volSize3;

////    cbctslice = new unsigned char[ dimension[0]*dimension[1]];
////    cbctvolume = new float[dimension[0]*dimension[1]*dimension[2]];

////    unsigned char *Image = new unsigned char[dimension[0]*dimension[1]];
////    for(int i = 0; i < dimension[0]*dimension[1]; ++i)
////    {
////        int m = 256;
////        Image[i] = axial[i][m]*255.0/65535.0;
////    }
////    QImage *Image1 = new QImage(Image, dimension[0], dimension[1], QImage::Format_Indexed8);
////    QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));
////    scene->addItem(Image2);
////    scene->setSceneRect(0,0,3072,3072);
////    ui->graphicsView->setScene(scene);
////    ui->graphicsView->fitInView(Image2);
////    qDebug()<<"Program Exicuted Successfully"<<endl;
////    qDebug()<<"Axial Image";


////    ////    if(axialSlice != NULL)
////    ////    {
////    //        delete[] axialSlice;
////    ////    }
////    //    axialSlice = new unsigned char[512*512];

////    qDebug()<<"checking value1 "<<value;
//  //  value = ctDIM3-1;

////    qDebug()<<"checking value "<<value;

////    if (type==1)
////    {
////        for(int iPixel = 0; iPixel < (int)ctDIM2; iPixel++){
////        for(int jPixel = 0;jPixel < (int)ctDIM1; jPixel++){
////            // clip values < LT to LT, values > UT to UT
////            if(vol[ctDIM1-1-jPixel+iPixel*(int)ctDIM1+value*(int)ctDIM1*(int)ctDIM2] <= lowerThreshold)
////                axialSliceCT[jPixel+iPixel*(int)ctDIM1] = 0;
////            else if(vol[ctDIM1-1-jPixel+iPixel*(int)ctDIM1+value*(int)ctDIM1*(int)ctDIM2] >= upperThreshold)
////                axialSliceCT[jPixel+iPixel*(int)ctDIM1] = 255;
////            // scale the image such that LT = 0 and UT = 255
////            else
////                axialSliceCT[jPixel+iPixel*(int)ctDIM1] = (unsigned char)(((vol[ctDIM1-1-jPixel+iPixel*ctDIM1+value*(int)ctDIM1*(int)ctDIM2]
////                                                        - lowerThreshold) * 255.0f) /(upperThreshold - lowerThreshold));
////        }
////        }
////        return axialSliceCT;
////        //        for(int jPixel = 0; jPixel < vDIM; jPixel++){
////        //            for(int iPixel=0;iPixel< vDIM;iPixel++)
////        //            {
////        //            // clip values < LT to LT, values > UT to UT
////        //            if(vol[(value) * vDIM * vDIM + jPixel*vDIM+iPixel] <= lowerThreshold)
////        //                axialSliceCT[jPixel*vDIM+iPixel] = 0;
////        //            else if(vol[(value) * vDIM * vDIM + jPixel*vDIM+iPixel] >= upperThreshold)
////        //                axialSliceCT[jPixel*vDIM+iPixel] = 255;
////        //            // scale the image such that LT = 0 and UT = 255
////        //            else
////        //                axialSliceCT[jPixel*vDIM+iPixel] = (unsigned char)(((vol[(value) * vDIM * vDIM +jPixel*vDIM+ (vDIM-1-iPixel)]
////        //                                                        - lowerThreshold) * 255.0f) /(upperThreshold - lowerThreshold));

////        //            }
////        //        }
////        //        return axialSliceCT;
////    }
////    else
////    if(type == 1)
////    {
////        qDebug()<<"Checked type = 1, so we are in CBCT";

////        for(int iPixel = 0; iPixel < (int)ctDIM2; iPixel++){
////        for(int jPixel = 0;jPixel < (int)ctDIM1; jPixel++)
////        {
////            // clip values < LT to LT, values > UT to UT
////            if(vol[ctDIM1-1-jPixel+iPixel*(int)ctDIM1+value*(int)ctDIM1*(int)ctDIM2] <= lowerThreshold)
////                axialSliceCBCT[jPixel+iPixel*(int)ctDIM1] = 0;
////            else if(vol[ctDIM1-1-jPixel+iPixel*(int)ctDIM1+value*(int)ctDIM1*(int)ctDIM2] >= upperThreshold)
////                axialSliceCBCT[jPixel+iPixel*(int)ctDIM1] = 255;
////            // scale the image such that LT = 0 and UT = 255
////            else{

////                axialSliceCBCT[jPixel+iPixel*(int)ctDIM1] = (unsigned char)(((vol[ctDIM1-1-jPixel+iPixel*(int)ctDIM1+value*(int)ctDIM1*(int)ctDIM2]
////                                                          - lowerThreshold) * 255.0f) /(upperThreshold - lowerThreshold));

////            }

////        }
////        }
////        return axialSliceCBCT;

////    }

//}

unsigned char * MainWindow::getFrontalSlice(float* vol,int value,int type)
{
    // Frontal Slice
    ctDIM1=512;
    ctDIM2=512;
    ctDIM3=512;
    type =1;

    value = ctDIM3-1;
//    if (type==1)
//    {
//        int index = 0;
//        //    if(slice != NULL)
//        //        delete[] slice;
//        //    slice = new unsigned char[512*512];
//        for(int iRow = 0; iRow < (int)ctDIM3; iRow++)
//            for(int iCol = 0; iCol < (int)ctDIM1; iCol++){
//                index = value * (int)ctDIM1 + (int)ctDIM1 * (int)ctDIM2 * iRow + iCol;
//               // index = (/*vDIM-*/value/*-1*/) * vDIM + vDIM * vDIM * (/*vDIM-*/iRow/*-1*/) + vDIM-1-iCol;
//                // clip values < LT to LT, values > UT to UT
//                if(vol[index] <= lowerThreshold)
//                    frontalSliceCT[iRow * (int)ctDIM1 + iCol] = 0;
//                else if(vol[index] >= upperThreshold)
//                    frontalSliceCT[iRow *(int)ctDIM1 + iCol] = 255;
//                // scale the image such that LT = 0 and UT = 255
//                else
//                    frontalSliceCT[iRow * (int)ctDIM1 + iCol] = (unsigned char)(((vol[index] - lowerThreshold) * 255.0f) /
//                                                                         (upperThreshold - lowerThreshold));
//            }

//        return frontalSliceCT;
//    }
//    else
    if(type == 1)
    {
        qDebug()<<"Checked Type = 1, means we are in CBCT";
        int index = 0;
        //    if(slice != NULL)
        //        delete[] slice;
        //    slice = new unsigned char[512*512];
        for(int iRow = 0; iRow < (int)ctDIM3; iRow++)
            for(int iCol = 0; iCol < (int)ctDIM1; iCol++){
                index = value * (int)ctDIM1 + (int)ctDIM1 * (int)ctDIM2 * iRow + iCol;

               // index = (/*vDIM-*/value/*-1*/) * vDIM + vDIM * vDIM * (/*vDIM-*/iRow/*-1*/) + vDIM-1-iCol;
                // clip values < LT to LT, values > UT to UT
                if(vol[index] <= lowerThreshold)
                    frontalSliceCBCT[iRow * (int)ctDIM1 + iCol] = 0;
                else if(vol[index] >= upperThreshold)
                    frontalSliceCBCT[iRow * (int)ctDIM1 + iCol] = 255;
                // scale the image such that LT = 0 and UT = 255
                else
                    frontalSliceCBCT[iRow * (int)ctDIM1 + iCol] = (unsigned char)(((vol[index] - lowerThreshold) * 255.0f) /
                                                                           (upperThreshold - lowerThreshold));
            }

        return frontalSliceCBCT;
    }
}

unsigned char * MainWindow::getSagitalSlice(float *vol,int value,int type)
{
    ctDIM1=512;
    ctDIM2=512;
    ctDIM3=512;
    // Get Sagital Slice Function
    type = 1;
   value = ctDIM3-1;
    qDebug()<<"value: "<<value<<endl<<"type: "<<type<<endl;
//    qDebug()<<"value"<<value;
//    qDebug()<<"VALUE VALUE VALUE VALUE VALUE VALUE VALUE VALUE VALUE VALUE VLAUE VALUE VALUE VALUE VALUE";
//    if (type==1)
//    {
//        int index = 0;
//        //    if(slice != NULL)
//        //        delete[] slice;
//        //    slice = new unsigned char[512*512];


//        for(int iRow = 0; iRow < (int)ctDIM3; iRow++)
//            for(int iCol = 0; iCol < (int)ctDIM2; iCol++){

//                index = value + (int)ctDIM2 * iCol + (int)ctDIM1 * (int)ctDIM2 * iRow;

//                //index = (/*vDIM-*/value/*-1*/) + vDIM * iCol + vDIM * vDIM * (/*vDIM-*/iRow/*-1*/);

//                //    qDebug()<<"index"<<    index;
//                //            slice[iRow * 512 + iCol] = (unsigned char)(volume[index]);
//                // clip values < LT to LT, values > UT to UT
//                if(vol[index] <= lowerThreshold)
//                    sagitalSliceCT[iRow * (int)ctDIM2  +iCol ] = 0;
//                //                    sagitalSliceCT[iRow  +iCol* vDIM ] = 0;
//                else if(vol[index] >= upperThreshold)
//                    sagitalSliceCT[iRow * (int)ctDIM2  +iCol ] = 255;
//                //                    sagitalSliceCT[iRow  +iCol* vDIM ] = 255;
//                // scale the image such that LT = 0 and UT = 255
//                else
//                    sagitalSliceCT[iRow * (int)ctDIM2  +iCol ] = (unsigned char)(((vol[index] - lowerThreshold) * 255) /
//                                                                          (upperThreshold - lowerThreshold));
//                //                    sagitalSliceCT[iRow  +iCol* vDIM ] = (unsigned char)(((vol[index] - lowerThreshold) * 255) /
//                //                                                                         (upperThreshold - lowerThreshold));
//            }

//        return sagitalSliceCT;
//    }
//    else

    if(type == 1)
    {
        qDebug()<<"Checked type condition = 1 means CBCT";
        int index = 0;
        //    if(slice != NULL)
        //        delete[] slice;
        //    slice = new unsigned char[vDIM*vDIM];

        for(int iRow = 0; iRow < (int)ctDIM3; iRow++)
            for(int iCol = 0; iCol < (int)ctDIM2; iCol++){

                index = value + (int)ctDIM2 * iCol + (int)ctDIM1 * (int)ctDIM2 * iRow;

                //index = (/*vDIM-*/value/*-1*/) + vDIM * iCol + vDIM * vDIM * (/*vDIM-*/iRow/*-1*/);

                //            slice[iRow * vDIM + iCol] = (unsigned char)(volume[index]);
                // clip values < LT to LT, values > UT to UT
                if(vol[index] <= lowerThreshold)
                    sagitalSliceCBCT[iRow * (int)ctDIM2 + iCol ] = 0;
                //                    sagitalSliceCBCT[iRow + iCol* vDIM ] = 0;
                else if(vol[index] >= upperThreshold)
                    sagitalSliceCBCT[iRow * (int)ctDIM2  +iCol ] = 255;
                //                    sagitalSliceCBCT[iRow  +iCol* vDIM ] = 255;
                // scale the image such that LT = 0 and UT = 255
                else
                    sagitalSliceCBCT[iRow * (int)ctDIM2  +iCol ] = (unsigned char)(((vol[index] - lowerThreshold) * 255) /
                                                                            (upperThreshold - lowerThreshold));
                //                    sagitalSliceCBCT[iRow  +iCol* vDIM ] = (unsigned char)(((vol[index] - lowerThreshold) * 255) /
                //                                                                           (upperThreshold - lowerThreshold));
            }
        qDebug()<<"index11"<<    index;

        return sagitalSliceCBCT;
    }

}

void MainWindow::on_Draw_clicked()
{
    ascene->setScene(ascene,fscene,sscene,customescene::Mode::DrawEllipse);

}
