#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "gdcmGlobal.h"
#include "gdcmDicts.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    scene->setSceneRect(0,0,width,height);
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
        std::cout<<str_Jaw<<endl;
        return str_Jaw;
    }
}
void MainWindow::on_LOAD_clicked()
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

    // Access the ReferencedRTPlanSequence (300C,0002)
    gdcm::Tag referencedRTPlanSequenceTag(0x300C, 0x0002);
    if (gdcmDS.FindDataElement(referencedRTPlanSequenceTag))
    {
        const gdcm::DataElement &referencedRTPlanSequenceElement = gdcmDS.GetDataElement(referencedRTPlanSequenceTag);
        // Ensure the element is a sequence (VR = SQ)
        if (referencedRTPlanSequenceElement.GetVR() == gdcm::VR::SQ)
        {
            const gdcm::SequenceOfItems *seq = referencedRTPlanSequenceElement.GetValueAsSQ();
            if (seq)
            {
                for (unsigned int i = 1; i <= seq->GetNumberOfItems(); ++i)
                {
                    const gdcm::Item &item = seq->GetItem(i);
                    const gdcm::DataSet &itemDataSet = item.GetNestedDataSet();

                    // Access the Referenced SOP Class UID (0008,1150)
                    gdcm::Tag referencedSOPClassUIDTag(0x0008, 0x1150);
                    if (itemDataSet.FindDataElement(referencedSOPClassUIDTag))
                    {
                        const gdcm::DataElement &referencedSOPClassUIDElement = itemDataSet.GetDataElement(referencedSOPClassUIDTag);
                        gdcm::Attribute<0x0008, 0x1150> referencedSOPClassUIDAttr;
                        referencedSOPClassUIDAttr.SetFromDataElement(referencedSOPClassUIDElement);
                        QString Val1=referencedSOPClassUIDAttr.GetValue();
                        qDebug()  << "Referenced SOP Class UID:" << Val1;
                        std::cout << "Referenced SOP Class UID:  " << referencedSOPClassUIDAttr.GetValue() << std::endl;
                    }

                    // Access the Referenced SOP Instance UID (0008,1155)
                    gdcm::Tag referencedSOPInstanceUIDTag(0x0008, 0x1155);
                    if (itemDataSet.FindDataElement(referencedSOPInstanceUIDTag))
                    {
                        const gdcm::DataElement &referencedSOPInstanceUIDElement = itemDataSet.GetDataElement(referencedSOPInstanceUIDTag);
                        gdcm::Attribute<0x0008, 0x1155> referencedSOPInstanceUIDAttr;
                        referencedSOPInstanceUIDAttr.SetFromDataElement(referencedSOPInstanceUIDElement);
                        QString Val1=referencedSOPInstanceUIDAttr.GetValue();
                        qDebug()  << "Referenced SOP Instance UID:" << Val1;
                        std::cout << "Referenced SOP Instance UID:  " << referencedSOPInstanceUIDAttr.GetValue() << std::endl;
                    }
                }
            }
        }
        else
        {
           std::cerr << "Referenced RT Plan Sequence Element VR not found." << std::endl;
        }
    }
    else
    {
        std::cerr << "Referenced RT Plan Sequence (300C,0002) not found." << std::endl;
    }

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
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(/*scene->itemsBoundingRect()*/item,Qt::KeepAspectRatio);
    scene->addItem(item);
}
