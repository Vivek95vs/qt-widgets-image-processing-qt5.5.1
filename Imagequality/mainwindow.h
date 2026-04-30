#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    int height=1536;
    int width=1536;

private slots:
    void on_Load_Image_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
