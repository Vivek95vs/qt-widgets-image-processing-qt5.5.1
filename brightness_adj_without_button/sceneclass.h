#ifndef SCENECLASS_H
#define SCENECLASS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

//Opencv Headers
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace  cv;

class sceneclass:public QGraphicsScene
{
    Q_OBJECT
public:
    sceneclass();

    QPointF slider_moved;
    QPointF mousepress_pos;
    QPointF mouserelease_pos;
    QPointF currentmouse_pos;
    float angle;
    int angle_f;
    cv::Mat imgMat;
    QPointF b;
    /*int*//*qreal*/ QPointF brightness;
    QPointF c;
    int b1=0;
    int c1=0;
    int /*qreal *//*QPointF*/ contrast=1;
    QPointF orig;
    qreal temp_bright;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void rightbuttonclicked();
};

#endif // SCENECLASS_H
