#include "imagewidget.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400, 300);
    imageWidget = new ImageWidget(this);
    setCentralWidget(imageWidget);
}

void MainWidget::openDirectory(const QString &path)
{
    imageWidget->openDirectory(path);
}
