#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPointF>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPen pen;
    QPainter painter(this);
    pen.setWidth(2);
    pen.setColor(QColor(Qt::darkGray));
    painter.setPen(pen);
    painter.drawRect(boundingRect().adjusted(5, 5, -5, -5));

    if(m_line.isNull()) return;
    pen.setWidth(10);
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);
    painter.drawLine(m_line);
}

QRectF MainWindow::boundingRect() const
{
    return QRectF(QPointF(0,0), QPointF(200, 200));
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos().toPoint();
    qDebug() << "Pressed, start: " << startPoint;
    pressed = true;
    QGraphicsScene::mousePressEvent(event);

}

void MainWindow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(pressed)
    {
    QPoint endPoint = event->scenePos().toPoint();
    qDebug() << "Moving, start: " << startPoint << "  end: " << endPoint;
    m_line.setPoints(startPoint, endPoint);
    QGraphicsScene::mouseMoveEvent(event);
    }
}

void MainWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    QPoint endPoint = event->scenePos().toPoint();
    m_line.setPoints(startPoint, endPoint);
    qDebug() << "Release, start: " << startPoint << "  end: " << endPoint;
    QGraphicsScene::mouseReleaseEvent(event);
}


