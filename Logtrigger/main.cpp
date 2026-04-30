#include <QCoreApplication>
#include "triggerexe.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Triggerexe T;

//    QString list2= "D:\\writeStruct\\10-01-2023";
//    argv[1] =(char*)list2.toStdString().c_str();
    T.Triggercheck(argv[1]);

    a.quit();
    //return a.exec();
}

