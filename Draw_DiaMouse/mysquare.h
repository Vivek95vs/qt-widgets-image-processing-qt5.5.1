#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <iostream>
#include <QPixmap>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>

class mySquare: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit mySquare(QObject *parent = 0);
    int selectedTool;
    QPixmap mPix;
    QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintEvent(QPaintEvent *event);
    bool pressed;
    bool drawStarted;
    int X_1, Y_1,X_2, Y_2,X_3, Y_3,X_4, Y_4;
    ~mySquare();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF mRect;
    QPointF y;


private slots:

};

#endif // MYSQUARE_H
