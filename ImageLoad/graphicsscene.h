#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
 #include <QGraphicsEllipseItem>
#include <QApplication>


class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene();

     enum Mode {Line, Ellipse,Rectangle,noitem};
     Mode m1;
     Mode m3;
     void temp(Mode m2);

     void clr();

     QGraphicsLineItem* itemToDraw=NULL;
     QGraphicsEllipseItem *itemellipse=NULL;
     QGraphicsRectItem *itemrect=NULL;



private:
    QPointF  previousPoint;



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:

    void measuredrawn(QGraphicsItem *);



};

#endif // GRAPHICSSCENE_H
