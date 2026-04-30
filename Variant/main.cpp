#include <QCoreApplication>
#include <Qtcore>
#include <QVariant>
#include <QDebug>
#include "vclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVariant b=125.64;

    qDebug()<<b.toInt();
    qDebug()<<b.toDouble();
    qDebug()<<b.toString();

    if(b.canConvert<QString>())
    {
        qDebug()<<b.toString();
    }

    vclass cClass;
    cClass.number=333433;

    QVariant z=QVariant::fromValue(cClass);
    vclass zclass =z.value<vclass>();
    qDebug()<<zclass.number;

    return a.exec();
}

