#include <QCoreApplication>
#include <QtCore>
#include <QDebug>

void save()
{
    QFile file("D:/Workflow/Work/vivek.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<"good evening\r\n";
        stream<<"friends and family";

        stream.flush();
        file.close();
        qDebug()<<"file is written";
    }
}
void read()
{
    QFile file("D:/Workflow/Work/vivek.txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString linebyline;
        do{
            linebyline=stream.readAll();
            qDebug()<<linebyline;
        }while(!linebyline.isNull());
        file.close();
        qDebug()<<"File is read";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    save();
    read();
    return a.exec();
}

