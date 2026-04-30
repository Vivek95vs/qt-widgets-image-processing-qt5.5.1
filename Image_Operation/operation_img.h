#ifndef OPERATION_IMG_H
#define OPERATION_IMG_H
#include "disp_evt.h"
#include "ruler_item.h"

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>

struct TextItemData {
    int id;
    QString text;
    QFont font;
    QColor color;
    QPointF pos;
};

namespace Ui {
class operation_Img;
}

class operation_Img : public QDialog
{
    Q_OBJECT

public:
    explicit operation_Img(QWidget *parent = 0);
    QImage myImage;
    QImage myImage1;
    const int w=3072,h=3072;

//    Operation *opt;
    unsigned char* arr=new unsigned char[w*h];
    unsigned char* arr1=new unsigned char[w*h];
    unsigned char* arr2=new unsigned char[w*h];
    unsigned char* arr3=new unsigned char[w*h];
    bool Pressed;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;
    int ToggleScale;
    int ValueDiameter;
    Ruler_Item *itemRuler;
    ~operation_Img();


    QAction *Left;
    QAction *Right;

    QMap<int, QList<TextItemData>> textItemMap;
    int nextId = 0;

    void syncPositions();
//    QList<QGraphicsTextItem*> textItemlist;


private slots:


    void on_PB_LoadImage1_clicked();

    void on_PB_LoadImage2_clicked();

    void on_PB_Overlay_clicked();

    void on_PB_Quadrant_clicked();

    void on_PB_CheckerBoard_clicked();

    void on_PB_Toggle_clicked();

    void on_PB_Rectangle_clicked();

    void on_PB_Ellipse_clicked();

    void on_PB_FreeHand_clicked();

    void on_PB_Delete_clicked();

    void on_PB_Clearall_clicked();

    void on_PB_RectChange_clicked();

    void on_Left_clicked();
    void on_Right_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::operation_Img *ui;
    Disp_Evt *Evt;
    int dMode=0;

public slots:

    void changedLeftPos();
    void changedRightPos();
    void changedUpPos();
    void changedDownPos();
    void receivetohide();



    void on_PB_HorizRuler_clicked();
    void on_PB_VertiRuler_clicked();
    void on_PB_Image_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // OPERATION_IMG_H
