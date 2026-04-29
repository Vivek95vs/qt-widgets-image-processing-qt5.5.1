#include "mywidget.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QVTKWidget(parent)
{
    x=100;
    y=100;
    m_pressed = false;
}

MyWidget::~MyWidget()
{

}

void MyWidget::paintEvent(QPaintEvent *event)
{
    qDebug()<<"Entering-----drawellipse";

    if(selectedTool==1)
    {
        qDebug() << "vector size:" <<vec.size();
        int x1,y1;
        for(int i=0;i<vec.size();i+=2)
        {
            //draw a point
            x1 = vec[i];
            y1 = vec[i+1];
            QPainter painter(this);
//            QPainterPath paint;
            painter.setBrush(QBrush(Qt::yellow));
            painter.setPen(QPen(Qt::yellow));

            painter.drawEllipse(QPointF(x1,y1), rad, rad);
//            paint.addEllipse(QPointF(x1,y1), rad, rad);
        }
    }

    if(selectedTool==2)
    {
        QRectF rect(10.0,20.0,80.0,60.0);
        QPainter painter(this);
        painter.setBrush(QBrush(Qt::green));
        painter.setPen(QPen(Qt::green));
        painter.drawRect(rect);

    }

    QVTKWidget::paintEvent(event);
}


void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"MousePress";
    x=event->x();
    y=event->y();
    m_pressed = true;

    QVTKWidget::mousePressEvent(event);
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"MouseMove";
    if (m_pressed) {

        x=event->x();
        y=event->y();
        vec.push_back(x);
        vec.push_back(y);
        update();
    }

    QVTKWidget::mouseMoveEvent(event);
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"MouseRelease";

    x=event->x();
    y=event->y();
    vec.clear();
    update();
    m_pressed = false;

    QVTKWidget::mouseReleaseEvent(event);
}
