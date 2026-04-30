#include "triggerexe.h"
#include "QFile"
#include "QTextStream"

Triggerexe::Triggerexe()
{

}

void Triggerexe::Triggercheck(QString path)
{
    QString text8= path+"/log.txt";
    QFile fileOffLog8(text8);

    QTextStream stream8(&fileOffLog8);

    fileOffLog8.open(QIODevice::ReadWrite|QIODevice::Text);

    stream8<<"Exe has been triggered"<<endl;

    stream8<<"Exe has been triggered ended"<<endl;

    fileOffLog8.close();



}

