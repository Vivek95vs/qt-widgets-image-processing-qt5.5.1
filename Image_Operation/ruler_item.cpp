#include "ruler_item.h"
#include <QDebug>

float imaginPixelSpacing=1;
int rulerMode;

Ruler_Item::Ruler_Item()
{
    pressed=false;
//    setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
}

QRectF Ruler_Item::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void Ruler_Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Mode=rulerMode;

    if(Mode==1)

        //Horizontal Mode
    {
        dpi=width/*/17*/;
        qreal dpcm=dpi/3.1;
        QPixmap rulerCache(dpcm,dpcm/4);
        rulerCache.fill();
        qreal dpmm=dpcm/10;
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        qreal lineWidth=dpmm/5;
        qreal xpos=/*width/4+*/lineWidth/2;
        qDebug()<<"xpos"<<xpos;
        qDebug()<<"dpi"<<dpi;
        qDebug()<<"dpcm"<<dpcm;
        qDebug()<<"dpmm"<<dpmm;
        qDebug()<<"linewidth"<<lineWidth;
        qDebug()<<"ruler Cache"<<rulerCache.height();
//        dpmm = (width*0.099739)/50;
        qreal y=/*width/2*/0;
        int iter=ceil(width*imaginPixelSpacing)+1;
        for(int i=0;i<iter;i++)
        {
            painter->setPen(QPen(Qt::darkGreen,imaginPixelSpacing*5));
            if(!(i%10))
            {
                painter->drawLine(xpos,y,xpos,y+rulerCache.height());
                qDebug()<<"hiii";
                QFont font=painter->font();
                font.setPointSizeF(3);
                painter->setPen(QPen(Qt::red,1));
                painter->setFont(font);

                if(i==0)
                {
//                    qDebug()<<"go";
                    painter->drawText(QRectF(xpos,y+rulerCache.height()+1,4,5),QString::number(i/10));
                }
                else if(i<100)
                {
//                    qDebug()<<"hello";
                    painter->drawText(QRectF(xpos-1.25,y+rulerCache.height()+1,4,5),QString::number(i/10));
                }
                else
                {
//                    qDebug()<<"hhhhh";
                    painter->drawText(QRectF(xpos-2,y+rulerCache.height()+1,4,5),QString::number(i/10));
                }
            }
            else if(!(i%5))
            {
//                qDebug()<<"jhjhshh";
                painter->drawLine(xpos,y,xpos,y+rulerCache.height()/2);
                xpos=xpos+dpmm;
            }
        }
//        xpos=0;
    }
    else if(Mode==0)
    {
        //Vertical
        dpi=width/*/17*/;
        qreal dpcm=dpi/3.1;
        QPixmap rulerCache(dpcm,dpcm/4);
        rulerCache.fill();
        qreal dpmm=dpcm/10;
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        qreal lineWidth=dpmm/5;

        qreal xpos=/*width/4+*/lineWidth/2;
        qreal y=/*width/2*/0;
//        xpos=0;
//        y=0;
//        dpmm=1;
        int iter=ceil(width*imaginPixelSpacing)+1;
        for(int i=0;i<iter;i++)
        {
            painter->setPen(QPen(Qt::darkGreen,imaginPixelSpacing*5));
            if(!(i%10))
            {
                painter->drawLine(y,xpos,y+rulerCache.height(),xpos);

                QFont font=painter->font();
                font.setPointSizeF(3);
                painter->setPen(QPen(Qt::darkGreen,1));
                painter->setFont(font);

                if(i==0)
                {
                    painter->drawText(QRectF(y+rulerCache.height()+1,xpos,5,4),QString::number(i/10));
                }
                else if(i<100)
                {
                    painter->drawText(QRectF(y+rulerCache.height()+1,xpos-1.25,5,4),QString::number(i/10));
                }
                else
                {
                    painter->drawText(QRectF(y+rulerCache.height()+1,xpos-2,5,4),QString::number(i/10));
                }
            }
            else if(!(i%5))
            {
                painter->drawLine(y,xpos,y+rulerCache.height()/2,xpos);
                xpos=xpos+dpmm;
            }
        }
        xpos=0;

    }
}

void Ruler_Item::setwidthHeight(int wid, int hei, int mod)
{
    width=wid;
    height=hei;
    Mode=mod;
}

