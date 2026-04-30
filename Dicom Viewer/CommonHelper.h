#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QString>
#include <QFileDialog>
#include <qapplication.h>

class CommonHelper
{
public:
    CommonHelper();
    ~CommonHelper();
    static void setStyle(const QString& style);
    static bool isADicomOrDicomDir(std::string filename);
};

#endif // COMMONHELPER_H
