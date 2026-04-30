#ifndef MOUSEOPERATION_H
#define MOUSEOPERATION_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QtDebug>

class MouseOperation : public QGraphicsScene
{
    Q_OBJECT
public:
    MouseOperation();
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleseEvent(QGraphicsSceneMouseEvent *ev);

    QPointF firstPoint, lastPoint;
    bool mouseRelesed;   

};

#endif // MOUSEOPERATION_H
