#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QObject>
#include <QWidget>
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QWidget *parent);
};

#endif // GRAPHICSSCENE_H
