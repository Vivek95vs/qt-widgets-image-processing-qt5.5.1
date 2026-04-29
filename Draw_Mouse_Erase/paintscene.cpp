#include "paintscene.h"

paintscene::paintscene(QObject *parent) : QGraphicsScene(parent)
{

}

paintscene::~paintscene()
{

}
void paintscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    double rad = 5;
    addEllipse(event->scenePos().x() - rad,event->scenePos().y() - rad,rad*2,rad*2,QPen(Qt::NoPen),QBrush(Qt::green));
    previousPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void paintscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    addLine(previousPoint.x(),previousPoint.y(),event->scenePos().x(),event->scenePos().y(),QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);

}

void paintscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    addLine(previousPoint.x(),previousPoint.y(),event->scenePos().x(),event->scenePos().y(),QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
}
