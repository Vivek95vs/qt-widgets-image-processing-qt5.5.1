#include "push.h"
#include "ui_push.h"

push::push(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::push)
{
    ui->setupUi(this);
}

push::~push()
{
    delete ui;
}
