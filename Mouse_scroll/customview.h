#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

class customview : public QGraphicsView
{
public:
    customview(QWidget *parent=0);

protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // CUSTOMVIEW_H
