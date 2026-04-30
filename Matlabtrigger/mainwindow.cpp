#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Enhancement_Rad.h"
#include <chrono>
#include <time.h>
#include <QDebug>
#include "QDir"
#include "DRRGen1.h"
#include "SC_grab.h"
#include "SC_grab_test.h"
#include "SC_grab_v2.h"
#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <cstdio>



using namespace std::chrono;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!mclInitializeApplication(nullptr, 0))
    {
        std::cerr << "Could not initialize the application." << std::endl;
        //return -1;
    }

    if (!Enhancement_RadInitialize())
    {
        std::cerr << "Could not initialize the library properly" << std::endl;
        //return -2;
    }

    if (!DRRGen1Initialize())
    {
        std::cerr << "Could not initialize the library properly" << std::endl;
        //return -2;
    }
    if(!SC_grabInitialize())
    {

        std::cerr << "Could not initialize SC_grab library properly" << std::endl;
    }

    if(!SC_grab_testInitialize())
    {

        std::cerr << "Could not initialize SC_grab_test library properly" << std::endl;
    }

    if(!SC_grab_v2Initialize())
    {

        std::cerr << "Could not initialize SC_grab_test_V2 library properly" << std::endl;
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Enhancement_RadSample()
{
    QString folderpath1InData="D:\\Pelvic Imagin";

    auto start1 = high_resolution_clock::now();

//    QString folderpath1InData=EnhancePath;
    mwArray folderpath1In(folderpath1InData.toStdString().c_str());
    try
    {
        Enhancement_Rad(folderpath1In);

    }
    catch (const mwException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error thrown" << std::endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start1);
    std::cout << "Time taken by To generate DRR: " << duration.count() << " seconds" << endl;

}
void MainWindow::on_pushButton_clicked()
{

    Enhancement_RadSample();

}

void MainWindow::on_pushButton_2_clicked()
{

        QString path="D:\\CapturedImages\\20240327\\2\\8\\23\\CT\\S1_P1\\FG1_FN2\\CT";
        QString ReferenceImages="D:\\DRROutput";
        QString Mode_DRR="AP-RLAT";
        QString GAngle_DRR="45";

        mwArray CTPath(path.toStdString().c_str());
        mwArray Outputpath(ReferenceImages.toStdString().c_str());
        mwArray Mode(Mode_DRR.toStdString().c_str());
        mwArray m_Gangle(GAngle_DRR.toStdString().c_str());

        try
        {
            DRRGen1(CTPath,Outputpath,Mode,m_Gangle);
        }
        catch (const mwException& e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unexpected error thrown" << std::endl;
        }


}

void MainWindow::on_bufffer_check_clicked()
{

    QString writepath="D:\\RTstructRead\\Malle_gowda\\Scatter corrected images";
    QString airmean = "D:\\Extern Buffer single Image\\dll_grabbing_scatercorrection\\air";


    mwArray CBCTwritePath(writepath.toStdString().c_str());
    mwArray airfolder(airmean.toStdString().c_str());

    QDir CBCT_Folder1("D:\\RTstructRead\\Malle_gowda\\RAW");
    QStringList filters;
    filters << "*.raw" ;
    CBCT_Folder1.setNameFilters(filters);

    QStringList rawfiles = CBCT_Folder1.entryList();

    qDebug()<<"path and length"<<rawfiles.length()<<airmean<<writepath;

    QByteArray ba;

    unsigned short* ExtBuffer=new unsigned short[1536*1536];

    for (int i=3;i<rawfiles.length()+1;++i){

    qDebug()<<"i value"<<i;

    ba = ("D:\\RTstructRead\\Malle_gowda\\RAW\\projD1_"+QString::number(i)+".raw").toLatin1();

    const char *fileName = ba.data();
    FILE    *fp;
    fopen_s(&fp, fileName, "rb");

    if(fp)
    {
        fread(ExtBuffer, sizeof(unsigned short), 1536*1536, fp);
        fclose(fp);
    }

    mwArray myMwArray(i);

    unsigned short **ExtBuffer2D = new unsigned short*[1536];
    for (int i = 0; i < 1536; ++i)
    {
        ExtBuffer2D[i] = new unsigned short[1536];
    }


    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            ExtBuffer2D[i][j] = ExtBuffer[j * 1536 +i];
        }
    }


//    mwArray buf(1, 1, mxUINT16_CLASS); // Create a 1x1 mwArray of type uint16
//    buf.SetData(reinterpret_cast<const mxUint16*>(&ExtBuffer), 1); // Set the value

    mwSize dims[2] = { 1536, 1536 }; // Dimensions of the matrix
    mwArray buf(2, dims, mxUINT16_CLASS); // Create a 1536x1536 mwArray of type uint16

    // Copy data from ExtBuffer to buf
    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            buf(i + 1, j + 1) = static_cast<mxUint16>(ExtBuffer2D[i][j]);
        }
    }

    try
    {
      auto start10 = high_resolution_clock::now();
      SC_grab(buf, myMwArray, CBCTwritePath, airfolder);
      auto stop10 = high_resolution_clock::now();
      auto duration10 = duration_cast<milliseconds>(stop10 - start10);
      qDebug() << "Time taken by matlab: "<< duration10.count() << " milliseconds" << endl;
    }
    catch (const mwException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error thrown" << std::endl;
    }

    }

}

void printBufferValue(unsigned short* ExtBuffer, int rows, int cols, int row, int col)
{
    // Calculate the 1D index from the 2D coordinates
    int index = col * cols + row;

    // Print the value at ExtBuffer[row][col]
    qDebug() << "Value at (" << row << ", " << col << "):" << ExtBuffer[index];
}


void MainWindow::on_buffertest_clicked()
{

    unsigned short* ExtBuffer=new unsigned short[1536*1536];

//    QString filename = "D:\\RTstructRead\\Malle_gowda\\RAW\\projD1_"+QString::number(3)+".raw";

    QString filename = "D:\\RTstructRead\\Malle_gowda\\image.raw";
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");


    if(Img)
    {
        fread(ExtBuffer,sizeof(unsigned short),1536*1536,Img);;
        qDebug() << "Image read:";

        int x = 23;
        int y = 47;
        unsigned short pixelValue = ExtBuffer[y*1536+ x];
        qDebug() << "Pixel value at (" << x << "," << y << "):" << pixelValue;

        fclose(Img);
    }
    else
    {
        qDebug()<<"fp Not opened";
    }

    unsigned short **ExtBuffer2D = new unsigned short*[1536];
    for (int i = 0; i < 1536; ++i)
    {
        ExtBuffer2D[i] = new unsigned short[1536];
    }


    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            ExtBuffer2D[i][j] = ExtBuffer[j * 1536 +i];
        }
    }


//    unsigned short **bckgnd_img = new unsigned short*[1536];

//    for (int i = 0; i < 1536; i++)
//        bckgnd_img[i] = new unsigned short[1536];
//    int p = 0;

//    for (int i = 0; i < 1536; i++)
//    {
//        for (int j = 0; j < 1536 ; j++)
//        {
//            bckgnd_img[i][j] = ExtBuffer[p];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
//            p = p + 1;
//        }
//    }
    FILE *outputImg = fopen("D:\\RTstructRead\\Malle_gowda\\image2.raw", "wb");
    if (outputImg)
    {
        for (int i = 0; i < 1536; ++i)
        {
            fwrite(ExtBuffer2D[i], sizeof(unsigned short), 1536, outputImg);
        }
        fclose(outputImg);
        qDebug() << "Image written to";
    }
    else
    {
        qDebug() << "Could not open output file";
    }

    qDebug()<<"2D array Val"<<ExtBuffer2D[23][47];

    mwSize dims[2] = { 1536, 1536 }; // Dimensions of the matrix
    mwArray buf(2, dims, mxUINT16_CLASS); // Create a 1536x1536 mwArray of type uint16

    // Copy data from ExtBuffer to buf
    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            buf(i + 1, j + 1) = static_cast<mxUint16>(ExtBuffer2D[i][j]);  //(ExtBuffer[i * 1536 + j])
        }
    }

    mxUint16 bufValue = buf(24, 48); // 1-based indexing
    qDebug() << "Value in buf at (23, 47):" << bufValue;


    printBufferValue(ExtBuffer, 1536, 1536, 23, 47);

    FILE *fp1;
    fopen_s(&fp1,"D:\\RTstructRead\\Malle_gowda\\image.raw","wb+");
  //  qDebug()<<"Trying to write !!"<<path;
    fwrite(ExtBuffer,sizeof(unsigned short),1536*1536,fp1);
    qDebug()<<"Trying to write !!";
    fclose(fp1);


    try
    {
      SC_grab_test(buf);
    }
    catch (const mwException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error thrown" << std::endl;
    }

//    }

}

void MainWindow::on_ImageBuff_return_clicked()
{

//    QString writepath="D:\\RTstructRead\\Malle_gowda\\Scatter corrected images";
    QString airmean = "D:\\Extern Buffer single Image\\dll_grabbing_scatercorrection\\air";


//    mwArray CBCTwritePath(writepath.toStdString().c_str());
    mwArray airfolder(airmean.toStdString().c_str());

    QDir CBCT_Folder1("D:\\RTstructRead\\Malle_gowda\\RAW");
    QStringList filters;
    filters << "*.raw" ;
    CBCT_Folder1.setNameFilters(filters);

    QStringList rawfiles = CBCT_Folder1.entryList();

    qDebug()<<"path and length"<<rawfiles.length()<<airmean;

    QByteArray ba;

    unsigned short* ExtBuffer=new unsigned short[1536*1536];

    for (int i=3;i<rawfiles.length()+1;++i){

    qDebug()<<"i value"<<i;

    ba = ("D:\\RTstructRead\\Malle_gowda\\RAW\\projD1_"+QString::number(i)+".raw").toLatin1();

    const char *fileName = ba.data();
    FILE    *fp;
    fopen_s(&fp, fileName, "rb");

    if(fp)
    {
        fread(ExtBuffer, sizeof(unsigned short), 1536*1536, fp);
        fclose(fp);
    }

//    mwArray myMwArray(i);

    unsigned short **ExtBuffer2D = new unsigned short*[1536];
    for (int i = 0; i < 1536; ++i)
    {
        ExtBuffer2D[i] = new unsigned short[1536];
    }


    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            ExtBuffer2D[i][j] = ExtBuffer[j * 1536 +i];
        }
    }


//    mwArray buf(1, 1, mxUINT16_CLASS); // Create a 1x1 mwArray of type uint16
//    buf.SetData(reinterpret_cast<const mxUint16*>(&ExtBuffer), 1); // Set the value

    mwSize dims[2] = { 1536, 1536 }; // Dimensions of the matrix
    mwArray buf(2, dims, mxUINT16_CLASS); // Create a 1536x1536 mwArray of type uint16

    // Copy data from ExtBuffer to buf
    for (int i = 0; i < 1536; ++i)
    {
        for (int j = 0; j < 1536; ++j)
        {
            buf(i + 1, j + 1) = static_cast<mxUint16>(ExtBuffer2D[i][j]);
        }
    }

    mwArray buf1(2, dims, mxUINT16_CLASS);

    try
    {
      auto start10 = high_resolution_clock::now();
      SC_grab_v2(1,buf1,buf,airfolder);

      // Convert buf1 to an array of unsigned short
      unsigned short* result = new unsigned short[1536 * 1536];
      mxUint64 len = static_cast<mxUint64>(1536 * 1536);
      mxUint64* tempBuffer = new mxUint64[len];

      buf1.GetData(tempBuffer, len);

      for (mxUint64 i = 0; i < len; ++i) {
          result[i] = static_cast<unsigned short>(tempBuffer[i]);
      }

      QString bufferpath=  "D:\\RTstructRead\\Malle_gowda\\Buffer raw\\projD1_"+QString::number(i)+".raw";

      FILE *fp1;
      fopen_s(&fp1,bufferpath.toStdString().c_str(),"wb+");
    //  qDebug()<<"Trying to write !!"<<path;
      fwrite(result,sizeof(unsigned short),1536*1536,fp1);
      qDebug()<<"Trying to write !!";
      fclose(fp1);


      auto stop10 = high_resolution_clock::now();
      auto duration10 = duration_cast<milliseconds>(stop10 - start10);
      qDebug() << "Time taken by matlab: "<< duration10.count() << " milliseconds" << endl;
    }
    catch (const mwException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error thrown" << std::endl;
    }

    }
}
