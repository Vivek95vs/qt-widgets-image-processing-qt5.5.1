#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QVTKWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_PB_load_clicked();

private:
    Ui::MainWindow *ui;
    QVTKWidget *vtkWidget;
};

#endif // MAINWINDOW_H
