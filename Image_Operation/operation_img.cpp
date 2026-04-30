#include "operation_img.h"
#include "ui_operation_img.h"
#include <QKeyEvent>
#include "QMenu"

extern float imaginPixelSpacing;
extern int rulerMode;
double ValueDia;
operation_Img::operation_Img(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operation_Img)
{
    ui->setupUi(this);
    Evt=new Disp_Evt();
    itemRuler=new Ruler_Item();

    ui->widget->hide();

    qDebug()<<"QT version"<<QT_VERSION_STR;

    connect(Evt,SIGNAL(positionLeftchanges()),this,SLOT(changedLeftPos()));
    connect(Evt,SIGNAL(positionRightchanges()),this,SLOT(changedRightPos()));
    connect(Evt,SIGNAL(positionUpchanges()),this,SLOT(changedUpPos()));
    connect(Evt,SIGNAL(positionDownchanges()),this,SLOT(changedDownPos()));
    connect(Evt,SIGNAL(sendtohide()),this,SLOT(receivetohide()));


    QMenu *Erasetool = new QMenu;
    Left = new QAction(tr("&Lt"), ui->pushButton);

    Right = new QAction(tr("&Rt"), ui->pushButton);

    Erasetool->addAction(Left);
    Erasetool->addAction(Right);


    connect(Left, &QAction::triggered, this, &operation_Img::on_Left_clicked);
    connect(Right, &QAction::triggered, this, &operation_Img::on_Right_clicked);

    ui->pushButton->setMenu(Erasetool);

}

operation_Img::~operation_Img()
{
    delete ui;
}


void operation_Img::on_PB_LoadImage1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/RAD/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[w*h];
    fread(Image,1,w*h*sizeof(unsigned short),Img);
//    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((Image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    Evt = new Disp_Evt();
    view = new QGraphicsView(Evt);
    //Evt->setSceneRect(200,200,1536,1536);
    ui->graphicsView->setScene(Evt);
    //item->setPos(1536-200,1536-200);

   // ui->graphicsView->setSceneRect(-200,400,100,100);
    ui->graphicsView->fitInView(item,Qt::IgnoreAspectRatio);
    Evt->addItem(item);

}

void operation_Img::on_PB_LoadImage2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/RAD/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img1;
    Img1= fopen(filename.toStdString().c_str(),"rb");
    unsigned short* Image1=new unsigned short[w*h];
    fread(Image1,1,w*h*sizeof(unsigned short),Img1);
//    unsigned char* arr1=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr1[i]=((Image1[i]*255)/65535);
    }
    myImage1=QImage(arr1,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage1));
    Evt = new Disp_Evt();

    view = new QGraphicsView();
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    Evt->addItem(item);
}

void operation_Img::on_PB_Overlay_clicked()
{
    //Overlay
    arr2=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
            arr2[i]=((arr[i])+(arr1[i]));
    }
    QImage myImage2(arr2,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
    Evt = new Disp_Evt();
    view = new QGraphicsView();
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item);
    Evt->addItem(item);

    //Overlay
//      QPixmap px1=QPixmap::fromImage(myImage);
//      QPixmap px2=QPixmap::fromImage(myImage1);

//      QPixmap px(px1.width(),px1.height());
//      px.fill(Qt::transparent);
//      QPainter painter(&px);
//      painter.drawPixmap(0,0,px1);
//      painter.drawPixmap(w,h,px2);

//        QPixmap px1=QPixmap::fromImage(myImage);
//        QPixmap px2=QPixmap::fromImage(myImage1);


//      scene=new QGraphicsScene();
//      item3=scene->addPixmap(0,0,px1);
//      item3->setPos(w,h);
//      view3=new QGraphicsView(scene);
//      ui->graphicsView3->setScene(scene);
//      ui->graphicsView3->fitInView(item3,Qt::KeepAspectRatio);
//      scene->addItem(item3);
}

void operation_Img::on_PB_Quadrant_clicked()
{
    //    Quadrant

    QPixmap px1=QPixmap::fromImage(myImage.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    QPixmap px2=QPixmap::fromImage(myImage1.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    Evt = new Disp_Evt();
    item=Evt->addPixmap(px1.copy(0,0,w/2,h/2));
    item->setPos(0,0);
    item=Evt->addPixmap(px1.copy(w/2,h/2,w/2,h/2));
    item->setPos(w/2,h/2);
    item=Evt->addPixmap(px2.copy(w/2,0,w/2,h/2));
    item->setPos(w/2,0);
    item=Evt->addPixmap(px2.copy(0,h/2,w/2,h/2));
    item->setPos(0,h/2);
    view = new QGraphicsView(Evt);
    ui->graphicsView->setScene(Evt);
    Evt->setSceneRect(0,0,w,h);
//        scene->addItem(item3);
}

void operation_Img::on_PB_CheckerBoard_clicked()
{
    //Checker board

    myImage=myImage.convertToFormat(QImage::Format_ARGB32);
    int n=10;
    int s=myImage.width();
    int sc=ceil((s/n));
    int s1=myImage.height();
    int sc1=ceil((s1/n));

    for (int i = 0;i<n;++i)
    {
       for(int j = 0;j<n;++j)
       {
           if ((i+j)%2==0)
             {
               for (int k = (j)*sc1;k<(j+1)*sc1;k++)
               {
                  for (int l = (i)*sc;l<(i+1)*sc;l++)
                  {
                            myImage.setPixel(l,k,qRgba(0,0,0,0));

                  }
               }
           }
       }
    }

    QPixmap px3=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px4=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    Evt=new Disp_Evt();
    p1=Evt->addPixmap(px4.copy(0,0,w,h));
    p2=Evt->addPixmap(px3.copy(0,0,w,h));
    view=new QGraphicsView();
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(p1);
}

void operation_Img::on_PB_Toggle_clicked()
{
    QPixmap px1=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px2=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    Evt=new Disp_Evt();
    p1=Evt->addPixmap(px1.copy(0,0,w,h));
    p2=Evt->addPixmap(px2.copy(0,0,w,h));
    p2->setFlag(QGraphicsItem::ItemIsMovable);

    if(ui->PB_Toggle->isChecked())
    {

        view=new QGraphicsView(Evt);
        ui->graphicsView->setScene(Evt);
        Evt->setSceneRect(0,0,w,h);
        p2->setOpacity(0);
        ui->graphicsView->fitInView(p1);
    }
    else
    {
        view=new QGraphicsView(Evt);
        ui->graphicsView->setScene(Evt);
        Evt->setSceneRect(0,0,w,h);
        p1->setOpacity(1);
        ui->graphicsView->fitInView(p2);

    }
}

void operation_Img::on_PB_Rectangle_clicked()
{
    Evt->selectedTool=1;
}

void operation_Img::on_PB_Ellipse_clicked()
{
    ui->widget->show();

    Evt->selectedTool=2;

}

void operation_Img::on_PB_FreeHand_clicked()
{
    Evt->selectedTool=3;
}

void operation_Img::on_PB_Delete_clicked()
{
    QList<QGraphicsItem *>Items=Evt->selectedItems();
    foreach(QGraphicsItem *item, Items)
    {
               Evt->removeItem(item);
               delete(item);

    }
}

void operation_Img::on_PB_Clearall_clicked()
{
    Evt->clear();
}

void operation_Img::on_PB_RectChange_clicked()
{
//    Evt->rect->setFlag(QGraphicsRectItem::ItemIsSelectable);
//    Evt->rect->setFlag(QGraphicsRectItem::ItemIsMovable);

    Evt->selectedTool=4;
}

void operation_Img::changedLeftPos()
{
    item->setPos(item->x()-10,item->y());
}

void operation_Img::changedRightPos()
{
    item->setPos(item->x()+10,item->y());
}

void operation_Img::changedUpPos()
{
    item->setPos(item->x(),item->y()-10);
}

void operation_Img::changedDownPos()
{
    item->setPos(item->x(),item->y()+10);
}

void operation_Img::receivetohide()
{
    qDebug()<<"hide";
    ui->widget->hide();
}

void operation_Img::on_PB_HorizRuler_clicked()
{
    rulerMode=1;
    if(ui->PB_HorizRuler->isChecked())
    {
        Evt->addItem(itemRuler);
//        itemRuler->setFlag(QGraphicsItem::ItemIsMovable,false);
        itemRuler->setPos(1,0);
        itemRuler->setScale(1/imaginPixelSpacing);
//        if(dMode==1)
//        {
            itemRuler->setwidthHeight(3072,3072,0);
        qDebug()<<"amode";
//        }
//        else
//        {
//            itemRuler->setwidthHeight(1536,1536,0);
//            qDebug()<<"bmode";
//        itemRuler->setRotation(0);
//        }
     }
    else
    {
        qDebug()<<"cmode";
        Evt->removeItem(itemRuler);
    }
    qApp->processEvents();
}

void operation_Img::on_PB_VertiRuler_clicked()
{
    rulerMode = 0;

    if(ui->PB_VertiRuler->isChecked())
    {
        Evt->addItem(itemRuler);
//        itemRuler->setFlag(QGraphicsItem::ItemIsMovable,false);
        itemRuler->setPos(1,0);
        itemRuler->setScale(1/imaginPixelSpacing);
//        if(dMode==1)
//        {
        qDebug()<<"dmode";
            itemRuler->setwidthHeight(3072,3072,0);
//        }
//        else
//        {
//            itemRuler->setwidthHeight(1536,1536,0);
//        itemRuler->setRotation(0);
//        }

    }
    else
    {
         qDebug()<<"Vertical Unchecked";
        Evt->removeItem(itemRuler);
    }
    qApp->processEvents();
}

void operation_Img::on_PB_Image_clicked()
{
    qDebug()<<"arr2"<<arr2[4];
    QImage myImage2(arr2,3072,3072,QImage::Format_Grayscale8);

    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
    Evt = new Disp_Evt();
    view = new QGraphicsView();
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item);
    Evt->addItem(item);
}

void operation_Img::on_lineEdit_textChanged(const QString &arg1)
{
    ValueDia= arg1.toDouble()*100;
    qDebug()<<"value dia----"<<ValueDia;
}

void operation_Img::syncPositions()
{
    for (auto it = textItemMap.begin(); it != textItemMap.end(); ++it) {
        QList<TextItemData>& items = it.value();

        for (QGraphicsItem* item : Evt->items()) {
            QGraphicsTextItem* textItem = dynamic_cast<QGraphicsTextItem*>(item);
            if (!textItem) continue;

            int id = textItem->data(0).toInt();
            for (TextItemData &data : items) {
                if (data.id == id) {
                    data.pos = textItem->pos();  // update stored position
                }
            }
        }
    }
}

void operation_Img::on_Left_clicked()
{

    if (!Evt) return;

       QGraphicsTextItem* textItem = Evt->addText("L", QFont("Arial", 40, QFont::Bold));
       textItem->setDefaultTextColor(Qt::red);
       textItem->setPos(100 + textItemMap[1].size() * 50, 100);
       textItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

       // Assign a unique ID
       int id = nextId++;
       textItem->setData(0, id);

       // Save essential data
       TextItemData data;
       data.id = id;
       data.text = textItem->toPlainText();
       data.font = textItem->font();
       data.color = textItem->defaultTextColor();
       data.pos = textItem->pos();

       textItemMap[1].append(data);

       qDebug() << "Added Left, total size =" << textItemMap[1].size();

}

void operation_Img::on_Right_clicked()
{
    if (!Evt) return;

    QGraphicsTextItem* textItem = Evt->addText("R", QFont("Arial", 40, QFont::Bold));
    textItem->setDefaultTextColor(Qt::red);
    textItem->setPos(100 + textItemMap[1].size() * 50, 100);
    textItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    // Assign a unique ID
    int id = nextId++;
    textItem->setData(0, id);

    // Save essential data
    TextItemData data;
    data.id = id;
    data.text = textItem->toPlainText();
    data.font = textItem->font();
    data.color = textItem->defaultTextColor();
    data.pos = textItem->pos();

    textItemMap[1].append(data);

    qDebug() << "Added Right, total size =" << textItemMap[1].size();

}

void operation_Img::on_pushButton_2_clicked()
{
    if (!Evt) return;

    syncPositions();

    QList<QGraphicsItem*> selectedItems = Evt->selectedItems();
    if (selectedItems.isEmpty()) return;

    for (QGraphicsItem* sel : selectedItems) {
        QGraphicsTextItem* textItem = dynamic_cast<QGraphicsTextItem*>(sel);
        if (!textItem) continue;

        int delId = textItem->data(0).toInt();  // retrieve unique ID

        // Remove from scene
        Evt->removeItem(textItem);
        delete textItem;

        // Remove from our map
        for (auto it = textItemMap.begin(); it != textItemMap.end(); ++it) {
            QList<TextItemData>& itemList = it.value();

            for (int i = 0; i < itemList.size(); ++i) {
                if (itemList[i].id == delId) {
                    itemList.removeAt(i);
                    qDebug() << "Deleted item with id =" << delId;

                    if (itemList.isEmpty()) {
                        textItemMap.erase(it);
                    }
                    return; // exit after deleting one
                }
            }
        }
    }

    qDebug() << "After delete, map size =" << textItemMap[1].size();
}

void operation_Img::on_pushButton_3_clicked()
{
    if (!Evt) return;

    syncPositions();

    Evt->clear(); // clear existing scene

    for (auto it = textItemMap.begin(); it != textItemMap.end(); ++it) {
        const QList<TextItemData>& items = it.value();
        for (const TextItemData& data : items) {
            QGraphicsTextItem* textItem = Evt->addText(data.text, data.font);
            textItem->setDefaultTextColor(data.color);
            textItem->setPos(data.pos);
            textItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

            // Restore ID
            textItem->setData(0, data.id);
        }
    }

    qDebug() << "Redrawn, total items =" << textItemMap[1].size();
}
