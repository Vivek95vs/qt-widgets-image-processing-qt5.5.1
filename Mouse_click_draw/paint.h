#ifndef PAINT_H
#define PAINT_H

#include <QWidget>


#include "paintscene.h"

namespace Ui {
class paint;
}

class paint : public QWidget
{
    Q_OBJECT

public:
    explicit paint(QWidget *parent = 0);
    ~paint();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::paint *ui;
    paintScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;

};

#endif // PAINT_H
