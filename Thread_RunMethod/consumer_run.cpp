#include "consumer_run.h"
#include "commonfun.h"

Consumer_run::Consumer_run(QObject *parent):QThread(parent)
{

}


void Consumer_run::run()
{
    for (int i = 0; i < DataSize; ++i)
    {
        usedBytes.acquire();
        fprintf(stderr, "%c", buffer[i % BufferSize]);
        freeBytes.release();
        emit bufferFillCountChanged(usedBytes.available());
        emit consumerCountChanged(i);
    }

}
