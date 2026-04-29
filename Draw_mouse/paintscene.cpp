#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    double rad = 5;
    ellipse= scene->addEllipse(event->scenePos().x() - rad,event->scenePos().y() - rad,rad*2,rad*2,QPen(Qt::NoPen),QBrush(Qt::green));
    previousPoint = event->scenePos();
}

void paint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    line= scene->addLine(previousPoint.x(),previousPoint.y(),event->scenePos().x(),event->scenePos().y(),QPen(Qt::green,10,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->scenePos();
}
