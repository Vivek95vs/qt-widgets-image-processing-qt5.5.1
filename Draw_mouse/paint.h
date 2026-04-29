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
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

private:
    Ui::Paint *ui;
    QGraphicsScene *scene;

};

#endif // PAINT_H
