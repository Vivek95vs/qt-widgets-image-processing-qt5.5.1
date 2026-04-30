#ifndef SCR_H
#define SCR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include<QWheelEvent>
class scr : public QGraphicsView
{
public:
    scr(QWidget *parent);
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // SCR_H
