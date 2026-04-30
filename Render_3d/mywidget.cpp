#include "mywidget.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
#include <QMouseEvent>
#include <QLabel>
#include <qdebug.h>

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

    if(selectedTool==1)
    {
        qDebug() << "vector size:" <<vec.size();
        int x1,y1;
        for(int i=0;i<vec.size();i+=2) {

            //draw a point
            x1 = vec[i];
            y1 =vec[i+1];
            QPainter painter(this);
            painter.setBrush(QBrush(Qt::yellow));
            painter.setPen(QPen(Qt::yellow));

            painter.drawEllipse(QPointF(x1,y1), rad, rad);

        }


    } else {

        qDebug()<<"Dwdjhwdqh";
        int mx,my;
        for(int i=0;i<vec.size();i+=2) {
            //draw a point
            mx = vec[i];
            my = vec[i+1];
            int x1 = mx - rad;
            int x2 = mx + rad;
            int y1 = my - rad;
            int y2 = my + rad;
            double inc = 1;

            for (int _x = x1, deltax = -rad; _x <= x2; _x+=inc, deltax+=inc)
            {
                for (int _y = y1, deltay = -rad; _y <= y2; _y+=inc,deltay+=inc)
                {
                    float dist = sqrtf(deltax*deltax + deltay*deltay);

                    if (dist<rad) {

                        QPainter painter(this);
                        painter.setBrush(QBrush(Qt::green));
                        painter.setPen(QPen(Qt::green));
                        painter.drawPoint(_x,_y);

                    }

                }

            }

        }

    }

    QVTKWidget::paintEvent(event);

}


void MyWidget::mousePressEvent(QMouseEvent *event)

{

    x=event->x();
    y=event->y();
    m_pressed = true;

    QVTKWidget::mousePressEvent(event);

}


void MyWidget::mouseReleaseEvent(QMouseEvent *event)

{

    x=event->x();
    y=event->y();
    vec.clear();
    update();
    m_pressed = false;

    QVTKWidget::mouseReleaseEvent(event);

}


void MyWidget::mouseMoveEvent(QMouseEvent *event)

{
    if (m_pressed) {

        x=event->x();
        y=event->y();
        vec.push_back(x);
        vec.push_back(y);
        update();
    }

    QVTKWidget::mouseMoveEvent(event);
}
