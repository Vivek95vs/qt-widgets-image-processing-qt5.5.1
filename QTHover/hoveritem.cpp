#include "hoveritem.h"

Hoveritem::Hoveritem()
{

}

void Hoveritem::hoverEnter(QGraphicsSceneHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
    repaint();

}

void Hoveritem::hoverLeave(QGraphicsSceneHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(false);
    this->setFont(font);
    repaint();
}

void Hoveritem::hoverMove(QGraphicsSceneHoverEvent *event)
{
    QFont font = this->font();
    font.setBold(true);
    this->setFont(font);
    repaint();
}

bool Hoveritem::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        qDebug()<<"Entering hover";
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
//    return QGraphicsSceneHoverEvent::event(event);
}

