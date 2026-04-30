 #include "mouseoperations.h"

MouseOperations::MouseOperations(QObject *parent) : QGraphicsScene(parent)
{

}

void MouseOperations::setMode(int number)
{
    mode = number;
}

void MouseOperations::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"PressEvent Start"<<endl;
    mousepressed = true;
    firstPoint = event->scenePos(); //to capture the x,y coordinate on first mouse click
//    qDebug()<<"firstPoint "<<firstPoint<<endl;
    switch (mode)
    {
    case otherOperations:
        break;

    case drawLine:
        firstPoint = event->scenePos();
        break;

    case drawRectangle:
        firstPoint = event->scenePos();
        break;

    case drawEllipse:
        firstPoint = event->scenePos();
        break;

    case drawPolygon:
        if(event->buttons() & Qt::LeftButton)
        {
            if(!polygon)
            {
                polygon = new QGraphicsPolygonItem();
                this->addItem(polygon);
                firstPoint = event->scenePos();
                polygonPoint.append(firstPoint);
            }
//            polygon->setFlag(QGraphicsItem::ItemIsSelectable, true);
            QPen polygonPen(Qt::blue, 10, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
            polygon->setPen(polygonPen);
            polygon->setPolygon(polygonPoint);
            graphicsItems.append(polygon);
        }
        else if (event->buttons() & Qt::RightButton) {
            break;
        }

        break;

    case brushTools:

        firstPoint = event->scenePos();
        break;

    }    
//    qDebug()<<"PressEvent End"<<endl;

    QGraphicsScene::mousePressEvent(event);
}

void MouseOperations::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"MoveEvent Start"<<endl;
    if(mousepressed == false)
        return;

    switch (mode)
    {
    case otherOperations:
        break;

    case drawLine:
//        qDebug()<<"Line drawing...";
        if(event->buttons() & Qt::LeftButton)
        {
            if(!line)
                {
    //              allowcate memory for line object
                    line = new QGraphicsLineItem(); //item to define to display the line in the Scene
                    line->setPos(firstPoint); //setting the previous position of mouse click
                    this->addItem(line);
                    QPen linePen(Qt::red, 3, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
                    line->setPen(linePen);

    //                pixel pitch calcualtions
    //                float x = powf((event->scenePos().x() - firstPoint.x()),2);//to find the distance between two points
    //                float y = powf((event->scenePos().y() - firstPoint.y()),2);
    //                float dist = powf(x+y,0.5); //line distance = Squ((x2-x1)^2 + (y2-y1)^2)

    //              allowcate memory for text object
                    text = new  QGraphicsTextItem();

    //              set the properties for the text
                    QPen textPen(Qt::blue, 5);
                    QFont serifFont("Times",(40),QFont::Thin);
                    text->setFont(serifFont);
                    text->setPos(firstPoint);
                    this->addItem(text);
//                    qDebug()<<"Distance....."<<(dist*(pixPitch)/10)<<endl;

                }
            line->setLine(0,0,event->scenePos().x()-firstPoint.x(),event->scenePos().y()-firstPoint.y()); //Line displayed while moving the mouse
                                                                                                          //(current position - previous position)
//                line->setFlag(QGraphicsItem::ItemIsSelectable, true); //setting the drawn line as selectable

//                pixel pitch calcualtions
            dist = sqrt(pow(event->scenePos().x()- firstPoint.x() - 0, 2) +
                             pow(event->scenePos().y()- firstPoint.y() - 0, 2));
            pixPitch = ((921.0/1690.0)*0.139);// (0.07) calculating pixel pitch
                                              //921.0->Source to Object distance
                                              //1690.0->Source to detector distance
                                              //varian detector pixel pitch

            text->setPlainText((QString::number(dist*(pixPitch)/10,'f',2)+" cm"));

//                text->setFlag(QGraphicsItem::ItemIsSelectable, true); //setting the drawn line as selectable

        }

        break;

    case drawRectangle:

//        qDebug()<<"drawRectangle...";
        if(event->buttons() & Qt::LeftButton)
        {
            if(!rectangle)
            {
                rectangle = new QGraphicsRectItem();
//                rectangle->setPos(firstPoint);
                this->addItem(rectangle);
                rectangle->setFlag(QGraphicsItem::ItemIsSelectable, true);
                QPen rectanglePen(Qt::yellow, 10, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
                rectangle->setPen(rectanglePen);
            }

            rectangle->setRect(firstPoint.x(),firstPoint.y(),event->scenePos().x()-firstPoint.x(),event->scenePos().y()-firstPoint.y());

        }
        break;

    case drawEllipse:
//        qDebug()<<"drawEllipse...";
        if(event->buttons() & Qt::LeftButton)
        {
            if(!ellipse)
            {
                ellipse = new QGraphicsEllipseItem();
                this->addItem(ellipse);
                ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
                QPen ellipsePen(Qt::blue, 10, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
                ellipse->setPen(ellipsePen);
            }
            ellipse->setRect(firstPoint.x(),firstPoint.y(),event->scenePos().x()-firstPoint.x(),event->scenePos().y()-firstPoint.y());

        }
        break;

    case drawPolygon:
         break;

    case brushTools:
        if(event->buttons() & Qt::LeftButton)
        {
            if(!brushTool)
            {
                brushTool = new QGraphicsPathItem();
                this->addItem(brushTool);
               Val=new QPainterPath();
                brushTool->setPos(firstPoint);
                brushTool->setFlag(QGraphicsItem::ItemIsSelectable, false);
                QPen brushPen(Qt::blue, 25, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
//                QBrush useBrush(Qt::yellow); //defning the colour and font of the line
//                useBrush.setStyle(Qt::SolidLine);
                brushTool->setPen(brushPen);
            }
            Val->lineTo(event->scenePos().x()-firstPoint.x(),event->scenePos().y()-firstPoint.y());
            brushTool->setPath(*Val);
        }

        break;
    }
//    qDebug()<<"MoveEvent Ends"<<endl;
    QGraphicsScene::mouseMoveEvent(event);
}

void MouseOperations::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"ReleaseEvent Start"<<endl;
    lastpoint = event->scenePos();
//    qDebug()<<"lastpoint"<<lastpoint;
    mousepressed = false;

    switch (mode) {
    case otherOperations:
        break;

    case drawLine:
//        qDebug()<<"Line Button Selected...";
        lastpoint = event->scenePos();
        break;

    case drawRectangle:
//        qDebug()<<"Rectangle Selected...";
        lastpoint = event->scenePos();
        graphicsItems.append(rectangle);
//        rectangle = NULL;
        break;

     case drawEllipse:
//        qDebug()<<"Ellipse Selected...";
        lastpoint = event->scenePos();
        graphicsItems.append(ellipse);
//        ellipse = NULL;
        break;

    case drawPolygon:
//        lastpoint = event->scenePos();
////        qDebug()<<"lastpoint"<<lastpoint;
//        polygonPoint.append(lastpoint);
////        qDebug()<<"polygonPoint"<<polygonPoint;
        polygon->setFlag(QGraphicsItem::ItemIsSelectable, true);
//        QPen polygonPen(Qt::blue, 10, Qt::SolidLine,Qt::RoundCap); //defning the colour and font of the line
//        polygon->setPen(polygonPen);
//        polygon->setPolygon(polygonPoint);
//        graphicsItems.append(polygon);
       break;

    case brushTools:
        if(firstPoint == lastpoint)
            return;
         brushTool->setFlag(QGraphicsPathItem::ItemIsSelectable,true);
         graphicsPathItems.append(brushTool);

        break;
    }

     QGraphicsItemGroup *lineTextGroup = new QGraphicsItemGroup();

    if(mode!= otherOperations && line){
  //                Grouping the Line and text

            lineTextGroup->addToGroup(line);
            lineTextGroup->addToGroup(text);
            this->addItem(lineTextGroup);
            lineTextGroup->setFlag(QGraphicsItem::ItemIsSelectable, true);
//            qDebug()<<"lineTextGroup"<<lineTextGroup;
            graphicsItems.append(lineTextGroup);
    }    
    if(line)
        line = NULL;

    if(rectangle)
        rectangle = NULL;

    if(ellipse)
        ellipse = NULL;

    if(polygon)
        polygon = NULL;

    if(brushTool)
        brushTool = NULL;

//    qDebug()<<"ReleaseEvent Ends"<<endl;

    QGraphicsScene::mouseReleaseEvent(event);
}

void MouseOperations::wheelEvent(QWheelEvent *event)
{
//    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

//    double scaleFactor = 1.15;

//    if(event->delta() > 0)
//    {

//        scale(scaleFactor, scaleFactor);

//    }
//    else
//    {
//        scale(1/scaleFactor, 1/scaleFactor);
//    }
}

void MouseOperations::selectLine()
{
    qDebug()<<"selectedLineList......";
    selectedLineList = this->selectedItems();

//    Deleting the items selected in the Graphics scene
    for (int i = 0;i<selectedLineList.length();i++)
        {
            this->removeItem(selectedLineList[i]);
        }
    for (int i = 0;i<selectedPathItem.length();i++)
        {
            this->removeItem(selectedPathItem[i]);
        }
}

void MouseOperations::deleteAllGraphicsItems()
{    
    for(int i=0; i<graphicsItems.length();i++)
    {
        this->removeItem(graphicsItems[i]);

    }
    for(int i=0; i<graphicsPathItems.length();i++)
    {
        this->removeItem(graphicsPathItems[i]);

    }
    qDebug()<<"graphicsItems"<<graphicsItems;
    graphicsItems.clear();
    polygonPoint.clear();



}



















