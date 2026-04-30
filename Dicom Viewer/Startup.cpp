#include "Startup.h"

Startup::Startup(QWidget *parent)
    : QWidget(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    ui.setupUi(this);
}

Startup::~Startup()
{
}
