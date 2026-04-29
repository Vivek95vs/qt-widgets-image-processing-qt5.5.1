#include "test_thread.h"
#include "worker_consumer.h"
#include "worker_producer.h"
#include "constants.h"
#include "basicfunc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test_Thread w;
    w.show();

    return a.exec();
}
