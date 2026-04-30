#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtDebug>
#include <QtAlgorithms>
#include <QPainter>
#include "mouseoperations.h"
#include <QGraphicsEllipseItem>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    QList <QGraphicsItem*> list;
    QGraphicsItem *selectLines;
    QGraphicsEllipseItem *ellipseBrush = NULL;

    ~Dialog();

protected:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    MouseOperations *mouseOperations;



private slots:    

    void on_displayImage_clicked();
    void on_deleteLines_clicked();
    void on_lineSelection_clicked();
    void on_drawLine_clicked();
    void on_drawRectangle_clicked();
    void on_drawEllipse_clicked();
    void on_drawPolygon_clicked();
    void on_brushButton_clicked();
};

#endif // DIALOG_H
