#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_pushButton_clicked();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    int temp(uchar* t);

private:
    Ui::Dialog *ui;
    QGraphicsItem *item;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // DIALOG_H
