// myitem.cpp

#include "myitem.h"
#include <QDebug>
//extern int mammo;
extern float imaginPixelSpacing;

extern int rulerMode;

myitem::myitem()
{
    Pressed = false;
    setFlag(ItemIsMovable);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);

}

QRectF myitem::boundingRect() const
{
    // outer most edges
    return QRectF(0,0,width,height);

}


void myitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//        qreal dpi=90;
    Mode = rulerMode;

    if(Mode==1)
    {
//        //Horizontal
//        if(mammo==1)
//            dpi=width/9; //mammo detector
//        else
        dpi=width/17; //varian detector
        qreal dpcm = dpi / 2.54;
        QPixmap rulerCache(dpcm, dpcm / 4);
        rulerCache.fill();
        qreal dpmm = dpcm / 10;
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        qreal lineWidth = dpmm / 5;

        qreal xpos = width/4+lineWidth / 2;

        qreal y=width/2;
        xpos=0;//added
        y=0;//added
        dpmm=1;
        int iter = ceil(width*imaginPixelSpacing)+1;
        qDebug()<<"iter"<<iter;
        //dpmm = (width*0.099739)/50;
        for (int i = 0; i < iter; ++i) {
            painter->setPen(QPen(Qt::cyan,imaginPixelSpacing*5));
            if (!(i%10)){

            painter->drawLine(xpos, y, xpos, y+rulerCache.height());
            qDebug()<<"xpos:"<<xpos<<y<<y+rulerCache.height();

            QFont font = painter->font();
            font.setPointSizeF(3);
            painter->setPen(QPen(Qt::cyan,1));
            painter->setFont(font);

            if (i==0){
            painter->drawText(QRectF(xpos,y+rulerCache.height()+0.5,4,5),QString::number(i/10));
            qDebug()<<"xpos1:"<<xpos<<y<<y+rulerCache.height()<<QString::number(i/10);
            }
            else if (i<100){
            painter->drawText(QRectF(xpos-1.25,y+rulerCache.height()+0.5,4,5),QString::number(i/10));
            qDebug()<<"xpos2:"<<xpos<<y<<y+rulerCache.height()<<QString::number(i/10);
            }
            else{
            painter->drawText(QRectF(xpos-2,y+rulerCache.height()+0.5,4,5),QString::number(i/10));
            qDebug()<<"xpos3:"<<xpos<<y<<y+rulerCache.height()<<QString::number(i/10);
            }

            }
            else if (!(i%5)) painter->drawLine(xpos, y, xpos, y+rulerCache.height() / 2);
            xpos += dpmm;
            qDebug()<<"xpos4:"<<xpos<<y<<y+rulerCache.height()/2;
        }

        xpos=0; //added
    }
    else if(Mode==0)
    {
            dpi=width/17; //varian detector
        qreal dpcm = dpi / 2.54;
        QPixmap rulerCache(dpcm, dpcm / 4);
        rulerCache.fill();
        qreal dpmm = dpcm / 10;
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        qreal lineWidth = dpmm / 5;
        qreal xpos = width/4+lineWidth / 2;
        qreal y=width/2;



        /*added*/
        xpos=0;//added
        y=0;//added
        dpmm=1;
        int iter = ceil(width*imaginPixelSpacing)+1;
       // dpmm = (width*0.099739)/50;
        for (int i = 0; i < iter; ++i) {
         painter->setPen(QPen(Qt::cyan, imaginPixelSpacing*5));
        //for (int i = 0; i < 51; ++i) {
            if (!(i%10))
            {
             painter->drawLine(y,xpos, y+rulerCache.height(),xpos);

             QFont font = painter->font();
             font.setPointSizeF(3);
             painter->setPen(QPen(Qt::cyan,1));
             painter->setFont(font);

             if (i==0)
             {
//             painter->rotate(-90);
             painter->drawText(QRectF(y+rulerCache.height()+1,xpos,5,4),QString::number(i/10));
//             painter->rotate(90);
             }
             else if (i<100)
             {

             painter->drawText(QRectF(y+rulerCache.height()+1,xpos-1.25,5,4),QString::number(i/10));

             }
             else
             {
             painter->drawText(QRectF(y+rulerCache.height()+1,xpos-2,5,4),QString::number(i/10));
             }

            }
            else if (!(i%5)) painter->drawLine(y,xpos , y+rulerCache.height() / 2, xpos);
            xpos += dpmm;
        }
        xpos=0; //added
    }
}

void myitem::setWidthHeight(int wid, int hei, int mod)
{
    width=wid;
    height=hei;
    Mode = mod;
}




