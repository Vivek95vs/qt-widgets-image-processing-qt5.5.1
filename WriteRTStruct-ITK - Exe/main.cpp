#include <QCoreApplication>
#include "rtstruct.h"
//#include "QDebug"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RTStruct R;

//    QString list2= "D:\\1008\\CT";
//    argv[1] =(char*)list2.toStdString().c_str();

//    QStringList list;
//    list.append("124.674");
//    list.append("132.593");
//    list.append("1.58101e-322");
//    list.append("172.003");
//    list.append("132.593");
//    list.append("1.58101e-322");
//    list.append("172.003");
//    list.append("157.454");
//    list.append("1.58101e-322");
//    list.append("124.674");
//    list.append("157.454");
//    list.append("1.58101e-322");
//    list.append("124.674");
//    list.append("132.593");
//    list.append("1.58101e-322");

//    QString list3 = list.join(",");
//    argv[2] =(char*)list3.toStdString().c_str();

//    QStringList list4;
//    list4.append("30");
//    list4.append("31");
//    list4.append("32");
//    list4.append("33");
//    list4.append("34");
//    list4.append("35");
//    list4.append("36");
//    list4.append("37");
//    list4.append("38");
//    list4.append("39");
//    list4.append("40");
//    list4.append("41");
//    list4.append("42");
//    list4.append("43");
//    list4.append("44");

//    QString list5 = list4.join(",");
//    argv[3] =(char*)list5.toStdString().c_str();


    R.on_readtag_clicked(argv[1],argv[2],argv[3]);

//    R.inputparameters(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);


    a.quit();
}

