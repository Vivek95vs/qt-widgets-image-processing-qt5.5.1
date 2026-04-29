#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QGraphicsScene>
#include <QPoint>
#include <QMouseEvent>

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

private:
    Ui::paint *ui;
    paintscene *scene;


};

#endif // PAINT_H
