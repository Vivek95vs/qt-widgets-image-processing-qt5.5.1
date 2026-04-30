#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsItem *item;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QScrollBar *bar;


protected:
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
