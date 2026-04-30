#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"


QList<QList<QList<double>>>fpregion;
QList<QList<double>>fpcontour;
QList<double>fppoint;
QList<QList<double>>ROIColor;
QList<QList<QList<QList<double>>>>ROIPoints;
QStringList ROIName;
QList<int>ROINumber;
QList<QList<QList<double>>>pregion;
QList<QList<double>>pcontour;
QList<double>ppoint;

typedef itk::Image< uint8_t, 3 >   ImageType;
typedef itk::Image< uint8_t, 2 >   ImageSliceType;
typedef itk::PolygonSpatialObject<2> PolygonType;
typedef itk::GroupSpatialObject<2> GroupType;
typedef itk::SpatialObjectToImageFilter<GroupType, ImageSliceType> SpatialObjectToImageFilterType;
typedef itk::NiftiImageIO ImgIOType;
typedef itk::Point< double, 3 > PointType;
PointType point;
typedef itk::SpatialObjectPoint<2> PolygonPointType;
PolygonPointType p;
ImageType::Pointer image;
PolygonType::PointListType pointList ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

//    QStringList ctFileNames = QFileDialog::getOpenFileNames(this, "Select CT Images", "", "DICOM Files (*.dcm)");
//    QString rtStructFileName = QFileDialog::getOpenFileName(this, "Select RT Structure", "", "DICOM Files (*.dcm)");

    QString rtStructFileName ="D://RTstructRead//RTSTRUCT_CT//Rangamma//RS1.2.752.243.1.1.20240223112625743.3000.47253.dcm";
    qDebug()<<"RTStructure"<<rtStructFileName;

    if (/*!ctFileNames.isEmpty() &&*/ !rtStructFileName.isEmpty()) {
//        loadCTImages(ctFileNames);
        loadRTStructure(rtStructFileName);
        displayImagesWithContours();
    }
}


void MainWindow::loadCTImages(const QStringList &fileNames) {
    using ImageType = itk::Image<uint8_t, 3>;
    using ReaderType = itk::ImageSeriesReader<ImageType>;
    using ImageIOType = itk::GDCMImageIO;

    ReaderType::Pointer reader = ReaderType::New();
    ImageIOType::Pointer dicomIO = ImageIOType::New();
    reader->SetImageIO(dicomIO);

    std::vector<std::string> fileNamesStd;
    for (const QString &fileName : fileNames) {
        fileNamesStd.push_back(fileName.toStdString());
    }
    reader->SetFileNames(fileNamesStd);

    try {
        reader->Update();
    } catch (itk::ExceptionObject &ex) {
        std::cerr << ex << std::endl;
        return;
    }

    image = reader->GetOutput();
}

void MainWindow::loadRTStructure(const QString &fileName) {
    gdcm::Reader RTreader;
    RTreader.SetFileName(fileName.toLatin1().data());
    if (!RTreader.Read()) {
        std::cerr << "Problem reading RTSTRUCT file" << std::endl;
        return;
    }

    const gdcm::DataSet &ds = RTreader.GetFile().GetDataSet();
    gdcm::Tag troicsq(0x3006, 0x0039);
    if (!ds.FindDataElement(troicsq)) {
        std::cerr << "Problem locating 0x3006,0x0039 - Is this a valid RT Struct file?" << std::endl;
        return;
    }
    const gdcm::DataElement &roicsq = ds.GetDataElement(troicsq);
    gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = roicsq.GetValueAsSQ();
    if (!sqi || !sqi->GetNumberOfItems()) {
        return;
    }

    for (unsigned int pd = 0; pd < sqi->GetNumberOfItems(); ++pd) {
        QList<QList<QList<double>>> p2;
        const gdcm::Item &item = sqi->GetItem(pd + 1);
        const gdcm::DataSet &nestedds = item.GetNestedDataSet();

        gdcm::Tag tcsq(0x3006, 0x0040);
        if (!nestedds.FindDataElement(tcsq)) {
            continue;
        }
        const gdcm::DataElement &csq = nestedds.GetDataElement(tcsq);
        gdcm::SmartPointer<gdcm::SequenceOfItems> sqi2 = csq.GetValueAsSQ();
        if (!sqi2 || !sqi2->GetNumberOfItems()) {
            std::cout << "Did not find sqi2 or no. items == 0, continuing..." << std::endl;
            continue;
        }

        unsigned int nitems = sqi2->GetNumberOfItems();
        gdcm::Tag tstructureName(0x3006, 0x0026);
        const gdcm::DataElement &structureNameElement = nestedds.GetDataElement(tstructureName);
        std::string str_currentOrgan(structureNameElement.GetByteValue()->GetPointer(), structureNameElement.GetByteValue()->GetLength());
        ROIName << QString::fromStdString(str_currentOrgan);

        qDebug() << "Number of contour items" << nitems;

        for (unsigned int i = 0; i < nitems; ++i) {
            QList<QList<double>> p1;
            const gdcm::Item &item2 = sqi2->GetItem(i + 1);
            const gdcm::DataSet &nestedds2 = item2.GetNestedDataSet();

            gdcm::Tag tcontourdata(0x3006, 0x0050);
            const gdcm::DataElement &contourdata = nestedds2.GetDataElement(tcontourdata);

            gdcm::Attribute<0x3006, 0x0050> at;
            at.SetFromDataElement(contourdata);
            const double *pts = at.GetValues();
            unsigned int npts = at.GetNumberOfValues() / 3;

            for (unsigned int j = 0; j < npts * 3; j += 3) {
                QList<double> po;
                itk::Point<double, 3> point;
                point[0] = pts[j + 0];
                point[1] = pts[j + 1];
                point[2] = pts[j + 2];

                itk::Index<3> pixelIndex;
                if (!image->TransformPhysicalPointToIndex(point, pixelIndex)) {
                    std::cerr << "Point outside image boundary" << std::endl;
                    continue;
                }

                po.append(pixelIndex[0]);
                po.append(pixelIndex[1]);
                po.append(pixelIndex[2]);
                p1.append(po);
            }
            p2.append(p1);
        }
        ROIPoints.append(p2);
    }
}

void MainWindow::displayImagesWithContours() {
    using ImageSliceType = itk::Image<uint8_t, 2>;
    using FilterType = itk::ExtractImageFilter<itk::Image<uint8_t, 3>, ImageSliceType>;

    ImageType::RegionType inputRegion = image->GetLargestPossibleRegion();
    ImageType::SizeType size = inputRegion.GetSize();
    ImageType::IndexType start = inputRegion.GetIndex();

    for (size[2] = 0; size[2] < inputRegion.GetSize()[2]; ++size[2]) {
        start[2] = size[2];
        ImageType::RegionType desiredRegion;
        desiredRegion.SetSize(size);
        desiredRegion.SetIndex(start);

        FilterType::Pointer filter = FilterType::New();
        filter->SetExtractionRegion(desiredRegion);
        filter->SetInput(image);
        filter->SetDirectionCollapseToIdentity();
        filter->Update();

//        ImageSliceType::Pointer slice = filter->GetOutput();
//        QImage qImage(slice->GetBufferPointer(), slice->GetLargestPossibleRegion().GetSize()[0], slice->GetLargestPossibleRegion().GetSize()[1], QImage::Format_Indexed8);
//        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(qImage));
//        scene->addItem(pixmapItem);

        // Add contours overlay for the current slice
        for (const auto &contour : ROIPoints) {
            for (const auto &slicePoints : contour) {
                if (!slicePoints.isEmpty() && slicePoints.first()[2] == static_cast<double>(size[2])) {
                    QPolygonF polygon;
                    for (const auto &point : slicePoints) {
                        polygon << QPointF(point[0], point[1]);
                    }
                    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(polygon);
                    QPen pen(Qt::red);
                    pen.setWidth(2);
                    polygonItem->setPen(pen);
                    scene->addItem(polygonItem);
                }
            }
        }
    }
}
