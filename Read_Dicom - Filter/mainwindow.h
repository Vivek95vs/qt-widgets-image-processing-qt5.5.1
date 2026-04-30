#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QWidget>
#include <QtWidgets>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int i;
    QImage q_image;
    QImage q_image1;
    int Rows;
    int Cols;
    unsigned char *dispImg;
    unsigned char *dispImg1;
    QString SiteNameLabel;
    ~MainWindow();

private slots:
    void on_LOAD_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsScene *scene1;
    QGraphicsView *view1;
    QGraphicsItem *item1;
};

#endif // MAINWINDOW_H
