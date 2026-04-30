#include "imageenhancementnew.h"
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
int numTiles[2]={4,4};
int ImageSize;
int dimTile[2];
int nbins=65536;
float* aLut;
unsigned short* claheI;
//unsigned short * Output_Data;
float * gauss_Data;


ImageEnhancementNew::ImageEnhancementNew()
{

}

void ImageEnhancementNew::StartImageEnhancement(unsigned short *Input1, unsigned short *Output, int rowS, int colS)
{
    start = clock();
    //**********************************Variable declaration*********************************//

    int numPixIntile;
    unsigned short* tile;
    int selectedRange[2]={0,65535};
    int fullRange[2]={0,65535};
    int* Histogram;
    float mapping1;
    int* histSum;
    ImageSize = rowS;
    int imgCol,imgRow;

    Input = (unsigned short*)malloc(sizeof(unsigned short)*ImageSize*ImageSize);
    if (Input == NULL)
        printf("Memory is not allocated");

    //        //*********************************End of reading file*******************************//

    for (int i=0;i<ImageSize*ImageSize;i++)
    {
        Input[i] = Input1[i];
    }

    float* Log_Data;
    Log_Data = (float *)malloc(ImageSize*ImageSize*sizeof(float));
    if(Log_Data==NULL)
        printf("Log_Data Memory is not allocated");

    for (int i=0;i<ImageSize*ImageSize;i++)
        Log_Data[i] = (float)Input[i];

    unsigned short int vMax = 0;
    float LogImage = 0;
    for(int i = 0; i < ImageSize*ImageSize; i++)
    {
        if(vMax <= Input[i])
            vMax = Input[i];
    }

    float gMax = 0, gMin = 0;
    float Temp =1;

    for(int i = 0; i < ImageSize; i++)
    {
        //Input[i] = 0;
        for(int j = 0; j < ImageSize; j++)
        {
            //Log correction
            Log_Data[i*ImageSize + j] = max(Log_Data[i*ImageSize + j],1);

            LogImage = -logf(min(max(Log_Data[i*ImageSize + j]/vMax, 0), 1));
            if(LogImage > INFINITE)
                LogImage = 0;
            if(LogImage != LogImage)
                LogImage = 0;

            //To get maximum value
            if(gMax < LogImage)
                gMax = LogImage;
            //To get minimum value
            if(gMin > LogImage)
                gMin = LogImage;

            Log_Data[i*ImageSize + j] = LogImage;
        }
    }

    //************************************Scaling the Image*********************************//

    for(int i = 0; i < ImageSize; i++)
        for(int j = 0; j < ImageSize; j++)
        {
            //Temp = (Log_Data[i*ImageSize + j] - gMin)/(gMax - gMin);

            Input[i*ImageSize + j] =  (Log_Data[i*ImageSize + j] - gMin)/(gMax - gMin) * 65535;

            //Input[i*ImageSize + j] = Temp*65535;//16384;
        }
    //***********************************End Log correction********************************//
    free(Log_Data);
    //******************Backgroud Elimination (using Thresholding) ***********************//
    /*for (int i=0;i<ImageSize*ImageSize;i++)
                       Input[i]=Input[i]<2000?0:Input[i];*/
    //*****************End Backgroud Elimination (using Thresholding) *********************//
    //****************************MakeTileMappings calculation**************************//

    int l1;
    dimTile[0]=ImageSize/numTiles[0];
    dimTile[1]=ImageSize/numTiles[1];
    numPixIntile=dimTile[0]*dimTile[1];

    // *********************************Tile Spliting*********************************//
    imgCol = 0;
    for (int Cell_Col=0;Cell_Col<numTiles[1];Cell_Col++)
    {
        imgRow = 0;
        for (int Cell_Row=0;Cell_Row<numTiles[0];Cell_Row++)
        {
            tile=(unsigned short*)malloc(sizeof(unsigned short)*dimTile[0]*dimTile[1]);
            if(tile==NULL)
                printf("Tile Memory is not allocated");

            l1=0;
            for (int i=imgRow;i<imgRow+dimTile[0];i++)
            {
                for (int j=imgCol;j<imgCol+dimTile[1];j++)
                {
                    tile[l1]=Input[(j*ImageSize)+i];
                    l1=l1+1;
                }
            }
            /*end = clock();
                   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                   printf("Tile Splitting:%f\n",cpu_time_used);*/
            // *********************************End Tile Spliting*********************************//
            //start = clock();
            Histogram=(int*)malloc(sizeof(int)*65537);
            if(Histogram==NULL)
                printf("Histogram Memory is not allocated");
            // *****************************Histogram calculation*****************************//
            for (int j=0;j<=nbins;j++)
                Histogram[j]=0;

            for (int j=0;j<dimTile[0]*dimTile[1];j++)
            {
                Histogram[tile[j]]=Histogram[tile[j]]+1;
            }

            //***************************End of Histogram calculation***************************//
            free(tile);
            //*************************Cliplimit Histogram calculation*************************//
            //start = clock();
            int totalExcess=0;
            int cliplimit = 0;
            if (ImageSize == 1536)
                cliplimit = 50;
            else
                cliplimit = 700;//1298
            int avgBinIncr,upperLimit;
            for (int i=0;i<nbins;i++)
                totalExcess=((Histogram[i]-cliplimit)>0?totalExcess+(Histogram[i]-cliplimit):totalExcess);

            avgBinIncr=floor(float(totalExcess)/nbins);
            upperLimit=cliplimit-avgBinIncr;
            // this loop should speed up the operation by putting multiple pixels
            // into the "obvious" places first
            for (int k=0;k<nbins;k++)
            {
                if(Histogram[k] > cliplimit)
                    Histogram[k] = cliplimit;
                else
                {
                    if (Histogram[k] > upperLimit) // high bin count
                    {
                        totalExcess = totalExcess - (cliplimit - Histogram[k]);
                        Histogram[k] = cliplimit;
                    }
                    else
                    {
                        totalExcess = totalExcess - avgBinIncr;
                        Histogram[k] = Histogram[k] + avgBinIncr;
                    }
                }
            }
            // this loops redistributes the remaining pixels, one pixel at a time
            int k = 0;
            int stepSize;
            while (totalExcess != 0)
            {
                //keep increasing the step as fewer and fewer pixels remain for
                //the redistribution (spread them evenly)
                stepSize = floor(float(nbins)/totalExcess)<1?1:floor(float(nbins)/totalExcess);
                for (int m=k;m<nbins;m=m+stepSize)
                {
                    if (Histogram[m] < cliplimit)
                    {
                        Histogram[m] = Histogram[m]+1;
                        totalExcess = totalExcess - 1;//reduce excess
                        if (totalExcess == 0)
                            break;
                    }
                }

                k = k+1; //prevent from always placing the pixels in bin #1
                if (k > nbins) // start over if nbins was reached
                    k = 1;
            }
            //*****************************MakeMapping calculation***************************//

            histSum=(int*)malloc(sizeof(int)*65537);
            if(histSum==NULL)
                printf("Histogram Sum Memory is not allocated");

            int valSpread;
            float alpha=0.5,hconst,vmax,temp,val;
            histSum[0]= Histogram[0];
            for (int i=1; i<nbins; i++)
                histSum[i]= Histogram[i]+histSum[i-1];
            valSpread  = selectedRange[1] - selectedRange[0];
            free(Histogram);
            //***************************** Rayleigh Distribution ***************************//
            {
                /*	mapping1=(float*)malloc(sizeof(float)*65536);
                   if(mapping1==NULL)
                       printf("Mapping Memory is not allocated");*/

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
            //************************End of MakeMapping calculation**************************//
            imgRow = imgRow + dimTile[0];
        }
        imgCol = imgCol + dimTile[1];
    }
    //	//**********************End of MakeTileMappings calculation************************//
    //	//**************************MakeClaheImage calculation***************************//

    aLut=(float*)malloc(sizeof(float)*(65536));
    if(aLut==NULL)
        printf("aLut Memory is not allocated");

    claheI=(unsigned short*)malloc(ImageSize*ImageSize*sizeof(unsigned short));
    if(claheI==NULL)
        printf("CLAHE Image Memory is not allocated");


    for (int k1 =selectedRange[0];k1<=selectedRange[1];k1++)
        aLut[k1]=((float)((k1)-selectedRange[0])/(selectedRange[1]-selectedRange[0]));


    //HANDLE ghMutex;
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

    // passing data to threads
    for(i = 0;i < N_THREADS; i++)
    {
        pMakeClahe_Info[i] = &MakeClahe_Info[i];

        ulMapTile=(float*)malloc(sizeof(float)*65536);
        if(ulMapTile==NULL)
            printf("ulMapTile Memory is not allocated");

        urMapTile=(float*)malloc(sizeof(float)*65536);
        if(urMapTile==NULL)
            printf("urMapTile Memory is not allocated");

        blMapTile=(float*)malloc(sizeof(float)*65536);
        if(blMapTile==NULL)
            printf("blMapTile Memory is not allocated");


        brMapTile=(float*)malloc(sizeof(float)*65536);
        if(brMapTile==NULL)
            printf("brMapTile Memory is not allocated");

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

        // CreateThread function creates the threads :/
        thread_h[i] = CreateThread(NULL,0,MakeClaheImage,pMakeClahe_Info[i],0,&mythreadid);
        //thread_h[i] = CreateThread(NULL,0,MakeClaheImage,0,0,&mythreadid);
        // when each thread is done doing its work, it returns null
        // after which we can terminate the thread process
        if ( thread_h[i] == NULL)
            ExitProcess(3);
    }
    //}

    // Wait for all threads to finish
    WaitForMultipleObjects(N_THREADS,thread_h,TRUE, INFINITE);

    for( i=0; i < N_THREADS; i++ )
    {
        CloseHandle(thread_h[i]);
    }

    free(ulMapTile);
    free(urMapTile);
    free(blMapTile);
    free(brMapTile);
    //	//**************************End MakeClaheImage calculation***************************//
    //	//**************************Gaussian filter calculation***************************//
    // gauss_Data = (float *)malloc(ImageSize*ImageSize*sizeof(float));



    //                       int mini = 65535, maxi = 0;


    //                               for (int i = 0; i < ImageSize; i++)
    //                               {
    //                                       for (int j = 0; j < ImageSize; j++)
    //                                       {
    //                                               mini = (mini>claheI[i*ImageSize+j] ? claheI[i*ImageSize+j] : mini); //limit to max
    //                                               maxi = (maxi<claheI[i*ImageSize + j] ? claheI[i*ImageSize + j] : maxi); //limit to max

    //                                       }
    //                               }

    // unsigned short* Normalization = (unsigned short*)malloc(ImageSize*ImageSize*sizeof(unsigned short));



    //                       if (ImageSize == 3072)
    //                               {
    //                                       //Normalization = Normalization_Function(claheI, ImageSize, (mini), (maxi ));
    //                                      // gaussFilt(claheI, 2, gauss_Data, ImageSize);
    //                                       /*for (int i = 0; i<ImageSize*ImageSize; i++)
    //                                               claheI[i] = claheI[i]<28000 ? 0 : claheI[i];*/

    //                               }
    //                               else
    //                               {
    //                                      // Normalization = Normalization_Function(claheI, ImageSize, (mini), (maxi));
    //                                      // gaussFilt(Normalization, 2, gauss_Data, ImageSize);
    //                                       /*for (int i = 0; i<ImageSize*ImageSize; i++)
    //                                               gauss_Data[i] = gauss_Data[i]<22000 ? 0 : gauss_Data[i];*/

    //                               }


    //	//***********************End Gaussian filter calculation***********************//


    unsigned short* OutputPre = new unsigned short[rowS*colS];
    unsigned short* OutputPre1 = new unsigned short[rowS*colS];

    //memcpy(OutputPre,claheI,ImageSize*ImageSize*sizeof(unsigned short));
    memcpy(Output,claheI,ImageSize*ImageSize*sizeof(unsigned short));


    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //                   int k = 0;
    //                           for (int i = 0; i < rowS; i++, k = 0)
    //                           {
    //                               for (int j = (colS - 1); j >= 0; j--, k++)
    //                               {
    //                                   OutputPre1[(i*rowS) + k] = OutputPre[(j*colS) + i];
    //                                //   cout << Iarray1[(i*rowS) + k] << " ";
    //                               }
    //                              // cout << "\n";
    //                           }


    //                           //cout << "\n"; cout << "\n"; cout << "\n"; cout << "\n";
    //                            k = 0;
    //                           for (int i = 0; i < rowS; i++, k = 0)
    //                           {
    //                               for (int j = (colS - 1); j >= 0; j--, k++)
    //                               {
    //                                   Output[(i*rowS) + k] = OutputPre1[(j*colS) + i];
    //                                 //  cout << Iarray[(i*rowS) + k] << " ";
    //                               }
    //                              // cout << "\n";
    //                           }

    //printf("Time Elapsed:%f\n",cpu_time_used);

    //**********************End of MakeClaheImage calculation************************//
    free(Input);
    free(aLut);
    free(claheI);
    free(gauss_Data);
    //return 0;


}

unsigned short GrayXForm1(unsigned short ImagePixel,float* Lut,int sizeofLut)
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
//************************************************************************************************************************************************//
//void gaussFilt(unsigned short *image, int sigma, float *outputImage, int imageSize)
//{
//    unsigned short	*paddedInput;
//    paddedInput = (unsigned short*)malloc((imageSize+4)*(imageSize+4)*sizeof(unsigned short)); //4 extra rows and colemns for kernel size of 5 X 5

//    // defining the padded Input

//    // first the inside region
//    for(int r=2; r < (imageSize+4)-2; r++)
//        for(int c=2; c < (imageSize+4)-2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[(r-2)*imageSize+(c-2)];

//    // next, defining the top rows
//    for(int r=0; r < 2; r++)
//    {
//        //middle part, copy the first row
//        for(int c=2; c < (imageSize+4)-2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[0+(c-2)];
//        //left corner, copy the first element only
//        for(int c=0; c < 2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[0];
//        //right corner, copy the last element of the first row
//        for(int c=(imageSize+2); c < (imageSize+4); c++)
//            paddedInput[r*(imageSize+4)+c] = image[(imageSize-1)];
//    }

//    // next, defining the bottom rows
//    for(int r=(imageSize+2); r < (imageSize+4); r++)
//    {
//        //middle part, copy the last row
//        for(int c=2; c < (imageSize+4)-2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[(imageSize-1)*imageSize+(c-2)];
//        //left corner, copy the first element only
//        for(int c=0; c < 2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[(imageSize-1)*imageSize];
//        //right corner, copy the last element of the last row
//        for(int c=(imageSize+2); c < (imageSize+4); c++)
//            paddedInput[r*(imageSize+4)+c] = image[(imageSize-1)*imageSize+(imageSize-1)];
//    }

//    //defining the left most columns
//    for(int r=2; r < (imageSize+4)-2; r++)
//        for(int c=0; c < 2; c++)
//            paddedInput[r*(imageSize+4)+c] = image[(r-2)*imageSize];

//    //defining the right most columns
//    for(int r=2; r < (imageSize+4)-2; r++)
//        for(int c=(imageSize+2); c < (imageSize+4); c++)
//            paddedInput[r*(imageSize+4)+c] = image[(r-2)*imageSize+(imageSize-1)];


//    // Now, define the gaussianKernel of 5 X 5 for sigma = 1
//    float	gaussKernel[25], kernelSum = 0;// since the coefs are real

//    for(int kr = -2; kr < 3; kr++)
//        for(int kc = -2; kc < 3; kc++)
//        {
//            gaussKernel[(kr+2)*5+(kc+2)] = exp(-(kc*kc+kr*kr)/(2.0*sigma*sigma));
//            kernelSum += gaussKernel[(kr+2)*5+(kc+2)];
//        }

//    for(int kr = -2; kr < 3; kr++)
//    {
//        for(int kc = -2; kc < 3; kc++)
//        {
//            gaussKernel[(kr+2)*5+(kc+2)] /= kernelSum;
//            //printf("%f ", gaussKernel[(kr+2)*5+(kc+2)]);
//        }
//        //printf("\n");
//    }


//    // Apply the kernel on the padded input

//    float	centerPixel;

//    for(int r = 2; r < (imageSize+4)-2; r++)
//        for(int c = 2; c < (imageSize+4)-2; c++)
//        {
//            centerPixel = 0;
//            for(int kr = -2; kr < 3; kr++)
//                for(int kc = -2; kc < 3; kc++)
//                    centerPixel += paddedInput[(r+kr)*(imageSize+4)+(c+kc)] * gaussKernel[(kr+2)*5+(kc+2)] ;
//            outputImage[(r-2)*imageSize+(c-2)] = centerPixel;
//        }

//    free(paddedInput);
//}


//unsigned short*Normalization_Function(unsigned short* InputImage, int ImageSize,int minValue, int maxValue)
//{

//        unsigned short* Normalization ;
//        Normalization = (unsigned short*)malloc(sizeof(unsigned short)*ImageSize*ImageSize);

//        float  N1_min = (float)minValue;
//        float N1_max = (float)maxValue;
//        int saturatedValue;
//        //Finding_Normalization_Of_The_Image
//        for (int i = 0; i < ImageSize; i++)
//        {
//                for (int j = 0; j < ImageSize; j++)
//                {
//                        saturatedValue = InputImage[i*ImageSize+j] - ((unsigned short)N1_min);
//                        if (saturatedValue > 0)
//                        {
//                                Normalization[i*ImageSize + j] = round(((((float)(saturatedValue))) / (float)(N1_max - (N1_min)))*(75000));
//                        }
//                        else
//                        {
//                                Normalization[i*ImageSize + j] = 0;
//                        }
//                }
//        }


//        return Normalization;
//}



DWORD WINAPI MakeClaheImage(LPVOID Param)
{
    MakeClahe_Struct *pInfo;
    //**************************MakeClaheImage calculation***************************//
    //Tile Mapping,Original Image,Number of Tiles,Select Range,Number of Bins,Dim Tiles

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
                    //            /claheI[(TileRow*ImageSize)+TileCol]=((rowRevW*(colRevW*(GrayXForm1(imgPixVals,Test_ulMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_urMapTile,0)))+rowW*(colRevW*(GrayXForm1(imgPixVals,Test_blMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_brMapTile,0))))/normFactor);
                    claheI[(TileCol*ImageSize)+TileRow]=((rowRevW*(colRevW*(GrayXForm1(imgPixVals,Test_ulMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_urMapTile,0)))+rowW*(colRevW*(GrayXForm1(imgPixVals,Test_blMapTile,0))+colW*(GrayXForm1(imgPixVals,Test_brMapTile,0))))/normFactor);

                }
            }
            // imgTileCol = imgTileCol + imgTileNumCols;
        }
        //imgTileRow = imgTileRow + imgTileNumRows;
    }

    return 0;
}
