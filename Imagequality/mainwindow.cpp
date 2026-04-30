#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_Load_Image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[height*width];
    fread(Image,1,width*height*sizeof(unsigned short),Img);

//    QString filenam12="D:\\size";
//    std::string fileName13 = filenam12.toStdString() + "\\Image_" + std::to_string(5) + ".raw";
//    FILE *fp1;
//    fopen_s(&fp1,fileName13.c_str(),"wb+");
//    fwrite(Image,sizeof(unsigned short),1536*1536,fp1);
//    fclose(fp1);

    unsigned short** ComplementImage = new unsigned short*[height];//Allocating_Memory//
      for (int i = 0; i < height; i++)
          ComplementImage[i] = new unsigned short[width];

      unsigned short **bckgnd_img = new unsigned short*[height];

      for (int i = 0; i < height; i++)
          bckgnd_img[i] = new unsigned short[width];
        int p = 0;

       for (int i = 0; i < height; i++)
       {
            for (int j = 0; j < width ; j++)
           {
              bckgnd_img[i][j] = Image[p];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
              p = p + 1;
           }
       }

       for (int i = 0; i < height; i++)
       {
           for (int j = 0; j < width; j++)
           {
               ComplementImage[i][j] = (unsigned short)abs((int)bckgnd_img[i][j] - 65535);
           }
       }

       unsigned short *temp_buffer = new unsigned short[width*height];     // Conversion of 2_Dimension to 1_Dimension_________________________
       for(int i=0;i<height;i++)
       {
           for(int j=0;j<width;j++)
           {
               temp_buffer[i*width+j]=ComplementImage[i][j];
           }
       }

       int maximum_value = 65536;

       unsigned short* histo_gram = new unsigned short[maximum_value+1];

       for(int i=0;i<=maximum_value;i++)
       {
           histo_gram[i]=0;
       }

       for(int j=0;j<width*height;j++)
       {
           histo_gram[temp_buffer[j]] = histo_gram[temp_buffer[j]]+1;
       }

       int min_value;

       for(int k=0;k<maximum_value;k++)
       {
           if(histo_gram[k] > 0)
           {
                min_value = k;
                k=maximum_value;
           }
       }

       qDebug()<<min_value<<"the sub_value is-------";

       int max_value=0;
       for(int m=0;m<width*height;m++)
       {
           if(temp_buffer[m]>max_value)
           {
               max_value=temp_buffer[m];
           }
       }
       qDebug()<<max_value<<"maximum value-------";


//    int px_value = temp_buffer[0];
//       int mode = px_value;
//       int count = 1;
//       int countMode = 1;

//       for(int i=0;i<width*height;i++)
//       {
//           if(temp_buffer[i]==px_value)
//           {
//               ++count;
//           }
//           else
//           {
//               if(count > countMode)
//               {
//                   countMode = count;
//                   mode = px_value;
//               }
//               count=1;
//               px_value = temp_buffer[i];
//           }
//       }

//       for(int i=0;i<width*height;i++)
//       {
//           if(temp_buffer[i] == mode)
//           {
//               temp_buffer[i]=0;
//           }
//       }

       int s1 = 0;
       int s2 = 65535;
       int r1 = min_value/*+5000*/;
       int r2 = max_value;

       for(int y=0;y<width*height;y++)
       {
           if(temp_buffer[y]>0 && temp_buffer[y]<r1)
           {
               temp_buffer[y] = (s1/r1)*temp_buffer[y];
           }
           else if(temp_buffer[y]>r1 && temp_buffer[y]<r2)
           {
               temp_buffer[y] = ((s2-s1)/(r2-r1))*(temp_buffer[y]-r1) + s1/*+5000*/;
           }
           else
           {
               temp_buffer[y] = temp_buffer[y];
           }
       }

//       QString filename2="D:\\size";
//       std::string fileName3 = filename2.toStdString() + "\\Image_" + std::to_string(2) + ".raw";
//       FILE *fp;
//       fopen_s(&fp,fileName3.c_str(),"wb+");
//       fwrite(temp_buffer,sizeof(unsigned short),1536*1536,fp);
//       fclose(fp);

           unsigned char* arr=new unsigned char[width*height];
           for(int i=0;i<width*height;i++)
           {
               arr[i]=((temp_buffer[i]*255)/max_value);
           }
       //    qDebug()<<arr[20];
           QImage myImage = QImage(arr,1536,1536,QImage::Format_Grayscale8);
           item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
           scene = new QGraphicsScene();
           view = new QGraphicsView(scene);

           ui->graphicsView->setScene(scene);
           ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
           scene->addItem(item);
}
