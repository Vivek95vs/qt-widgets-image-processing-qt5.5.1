#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QWidget>

#include <QVTKWidget.h>


class MyWidget : public QVTKWidget
{
    Q_OBJECT

public:

    explicit MyWidget(QWidget *parent = 0);
    int selectedTool;
    ~MyWidget();

protected:

   // QPaintEngine * paintEngine() const;

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent* event);

    int x;

    int rad = 20;

    int y;

    std::vector<int> vec;

    bool m_pressed;


signals:


public slots:

};


#endif // MYWIDGET_H
