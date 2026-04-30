#include "worker.h"
#include "QDebug"

Worker::Worker()
{

}

void Worker::tagprocess()
{
    emit sendtagprocess();
}

