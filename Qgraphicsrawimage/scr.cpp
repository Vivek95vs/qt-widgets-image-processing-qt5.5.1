#include "scr.h"

scr::scr(QWidget* parent=0):QGraphicsView(parent)
{

}


void scr::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scalefactor=1.5;
    if(event->delta()>0)
    {
        scale(scalefactor,scalefactor);
    }
    else{
        scale(1/scalefactor,1/scalefactor);
    }
}
