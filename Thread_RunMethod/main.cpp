#include "run_over.h"
#include "consumer_run.h"
#include "producer_run.h"
#include "nonchangable.h"
#include "commonfun.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Run_Over w;
    w.show();

    return a.exec();
}
