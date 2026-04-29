#include "worker_consumer.h"
#include "basicfunc.h"

Worker_Consumer::Worker_Consumer(QObject *parent) : QObject(parent)
{

}

void Worker_Consumer::consumer()
{

    for (int i = 0; i < DataSize; ++i)
    {
        //usedBytes.acquire();

        //freeBytes.release();
        emit bufferFillCountChanged(usedBytes.available());
        emit consumerCountChanged(i);
    }
}

