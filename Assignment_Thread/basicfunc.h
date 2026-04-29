#ifndef BASICFUNC
#define BASICFUNC

#include <QSemaphore>
#include "constants.h"

extern char buffer[BufferSize];

extern QSemaphore freeBytes;
extern QSemaphore usedBytes;
#endif // BASICFUNC

