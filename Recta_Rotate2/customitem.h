#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include <QDebug>

class customitem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    customitem();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
    void itemChanged(QPointF);
};

#endif // CUSTOMITEM_H
