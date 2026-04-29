#ifndef CUSTOMITEMELLIPSE_H
#define CUSTOMITEMELLIPSE_H
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include <QDebug>

class CustomItemEllipse: public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    CustomItemEllipse();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
    void itemChanged(QPointF);
};

#endif // CUSTOMITEMELLIPSE_H
