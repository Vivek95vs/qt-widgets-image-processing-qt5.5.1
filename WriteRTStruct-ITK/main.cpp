#include <QCoreApplication>
#include "rtstruct.h"
#include "QDebug"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RTStruct R;

//    QString list1= "D:\\writeStruct\\CT";
//    argv[2] =(char*)list1.toStdString().c_str();

    QString list2= "D:\\writeStruct\\CT";
    argv[1] =(char*)list2.toStdString().c_str();

    QString list3= "10,11,12";
    argv[2] =(char*)list3.toStdString().c_str();


    R.on_readtag_clicked(argv[1],argv[2]);

//    R.inputparameters(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);


    a.quit();
}

