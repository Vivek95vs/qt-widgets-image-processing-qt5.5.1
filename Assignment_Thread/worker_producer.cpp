#include "worker_producer.h"
#include "basicfunc.h"

Worker_Producer::Worker_Producer(QObject *parent) : QObject(parent)
{

}

void Worker_Producer::producer()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < DataSize; ++i)
    {
        //freeBytes.acquire();
//        buffer[i % BufferSize] = [(int)qrand() % 4];
        //usedBytes.release();
        if(i % 20 == 0)
        emit bufferFillCountChanged(usedBytes.available());
        emit producerCountChanged(i);
    }
}

