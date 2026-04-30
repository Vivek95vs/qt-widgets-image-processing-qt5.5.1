#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
#include <time.h>

#define N_THREADS 4

const int Struct_n = 8;

double cpu_time_used;
 clock_t start;
 clock_t end;

 struct Struct
 {
     float Mapping[65536];
 }Struct_Tile[4][4];

typedef struct
{
    float* ThreadulMapTile;
    float* ThreadurMapTile;
    float* ThreadblMapTile;
    float* ThreadbrMapTile;
    int Threadstart;
    int Threadstop;
}MakeClahe_Struct;

DWORD WINAPI MakeClaheImage(LPVOID lpParam);
unsigned short GrayXForm1(unsigned short ImagePixel,float* Lut,int sizeofLut);
void gaussFilt(unsigned short *image, int sigma, float *outputImage, int imageSize);
unsigned short*Normalization_Function(unsigned short* InputImage, int ImageSize,int minValue, int maxValue);
unsigned short* Input;
int selectedRange[2]={0,65535};
int fullRange[2]={0,65535};
int numTiles[2]={4,4};
unsigned short* image;
unsigned short *Output;
int dimTile[2];
int ImageSize;
int nbins=65536;
float* aLut;
unsigned short* claheI;
int w=3072,h=3072;


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

void MainWindow::on_PB_Load_clicked()
{
    start = clock();

    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* image1=new unsigned short[w*h];
    image=(unsigned short*)malloc(sizeof(unsigned short)*ImageSize*ImageSize);
    if(image==NULL)
    {
        qDebug()<<"Memory is not allocated";
    }
    for (int i=0;i<ImageSize*ImageSize;i++)
    {
        image[i]=image1[i];
    }

    float* Log_Data;
    Log_Data=(float *)malloc(ImageSize*ImageSize*sizeof(float));
    if(Log_Data==NULL)
    {
        qDebug()<<"Log_Data memory is not allocated";
    }

    for(int i=0;i<ImageSize*ImageSize;i++)
    {
        Log_Data[i]=(float)image[i];
    }

    unsigned short int vMax=0;
    float LogImage=0;
    for(int i=0;i<ImageSize*ImageSize;i++)
    {
        if(vMax<=image[i])
            vMax=image[i];
    }
    float gMax=0, gMin=0;
//    float Temp=1;

    for(int i=0;i<ImageSize;i++)
    {
        for(int j=0;j<ImageSize;j++)
        {
            Log_Data[i*ImageSize+j]=max(Log_Data[i*ImageSize+j],1);
            LogImage= -logf(min(max(Log_Data[i*ImageSize+j]/vMax,0),1));

            if(LogImage > INFINITE)
                LogImage=0;
            if(LogImage != LogImage)
                LogImage=0;

            if(gMax < LogImage)
                gMax=LogImage;
            if(gMin > LogImage)
                gMin=LogImage;

            Log_Data[i*ImageSize+j]= LogImage;
        }
    }

    for (int i=0;i<ImageSize;i++)
    {
        for (int j=0;j<ImageSize;j++)
        {
            image[i*ImageSize+j]=(Log_Data[i*ImageSize+j]-gMin)/(gMax-gMin)*65535;
        }
    }

    free(Log_Data);

    int l1;
    dimTile[0]=ImageSize/numTiles[0];
    dimTile[1]=ImageSize/numTiles[1];
    numPixIntile=dimTile[0]*dimTile[1];

    imgCol=0;
    for(int Cell_Col=0;Cell_Col<numTiles[1];Cell_Col++)
    {
        imgRow=0;
        for(int Cell_Row=0;Cell_Row<numTiles[0];Cell_Row++)
        {
            tile=(unsigned short*)malloc(sizeof(unsigned short)*dimTile[0]*dimTile[1]);
            if(tile==NULL)
            {
                qDebug()<<"Tile memory is not allocated";
            }
            l1=0;

            for (int i=imgRow;i<imgRow+dimTile[0];i++)
            {
                for(int j=imgCol;j<imgCol+dimTile[1];j++)
                {
                    tile[l1]=image[(j*ImageSize)+i];
                    l1=l1+1;
                }
            }

            Histogram=(int*)malloc(sizeof(int)*65537);
            if(Histogram==NULL)
            {
                qDebug()<<"Histogram memory is not allocated";
            }
            for(int j=0;j<=nbins;j++)
            {
                Histogram[j]=0;
            }
            for(int j=0;j<dimTile[0]*dimTile[1];j++)
            {
                Histogram[tile[j]]=Histogram[tile[j]]+1;
            }

            free(tile);

            int totalExcess=0;
            int cliplimit=0;
            if(ImageSize==1536)
                cliplimit=50;
            else
                cliplimit=700;

            int avgBinIncr,upperLimit;

            for(int i=0;i<nbins;i++)
            {
                totalExcess=((Histogram[i]-cliplimit)>0?totalExcess+(Histogram[i]-cliplimit):totalExcess);
            }

            avgBinIncr=floor(float(totalExcess)/nbins);
            upperLimit=cliplimit-avgBinIncr;

            for(int k=0;k<nbins;k++)
            {
                if(Histogram[k]>cliplimit)
                    Histogram[k]=cliplimit;
                else
                {
                    if(Histogram[k]>upperLimit)
                    {
                        totalExcess=totalExcess-(cliplimit-Histogram[k]);
                        Histogram[k]=cliplimit;
                    }
                    else
                    {
                        totalExcess=totalExcess-avgBinIncr;
                        Histogram[k]=Histogram[k]+avgBinIncr;
                    }
                }
            }

            int k=0;
            int stepsize;
            while (totalExcess!=0)
            {
                stepsize=floor(float(nbins)/totalExcess)<1?1:floor(float(nbins)/totalExcess);
                for(int m=k;m<nbins;m=m+stepsize)
                {
                    if(Histogram[m]<cliplimit)
                    {
                        Histogram[m]=Histogram[m]+1;
                        totalExcess=totalExcess-1;
                        if(totalExcess==0)
                            break;
                    }
                }

                k=k+1;
                if(k>nbins)
                    k=1;
            }

            histSum=(int*)malloc(sizeof(int)*65537);
            if(histSum==NULL)
            {
                qDebug()<<"Histogram Sum memory is allocated";
            }
            int valSpread;
            float alpha=0.5,hconst,vmax,temp,val;
            histSum[0]= Histogram[0];
            for (int i=1; i<nbins; i++)
                histSum[i]= Histogram[i]+histSum[i-1];
            valSpread  = selectedRange[1] - selectedRange[0];
                free(Histogram);
            {
                    hconst = 2*pow(alpha,2);
                    vmax = 1 - exp(-1/hconst);
                        for (int i=0; i<nbins; i++)
                        {
                        val = vmax*(histSum[i]/(float)numPixIntile);
                        val=val>=1?1-0.0000000001:val;// avoid log(0)
                        temp= sqrt(-hconst*log(1-val));
                        mapping1 = (selectedRange[0]+temp*valSpread>selectedRange[1]?selectedRange[1]:selectedRange[0]+temp*valSpread); //limit to max
                        Struct_Tile[Cell_Row][Cell_Col].Mapping[i]=(mapping1/fullRange[1]);
                        }
                        free(histSum);

            }
                imgRow = imgRow + dimTile[0];
        }

        imgCol = imgCol + dimTile[1];
    }

    aLut=(float*)malloc(sizeof(float)*(65536));
    if(aLut==NULL)
    {
        qDebug()<<"aLut Memory is not allocated";
    }
    claheI=(unsigned short*)malloc(ImageSize*ImageSize*sizeof(unsigned short));
    if(claheI==NULL)
    {
        qDebug()<<"CLAHE Image Memory is not allocated";
    }
    for (int k1 =selectedRange[0];k1<=selectedRange[1];k1++)
    aLut[k1]=((float)((k1)-selectedRange[0])/(selectedRange[1]-selectedRange[0]));

    DWORD mythreadid;
    HANDLE thread_h[N_THREADS];
    MakeClahe_Struct MakeClahe_Info[N_THREADS],*pMakeClahe_Info[N_THREADS];

    int i;
    float* ulMapTile;
    float* urMapTile;
    float* blMapTile;
    float* brMapTile;
    int Threadstart;
    int Threadstop;

    for(i = 0;i < N_THREADS; i++)
    {
        pMakeClahe_Info[i] = &MakeClahe_Info[i];

    ulMapTile=(float*)malloc(sizeof(float)*65536);
    if(ulMapTile==NULL)
        qDebug()<<"ulMapTile Memory is not allocated";

    urMapTile=(float*)malloc(sizeof(float)*65536);
    if(urMapTile==NULL)
        qDebug()<<"urMapTile Memory is not allocated";

    blMapTile=(float*)malloc(sizeof(float)*65536);
    if(blMapTile==NULL)
        qDebug()<<"blMapTile Memory is not allocated";


    brMapTile=(float*)malloc(sizeof(float)*65536);
    if(brMapTile==NULL)
        qDebug()<<"brMapTile Memory is not allocated";

    int Interval;
    Interval=numTiles[0]/N_THREADS;
    if(i==0)
    {
    Threadstart=((i)*Interval);
    Threadstop=((i+1)*Interval);
    }
    else
    {
    Threadstart=((i)*Interval)+1;
    Threadstop=((i+1)*Interval);
    }

    MakeClahe_Info[i].ThreadulMapTile=ulMapTile;
    MakeClahe_Info[i].ThreadurMapTile=urMapTile;
    MakeClahe_Info[i].ThreadblMapTile=blMapTile;
    MakeClahe_Info[i].ThreadbrMapTile=brMapTile;
    MakeClahe_Info[i].Threadstart=Threadstart;
    MakeClahe_Info[i].Threadstop=Threadstop;

    thread_h[i] = CreateThread(NULL,0,MakeClaheImage,pMakeClahe_Info[i],0,&mythreadid);

    if ( thread_h[i] == NULL)
    ExitProcess(3);
    }

    WaitForMultipleObjects(N_THREADS,thread_h,TRUE, INFINITE);

    for( i=0; i < N_THREADS; i++ )
    {
        CloseHandle(thread_h[i]);
    }

    free(ulMapTile);
    free(urMapTile);
    free(blMapTile);
    free(brMapTile);

//    memcpy(Output,claheI,ImageSize*ImageSize*sizeof(unsigned short));


//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    free(Input);
    free(aLut);
    free(claheI);
    free(gauss_Data);


    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((claheI[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);

 }

unsigned short GrayXForm1(unsigned short ImagePixel, float *Lut, int sizeofLut)
{
    int Image,index;
    unsigned short Gray_output;
    int maxTidx;
    float scale;
    Image=ImagePixel;
    maxTidx=sizeofLut;
if(maxTidx == 0)
{
            Gray_output = (65535 * Lut[Image]+ 0.5);
}
else
{
     scale = maxTidx / 65535;
      try
      {
       index =  ceil(Image * scale + 0.5);
       Gray_output = floor(65535* Lut[index] + 0.5);
      }
      catch (...)
      {
        index =  floor(Image* scale + 0.5);
        Gray_output= floor (65535* Lut[index] + 0.5);
      }
}
return (Gray_output);

}

DWORD WINAPI MakeClaheImage(LPVOID Param)
{
    MakeClahe_Struct *pInfo;

    int mapTileRows[2],mapTileCols[2];
    int imgTileRow=0,imgTileNumRows;
    int imgTileCol=0,imgTileNumCols;
    int normFactor,k;
    double rowW,Row,rowW1,Row1;
    double colW,Col,colW1,Col1;
    double rowRevW,rowRevW1;
    double colRevW,colRevW1;

    unsigned short imgPixVals;
    int TileRow,TileCol;
    float * Test_ulMapTile;
    float * Test_urMapTile;
    float * Test_blMapTile;
    float * Test_brMapTile;
    //unsigned short* claheI1;
    int start;
    int stop;

    pInfo = (MakeClahe_Struct*)Param;

    Test_ulMapTile= pInfo -> ThreadulMapTile;
    Test_urMapTile= pInfo -> ThreadurMapTile;
    Test_blMapTile= pInfo -> ThreadblMapTile;
    Test_brMapTile= pInfo -> ThreadbrMapTile;
    start= pInfo -> Threadstart;
    stop= pInfo -> Threadstop;

    for (int k =start;k<=stop;k++)
    {

        if (k == 0)  //special case: top row
        {
        imgTileNumRows = dimTile[0]/2; //always divisible by 2 because of padding
        mapTileRows[0] =0;
        mapTileRows[1] =0;
        imgTileRow = k*imgTileNumRows;
        }
        else
       {
            if (k == numTiles[0])//special case: bottom row
            {
              imgTileNumRows = dimTile[0]/2;
            mapTileRows[0] =numTiles[0]-1;
            mapTileRows[1] =numTiles[0]-1;
            imgTileRow = ImageSize-imgTileNumRows;
            }
            else //default values
            {
              imgTileNumRows = dimTile[0];
              mapTileRows[0] =k-1;
            mapTileRows[1] = k;
            imgTileRow =((k-1)*imgTileNumRows)+(dimTile[0]/2);
             }
        }

    // loop over columns of the tileMappings cell array
         //imgTileCol=0;
      for (int l =0;l<=numTiles[1];l++)
      {

        if (l == 0) //special case: left column
        {
          imgTileNumCols = dimTile[1]/2;
            mapTileCols[0] =0;
            mapTileCols[1] =0;
        imgTileCol = l*imgTileNumCols;
        }
        else
        {
          if (l == numTiles[1])// special case: right column
          {
            imgTileNumCols = dimTile[1]/2;
            mapTileCols[0] =numTiles[1]-1;
            mapTileCols[1] = numTiles[1]-1;
            imgTileCol = ImageSize-imgTileNumCols;
          }
          else //default values
          {
            imgTileNumCols = dimTile[1];
            mapTileCols[0] =l-1;
            mapTileCols[1] = l;
            imgTileCol =((l-1)*imgTileNumCols)+(dimTile[1]/2);
          }
        }

    // Extract four tile mappings
      for (int i=0; i<nbins; i++)
    {
      Test_ulMapTile[i] =Struct_Tile[mapTileRows[0]][mapTileCols[0]].Mapping[i];
      Test_urMapTile[i] =Struct_Tile[mapTileRows[0]][mapTileCols[1]].Mapping[i];
      Test_blMapTile[i] =Struct_Tile[mapTileRows[1]][mapTileCols[0]].Mapping[i];
      Test_brMapTile[i] =Struct_Tile[mapTileRows[1]][mapTileCols[1]].Mapping[i];
    }


     normFactor = imgTileNumRows*imgTileNumCols;

     for (TileRow=imgTileRow;TileRow<imgTileRow+imgTileNumRows;TileRow++)
     {

          for (TileCol=imgTileCol;TileCol<imgTileCol+imgTileNumCols;TileCol++)
         {
            rowW=(TileRow-imgTileRow);
            colW=(TileCol-imgTileCol);
            rowRevW=imgTileNumRows-(TileRow-imgTileRow);
            colRevW=imgTileNumCols-(TileCol-imgTileCol);
            imgPixVals=GrayXForm1(Input[(TileCol*ImageSize)+TileRow],aLut,0);
            claheI[(TileCol*ImageSize)+TileRow]=((rowRevW*(colRevW*(GrayXForm1(imgPixVals,Test_ulMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_urMapTile,0)))+rowW*(colRevW*(GrayXForm1(imgPixVals,Test_blMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_brMapTile,0))))/normFactor);

          }
     }
    }
}
    QString Path =("D:/Workflow/Test images/5.raw");
    FILE *fp;
    fp=fopen(Path.toStdString().c_str(),"wb+");
    fwrite(claheI,sizeof(unsigned short),ImageSize*ImageSize,fp);
    fclose(fp);


    return 0;
}





