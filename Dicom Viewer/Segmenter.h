#ifndef SEGMENTER_H
#define SEGMENTER_H

#include <QWidget>
#include "ui_Segmenter.h"
#include "vtkImageSegmentCallback.h"

class Segmenter : public QWidget
{
    Q_OBJECT

public:
    Segmenter(QWidget *parent = Q_NULLPTR);
    Segmenter(std::string Filename,QWidget *parent = Q_NULLPTR);
    ~Segmenter();

private:
    Ui::Segmenter ui;
    std::string m_Filename;
    SegmentFunc m_segment_fun;
signals:
    void SegmentFuncChange();
public slots:
    void OnConnectedThreshold();
    void OnWatershedThreshold();
    void OnNeighborhoodConnected();
    void OnConfidenceConnected();
    void OnFastMarching();
    void OnShapeDetection();

    void OnSegmentFuncChange();
};


#endif // SEGMENTER_H
