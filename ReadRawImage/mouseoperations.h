#ifndef MOUSEOPERATIONS_H
#define MOUSEOPERATIONS_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QtDebug>

class MouseOperations : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MouseOperations(QObject *parent = 0);

    QPointF firstPoint , lastpoint;
    bool mousepressed;
    QGraphicsLineItem *line = NULL;
    QGraphicsTextItem *text;
    QGraphicsRectItem *rectangle = NULL;
    QGraphicsEllipseItem *ellipse = NULL;
    QGraphicsPolygonItem *polygon = NULL;
    QGraphicsPathItem *brushTool = NULL;
    QList <QGraphicsItem*> selectedLineList;
    QList <QGraphicsPathItem*> selectedPathItem;
    QList <QGraphicsItem*> graphicsItems;
    QList <QGraphicsPathItem*> graphicsPathItems;
    QGraphicsItemGroup *lineTextGroup;
    QPainterPath *Val;
    QPolygonF polygonPoint;
    double dist, pixPitch;
    enum itemsEnum {drawLine, drawRectangle, drawEllipse, drawPolygon, brushTools,otherOperations};
    int mode;

    void setMode(int number);
    void selectLine();
    void deleteAllGraphicsItems();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);


signals:
//    void UpdateDrawing(QGraphicsItem *lineTextGroup, QGraphicsItem *rectangle);
//    void UpdateDrawing(QList <QGraphicsItem*> graphicsItems);

public slots:
};

#endif // MOUSEOPERATIONS_H
