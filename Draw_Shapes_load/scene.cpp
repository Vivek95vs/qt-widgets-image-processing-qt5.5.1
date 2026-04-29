#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;

}
Scene::~Scene()
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine){
//    addEllipse(event->scenePos().x() - 50,event->scenePos().y() - 50,100,100,QPen(Qt::NoPen),QBrush(Qt::red));
//    origPoint = event->scenePos();
    itemToDraw->setLine(0,0,event->scenePos().x() - origPoint.x(),event->scenePos().y() - origPoint.y());
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine){
        if(!itemToDraw)
        {
            //itemToDraw = new QGraphicsLineItem(this);
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            itemToDraw->setPos(origPoint);
        }
        itemToDraw->setLine(0,0,event->scenePos().x() - origPoint.x(),event->scenePos().y() - origPoint.y());
    }
//    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

