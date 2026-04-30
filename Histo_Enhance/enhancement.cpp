
#include "Enhancement.h"
#include <iostream>
#include <fstream>
#include <QDebug>
using std::string;  /* Most recommended */
std::ofstream file;

Enhancement::Enhancement()
{

}

Enhancement::~Enhancement()
{

}

unsigned short** Enhancement::Conversion(unsigned short* image, int rowS, int colS)
{
    unsigned short** InputImage = new unsigned short*[rowS];

    for (int i = 0; i < rowS; i++)
        InputImage[i] = new unsigned short[colS];
    int k = 0;

    for (i = 0; i < rowS; i++)
    {
        for (j = 0; j < colS; j++)
        {
            InputImage[i][j] = image[k];		// Conversion_Of_1_Dimension_To_2_Dimension__________________________________
            k = k + 1;
        }
    }
    return InputImage;

}

unsigned short** Enhancement::Normalization_Function(unsigned short** InputImage, int rowSize, int colSize, int minValue, int maxValue, float Angle)
{
    unsigned short** Normalization = new unsigned short*[rowSize];
    for (int i = 0; i < rowSize; i++)
        Normalization[i] = new unsigned short[colSize];
    float  N1_min = minValue, N1_max = maxValue;
    float TempMin;

    if (Angle < -6)
    {
        if (minValue < 100)
            minValue = minValue * 400;//400
        else
            minValue = minValue * 180;//180
        N1_min = minValue, N1_max = maxValue;
        if (N1_min > N1_max)
        {
            N1_min = maxValue - 5000, N1_max = minValue;
            TempMin = maxValue;
        }
        else
            TempMin = minValue;
    }

    else if (Angle > 6)
    {
        if ((minValue < 200) && (minValue > 100))
            minValue = minValue * 120;
        else if (minValue < 100)
            minValue = minValue * 280;
        else
            minValue = minValue * 80;

        N1_min = minValue + 6000, N1_max = maxValue + 6000;
        if (N1_min > N1_max)
            //N1_min = maxValue - 30000, N1_max = minValue - 6000;
            N1_min = maxValue - ((minValue / 2)), N1_max = minValue - (maxValue / 10);

        TempMin = minValue;

    }

    else
    {
        minValue = (minValue + 5/*- 70*/) * 85;
        N1_min = minValue, N1_max = maxValue;

        TempMin = (minValue - 70) * 85;
    }

    if (Angle < -6)
    {
        float Difference = N1_max - N1_min;
        float Addition = N1_max + Difference;
        float Subtraction = N1_min - Difference;
        if (N1_max < 35000)
        {
            N1_max = N1_max + 30000;
            if (N1_min < 25000)
                N1_min += 30000;
        }
        else if (N1_max < 45000)
        {
            N1_max += 18000;
            N1_min += 18000;
        }
        else if ((Difference <= 15000) && (Addition < 65535)) // Counldn't get image for this condition
        {
            N1_max -= 2000;
            N1_min -= 12000;
        }
        else if ((Difference <= 10000) && (Subtraction > 0) && ((N1_min - 12000) > 0))
        {
            N1_max -= 2000;
            N1_min -= 12000;
        }
    }

    else if (Angle > 6)
    {
        float Difference = N1_max - N1_min;
        float Addition = N1_max + Difference;
        float Subtraction = N1_min - Difference;
        if ((Difference <= 15000) && (Addition < 65535)) // Counldn't get image for this condition
        {
            if (N1_max < 52000)
                N1_max += 12000;
            else
                N1_max += 10000;

            N1_min += 8000;
        }
        else if ((Difference <= 10000) && (Subtraction > 0))
        {
            N1_max += 2000;
            N1_min += 2000;
        }

    }

    //std::cout << "N1_max :: " << N1_max << " N1_min ::" << N1_min << std::endl;
    qDebug()<<"N1_max :: " << N1_max << " N1_min ::" << N1_min ;
    int saturatedValue;
    //Finding_Normalization_Of_The_Image
    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            if (Angle < -6)
                saturatedValue = InputImage[i][j] - TempMin; //  N1_min
            else if (Angle > 6)
                saturatedValue = InputImage[i][j] - TempMin; //  TempMin
            else
                saturatedValue = InputImage[i][j] - N1_min; //

            //std::cout << "saturatedValue :: " << saturatedValue << " InputImage[i][j] ::" << InputImage[i][j] << std::endl;
            if (saturatedValue > 0)
            {
                Normalization[i][j] = round(((((float)(saturatedValue))) / (N1_max - N1_min))*(65535));//50000
            }
            else
            {
                Normalization[i][j] = 0;
            }
            //std::cout << " Normalization[i][j] ::" << Normalization[i][j] << " InputImage[i][j] ::" << InputImage[i][j] << std::endl;
        }

    }


    //for (int i = 5600; i < rowSize; i++) // 5300
    //{
    //	for (int j = 0; j < colSize; j++)
    //	{
    //		Normalization[i][j] = 0;
    //	}
    //}


    return Normalization;
}

unsigned short** Enhancement::Complement_Function(unsigned short** NormalizedImage, int rowSize, int colSize)
{
    unsigned short** Complement = new unsigned short*[rowSize];
    for (int i = 0; i < rowSize; i++)
        Complement[i] = new unsigned short[colSize];

    for (i = 0; i < rowSize; i++)
        for (j = 0; j < colSize; j++)
            Complement[i][j] = (unsigned short)abs((int)NormalizedImage[i][j] - 65535);

    return  Complement;

}

unsigned short** Enhancement::Histogram_calculation(unsigned short** ComplementImage, int rowSize, int colSize, float Angle)
{
    int maximum_value = 65535;
    int maxi_Divide = 85;
    int N_maximum_value = maximum_value / maxi_Divide;
    unsigned long int sum = 0;
    int min = 0;
    const int Total_value = rowSize * colSize;
    //unsigned short* TwoDToOne = new unsigned short[Total_value];
    //unsigned short* O_TwoDToOne = new unsigned short[Total_value];
    unsigned short* Hist_value = new unsigned short[maximum_value+1];
    unsigned short* Sum_Hist_value = new unsigned short[N_maximum_value];
    unsigned short** Normalization/* = new unsigned short*[rowSize];

                    for (int i = 0; i < rowSize; i++)
                        Normalization[i] = new unsigned short[colSize]*/;

    for (int i = 0; i < maximum_value; i++)
    {
        Hist_value[i] = 0;
        if (i < N_maximum_value)
            Sum_Hist_value[i] = 0;
    }
    //Finding_Histogram_Value_Of_The_Image
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if(ComplementImage[i][j]>65535 || ComplementImage[i][j]<0)
                qDebug()<<"Invalid pixel at"<<i<<j;
            Hist_value[ComplementImage[i][j]] = Hist_value[ComplementImage[i][j]] + 1;
        }
    }

    /*for (i = 0; i < maximum_value; i++)
    {
    std::cout << Hist_value[i] << " ";// All Histogram_values...
    }*/


    int j = 0;
    int iu = 0;

    for (int i = 0; i < maximum_value; i++)
    {
        sum = sum + Hist_value[i];
        if (((i % maxi_Divide) == 0) && (i != 0))
        {
            iu++;
            Sum_Hist_value[j] = sum / maxi_Divide;
            //std::cout << Sum_Hist_value[j] << " ";
            j++;
            sum = 0;
        }
    }

    int Max_Sum_Value_Position = 0;
    int Max_Sum_Value_Position_point = 0;
    for (int i = 0; i < N_maximum_value; i++)
    {
        if (Sum_Hist_value[i] == 0)
        {
            Max_Sum_Value_Position_point++;
            int i1 = i;
            for (int i2 = (i1 + 1); i2 < N_maximum_value; i2++)
            {
                if (Sum_Hist_value[i2] == 0)
                    Max_Sum_Value_Position_point++;
                else
                    Max_Sum_Value_Position_point = 0;
            }
            if (Max_Sum_Value_Position_point >= i1)
            {
                Max_Sum_Value_Position = i1;
                break;
            }
        }
    }


    //int Max_Sum_Value_Position1 = Max_Sum_Value_Position * (maxi_Divide);
    //int Max_Sum_Value_Position1 = Max_Sum_Value_Position * (maxi_Divide + 5);


    int Msubtraction = 0, MLocation, MA_location = 0;
    int Mtemp = 0;
    for (int i = (N_maximum_value - 1); i >= 0; i--)
    {
        //std::cout << "\n" << (int)Sum_Hist_value[i] << "-" <<  (int)Sum_Hist_value[i - 1] << "\n";
        Msubtraction = (int)Sum_Hist_value[i] - Sum_Hist_value[i - 1];
        if (Msubtraction <= 0 && Sum_Hist_value[i] != 0 && Sum_Hist_value[i - 1] != 0)
        {
            //std::cout << "\ni = " << i << " " << (int)Sum_Hist_value[i] <<" "<< (int)Sum_Hist_value[i-1] << "\n";
            Mtemp++;
            if (Mtemp >= 4)//>9
            {
                int i1 = i - 1;
MLable:
                Msubtraction = (int)Sum_Hist_value[i1] - Sum_Hist_value[i1 - 1];
                if (Msubtraction < -5)
                {
                    MLocation = i;
                    MA_location = (MLocation+5)* maxi_Divide;
                    //std::cout << "\ni = " << Sum_Hist_value[i1-1] << "\n" << Sum_Hist_value[i1] << "\n";
                    //std::cout << "MA_location :: " << MA_location << std::endl;
                    break;
                }
                else
                    i1--;
                goto MLable;
            }
        }
        else
            Mtemp = 0;
    }


    //	std::cout << "\n\nTotal entered times " << iu << std::endl;
    int subtraction = 0, Location=0, A_location = 0;
    int temp = 0;
    for (int i = 0; i < N_maximum_value - 1; i++)
    {
        subtraction = (int)Sum_Hist_value[i] - Sum_Hist_value[i + 1];
        if (subtraction <= 0 && Sum_Hist_value[i] !=0 && Sum_Hist_value[i + 1] !=0 )
        {
            temp++;
            //std::cout << "\ni = " << i << " " << (int)Sum_Hist_value[i] << " " << (int)Sum_Hist_value[i + 1] <<" temp :: "<<temp<< "\n"<<std::endl;
            //std::cout << "Location :: " << Location << std::endl;
            if (temp >= 4)
            {
                int i1 = i + 1;
Lable:
                subtraction = (int)Sum_Hist_value[i1] - Sum_Hist_value[i1 + 1];
                //std::cout << "\ni1 = " << i1 << " " << Sum_Hist_value[i1] << " " << Sum_Hist_value[i1 + 1] << " " << subtraction << "\n" << std::endl;
                if (subtraction < -5 )//-10
                {
                    Location = i1;
                    A_location = (Location - 5) * maxi_Divide;
                    break;
                    //if ((MLocation - Location) > 85 ){
                    //	i1++;
                    //	goto Lable;
                    //}
                    //else
                    //{
                    //	std::cout << "\ni1 = " << Sum_Hist_value[i1 + 1] << "\n" << Sum_Hist_value[i1] << "\n";
                    //	std::cout << "A_location :: " << A_location << std::endl;
                    //	break;
                    //}
                }
                else
                    i1++;
                goto Lable;
            }
        }
        else
            temp = 0;
    }

    if (Location == 0){
        for (int k = 1; k < N_maximum_value; k++){
            if (Sum_Hist_value[k - 1] != 0 && Sum_Hist_value[k] != 0 && Sum_Hist_value[k + 1] != 0){
                if (Sum_Hist_value[k - 1] > Sum_Hist_value[k] && Sum_Hist_value[k] < Sum_Hist_value[k + 1]){
                    //std::cout << "\nk = " << k << " " << Sum_Hist_value[k - 1] << " " << Sum_Hist_value[k] << " " << Sum_Hist_value[k + 1] << "\n" << std::endl;
                    //std::cout << "abs :: " << abs(Sum_Hist_value[k - 1] - Sum_Hist_value[k + 1]) << std::endl;
                    if (abs(Sum_Hist_value[k - 1] - Sum_Hist_value[k + 1]) >= 5 && abs(Sum_Hist_value[k - 1] - Sum_Hist_value[k + 1]) < 100){
                        //std::cout << "local minima :: " << Sum_Hist_value[k - 1] << " " << Sum_Hist_value[k] << " " << Sum_Hist_value[k + 1] << std::endl;
                        Location = k-5;
                        break;
                    }
                }
            }
        }
    }

    int Background_Zero = 0;//To remove background.
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (Background_Zero < (A_location))
                ComplementImage[i][j] = 0;
            Background_Zero++;
        }
    }




    /*int count = 0;
    for (int i = 1; i < Location; i++)
    {
    if (Sum_Hist_value[Location - i] > 100)
    {
    count = i;
    break;
    }
    }*/

    //for testing
    if(Location==0 && MA_location==0)
    {
        qDebug()<<"low values";
        Location=765;
        MA_location=65035;
    }
    if (MA_location==0){
        qDebug()<<"max low values"<<Location;
        MA_location = (Location+1)*85;
        if ((MA_location+500) > 65535)
            MA_location = 65035;
    }
    //for testing




    //if (count > 50)//if pixel value difference between background is more than 25500 image forground is not clearly visible .so we eliminate the background and normalize the image.
    //{
    Normalization = Normalization_Function(ComplementImage, rowSize, colSize, Location, (MA_location+500/* + 1000*/), Angle);//Function_call_for_Normalization_Function//
    //Normalization = Normalization_Function(ComplementImage, rowSize, colSize,10820, 32415);//Function_call_for_Normalization_Function//
    //}
    //else
    //{
    //	//std::cout << "\n\n\n" << std::endl;
    //	for (i = 0; i < rowSize; i++)
    //	{
    //		for (j = 0; j < colSize; j++)
    //		{
    //			//std::cout << ComplementImage[i][j] << " ";
    //			Normalization[i][j] = ComplementImage[i][j];
    //		}
    //		//std::cout << "\n";
    //	}
    //}

    /*int s1=24000,s2=60535,r1=0,r2=14000;

    for (i = 0; i < rowSize; i++)
    {
    for (j = 0; j < colSize; j++)
    {
    Normalization[i][j] = (round(((float)(s2 - s1) / (r2 - r1)) * (float)(Normalization[i][j] - r1) + (float)s1));
    }
    }*/

    delete[] Hist_value;
    delete[] Sum_Hist_value;
    return Normalization;
}

void Enhancement::Convertion2D1(unsigned short** Normalization, unsigned short *image, int  rowSize, int colSize)
{
    int k = 0;

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            image[k] = Normalization[i][j];
            k++;
        }
    }
}

void Enhancement::gaussFilt(unsigned short *image, int sigma, unsigned short*outputImage, int rowSize, int colSize)
{
    unsigned short	*paddedInput;

    paddedInput = (unsigned short*)malloc((rowSize + 4)*(colSize + 4) * sizeof(unsigned short)); //4 extra rows and columns for kernel size of 5 X 5

    // defining the padded Input

    // first the inside region
    for (int r = 2; r < (rowSize + 4) - 2; r++)
    {
        for (int c = 2; c < (colSize + 4) - 2; c++)
        {
            paddedInput[r*(colSize + 4) + c] = image[(r - 2)*colSize + (c - 2)];
        }
    }
    // Now, define the gaussianKernel of 5 X 5 for sigma = 1
    float	gaussKernel[25], kernelSum = 0;// since the coefs are real

    for (int kr = -2; kr < 3; kr++)
    {
        for (int kc = -2; kc < 3; kc++)
        {
            gaussKernel[(kr + 2) * 5 + (kc + 2)] = exp(-(kc*kc + kr*kr) / (2.0*sigma*sigma));
            kernelSum += gaussKernel[(kr + 2) * 5 + (kc + 2)];
        }
    }

    for (int kr = -2; kr < 3; kr++)
    {
        for (int kc = -2; kc < 3; kc++)
        {
            gaussKernel[(kr + 2) * 5 + (kc + 2)] /= kernelSum;
        }
    }
    // Apply the kernel on the padded input
    float	centerPixel;
#pragma omp parallel for
    for (int r = 2; r < (rowSize + 4) - 2; r++)
    {
        for (int c = 2; c < (colSize + 4) - 2; c++)
        {
            centerPixel = 0;
            for (int kr = -2; kr < 3; kr++)
                for (int kc = -2; kc < 3; kc++)
                    centerPixel += paddedInput[(r + kr)*(colSize + 4) + (c + kc)] * gaussKernel[(kr + 2) * 5 + (kc + 2)];
            outputImage[(r - 2)*colSize + (c - 2)] = round(centerPixel);
        }
    }

    /*FILE* Fp1;
    fopen_s(&Fp1, "Output_Head.raw", "wb+");
    fwrite(outputImage, sizeof(unsigned short), colSize * rowSize, Fp1);
    fclose(Fp1);*/
    delete[] paddedInput;
}

unsigned short*  Enhancement::ImageEnhancement(unsigned short* inputImage, int rowSize, int colSize, int Angle)
{
    unsigned short** InputImage/* = new unsigned short*[rowSize];//Allocating_Memory//
                    for (int i = 0; i < rowSize; i++)
                        InputImage[i] = new unsigned short[colSize]*/;

    unsigned short** ComplementImage/* = new unsigned short*[rowSize];//Allocating_Memory//
                    for (int i = 0; i < rowSize; i++)
                        ComplementImage[i] = new unsigned short[colSize]*/;


    //double* thresholdValue = new double[2];

    /*unsigned short** NormalizedImage = new unsigned short*[rowSize];
    for (int i = 0; i < rowSize; i++)
        NormalizedImage[i] = new unsigned short[colSize]*/;

    unsigned short** Normalization/* = new unsigned short*[rowSize];
                    for (int i = 0; i < rowSize; i++)
                        Normalization[i] = new unsigned short[colSize]*/;


    unsigned short* outputImage1 = new unsigned short[rowSize * colSize];

    unsigned short *Normalized_image = new unsigned short[rowSize * colSize];
    unsigned short* image;
    image = (unsigned short*)inputImage;

    //	unsigned short** EnhancementImage = new unsigned short*[rowSize];
    //	for (int i = 0; i < rowSize; i++)
    //		EnhancementImage[i] = new unsigned short[colSize];

    int sigma = 3;
    //float Angle = float(IAngle / 10.0);

    /*file.open("Angle From Front End.txt");
    file << "Angle From Front End\t" << Angle;
    file.close();*/

    InputImage = Conversion(image, rowSize, colSize);	//Function_call_for_1D_to_2D_Conversion//
    ComplementImage = Complement_Function(InputImage, rowSize, colSize);
    Normalization = Histogram_calculation(ComplementImage, rowSize, colSize, Angle);	//Function_call_for_Histogram_calculation//
    Convertion2D1(Normalization, Normalized_image, rowSize, colSize);
    gaussFilt(Normalized_image, sigma, outputImage1, rowSize, colSize);

    //	unsigned char* outputImage = new unsigned char[colSize*rowSize];
    //	outputImage = (unsigned char*)outputImage1;

    //for (i = 0; i < rowSize; i++)
    //{
    //	for (j = 0; j < rowSize; j++)
    //	{
    //		fprintf(Fp1,"%u")
    //	}

    //    FILE* Fp1;
    //    fopen_s(&Fp1, "enhanced.raw", "wb+");
    //errno_t err;

    ///*char * cstr = new char[Path.length() + 1];
    //std::strcpy(cstr, Path.c_str());*/

    //if ((err = fopen_s(&Fp1, "histeqImg.raw", "wb+")) != 0)
    //	printf("file was not opened\n");
    ////for (i = 0; i < rowsize; i++)
    //    fwrite(outputImage1, sizeof(unsigned short), rowSize*colSize, Fp1);
    //    fclose(Fp1);

    delete [] Normalized_image;

    return outputImage1;
}

