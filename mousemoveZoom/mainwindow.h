#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int w=3072;
    int h =3072;

private:
    Ui::MainWindow *ui;
    unsigned char *opdata;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item ;

protected:
  bool eventFilter(QObject* object,QEvent* event);
private slots:
  void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
