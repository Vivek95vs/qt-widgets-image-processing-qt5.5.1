#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "gdcmGlobal.h"
#include "gdcmDicts.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::ReadOfflineDXPrivateTagDetails(gdcm::Tag tg, gdcm::DataSet ds)
{
    if( !ds.FindDataElement( tg) ) {
        qDebug()<<"No tag found ";
        return "0.0";
    }
    else{
        std::cout<<ds.GetDataElement(tg)<<std::endl;
        /*const*/ gdcm::DataElement/*&*/ jawInfo = ds.GetDataElement( tg );
        if ( jawInfo.IsEmpty() ) {
            qDebug()<<"No tag values found";
        }

        const char *de_Jaw = jawInfo.GetByteValue()->GetPointer();
        const size_t len_de_Jaw = jawInfo.GetByteValue()->GetLength();

        std::string str_Jaw = std::string( de_Jaw, len_de_Jaw );
        std::cout<<str_Jaw<<std::endl;
        return str_Jaw;
    }
}

void MainWindow::on_pushButton_clicked()
{
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Test1/*.dcm",QDir::currentPath());
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

    gdcm::ImageReader gdcmReader2;
    gdcmReader2.SetFileName(fileName.toStdString().c_str());
    if( !gdcmReader2.Read() )
    {
        std::cerr << "gdcm read error " << std::endl;
        return ;
    }
    gdcm::File &gdcmFile = gdcmReader2.GetFile();
    gdcm::DataSet &gdcmDS = gdcmFile.GetDataSet();

    QString Rows=Rows1.c_str();
    QString Cols=Cols1.c_str();
    qDebug()<<Rows;
    qDebug()<<Cols;

    int height = Rows.toInt();
    int width = Cols.toInt();

    std::string TableHorizan;
    itk::ExposeMetaData(dict,"0019|0019",TableHorizan);
    QString H=  TableHorizan.c_str();
    if(H.isEmpty() || H.isNull())
        TableHorizan="0.0";


    qDebug()<<"Horizon value"<<H;

    std::string Tablevericle;

    itk::ExposeMetaData(dict,"0019|0021",Tablevericle);
    QString V=  Tablevericle.c_str();
    if(V.isEmpty() || V.isNull())
        Tablevericle="0.0";

     qDebug()<<"Vertical value"<<V;

    std::string Tablelateral;
    itk::ExposeMetaData(dict,"0019|0020",Tablelateral);
    QString L=  Tablelateral.c_str();
    if(L.isEmpty() || L.isNull())
        Tablelateral="0.0";

     qDebug()<<"Lateral value"<<L;

    std::string colTheta;
    double ColliThetaPresent;
    const gdcm::Tag collRot(0x0019,0x14);
    colTheta=ReadOfflineDXPrivateTagDetails(collRot,gdcmDS);
    if(colTheta=="0.0")
        ColliThetaPresent=0.0;
    else
        ColliThetaPresent=std::stof(colTheta);
    qDebug()<<"ColliThetaPresent ::"<<ColliThetaPresent;

    qDebug()<<"Collitheta"<<ColliThetaPresent;

    image = reader->GetOutput();

    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<pixelBuffer[0];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/65535.0;
    }
    qDebug()<<dispImg[0];

    q_image = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    scene= new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(/*scene->itemsBoundingRect()*/item,Qt::KeepAspectRatio);
    scene->addItem(item);
}

