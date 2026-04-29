#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPaintEvent>

class paintscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit paintscene(QObject *parent = 0);
    ~paintscene();

private:
    QPointF previousPoint;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
