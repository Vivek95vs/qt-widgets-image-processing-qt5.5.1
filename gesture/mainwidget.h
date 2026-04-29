
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

class ImageWidget;

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);

public slots:
    void openDirectory(const QString &path);

private:
    bool loadImage(const QString &fileName);

    ImageWidget *imageWidget;
};

#endif
