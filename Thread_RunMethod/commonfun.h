#ifndef COMMONFUN
#define COMMONFUN

#include <QSemaphore>
#include "nonchangable.h"

extern char buffer[BufferSize];

extern QSemaphore freeBytes;
extern QSemaphore usedBytes;

#endif // COMMONFUN

