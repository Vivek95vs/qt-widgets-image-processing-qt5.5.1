#include "mysquare.h"
#include <QDebug>
#include <QGraphicsScene>


mySquare::mySquare()
{
    pressed  = false;
    //setFlag(ItemIsMovable);
    selectedTool = 1;
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);
}

QRectF mySquare::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void mySquare::paintEvent(QPaintEvent *event)
{
    //painter->begin(this);
    QPen pen(Qt::red);
    painter->setPen(pen);
    //painter->setPen(Qt::blue);
    //QRectF rec = boundingRect();
    if(pressed)
    {
       // painter->drawPixmap();
        painter->drawPixmap(0,0,mPix);

        painter->drawRect(mRect);
        drawStarted = true;
    }
    else if (drawStarted)
    {
        QPainter tempPainter(&mPix);
        tempPainter.drawRect(mRect);
        painter->drawPixmap(0,0,mPix);
    }
}

void mySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;

    y = event->pos();
    qDebug()<<"Pos X : "<<y.x() <<endl;
    qDebug()<<"Pos Y : "<<y.y() <<endl;

    if(selectedTool == 1)
    {
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());

        X_1 = mRect.x();
        //X_1 = 400 - X_1;
        Y_1 = mRect.y();
        //Y_1 = 600 - Y_1;
        Y_2 = Y_1;
        X_3 = X_1;
        qDebug() << "Value of x_start axis " << X_1 <<endl;
        qDebug() << "Value of y_start axis " << Y_1 <<endl;
    }
    else if (selectedTool == 2)
    {

    }

    QGraphicsScene::mousePressEvent(event);
}

void mySquare::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"Inside mouseMoveEvent \n";
    if(event->type() == QEvent::MouseMove)
    {
        if(selectedTool == 1){
            mRect.setBottomRight(event->pos());
        }
        else if (selectedTool == 2){
            //mLine.setP2(event->pos());
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void mySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    qDebug()<<"Inside mouseReleaseEvent \n";
    QGraphicsScene::mouseReleaseEvent(event);
}
