#ifndef OPERATION_H
#define OPERATION_H

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>

class Operation : public QGraphicsScene
{
      Q_OBJECT
public:
    explicit Operation(QObject *parent = 0);
    QRectF boundingRect() const;
    ~Operation();

private:
    void paintEvent(QPaintEvent *);
};

#endif // OPERATION_H
