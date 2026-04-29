#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "QGraphicsView"
#include "QGraphicsScene"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QCustomPlot *customplot;
    void setup();

private:
    Ui::MainWindow *ui;

    QGraphicsView *view;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
