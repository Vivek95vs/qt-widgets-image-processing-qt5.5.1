#include <QCoreApplication>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FILE *Img, *image_raw;
    Img = fopen("picture.inf","r");
    int **matriz_image, test;

    int i, j, rows, colums;


    //i read dimension image
    QDebug()<<Img;
    QDebug() <<&colums;
    QDebug() <<&rows;


    //i create dinamic rows
    matriz_image = (int **) malloc (rows*sizeof(int*));

    //i create dinamic colums
    for(i=0;i<rows;i++)
    {

         matriz_image[i] = (int*) malloc (colums*sizeof(int));



    }

    //i open image raw
    image_raw = fopen("picture.raw","r");

    //i copy values to matriz_image
    for(i=0;i<rows;i++)
    {
        for(j=0;j<colums;j++)
        {

            //std::cin>>image_raw>>&test;
            matriz_image[i][j]=test;
            qDebug()<< test;

        }

    }


    //i print matriz
    for(i=0;i<rows;i++)
    {
        for(j=0;j<colums;j++)
        {

            qDebug()<<matriz_image[i][j];


        }
        qDebug()<<endl;

    }
    return a.exec();
}
