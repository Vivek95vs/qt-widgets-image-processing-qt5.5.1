
#include <QtGui>
#include "QApplication"
#include "QFileDialog"

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWidget w;
    w.show();

    if (QApplication::arguments().size() > 1)
        w.openDirectory(QApplication::arguments().at(1));
    else
        w.openDirectory(QFileDialog::getExistingDirectory(0, "Select image folder"));

    return app.exec();
}
