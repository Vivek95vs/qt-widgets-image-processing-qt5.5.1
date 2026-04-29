#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsLineItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit Scene(QObject* parent = 0);
    enum Mode{NoMode, SelectObject, DrawLine,RectLine};
    void setMode(Mode mode);
    ~Scene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int sceneMode;
    QPointF origPoint;
    //QGraphicsView* mView;
    QGraphicsLineItem *itemToDraw;
    void makeItemsControllable(bool areControllable);
};

#endif // SCENE_H
