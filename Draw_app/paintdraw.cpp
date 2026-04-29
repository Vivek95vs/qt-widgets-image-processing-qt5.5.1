#include <iostream>
#include <stdlib.h>
#include <qfiledialog.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <QMenuBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>
#include <QToolButton>
#include <QToolBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QColor>
#include<QImage>
#include<QRgb>
#include<QSize>
#include<QMoveEvent>
#include<mainwindow.h>
#include<paintdraw.h>

using namespace std;

PaintDraw::PaintDraw(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    painting = false;
    setButtonSelected(MainWindow::buttonPen);
    setPenWidth(1);
    setEraserWidth(5);
    resize(500, 500);
}

void PaintDraw::setButtonSelected(int val){
    buttonSelected = val;
}

int PaintDraw::getButtonSelected(){
    return buttonSelected;
}

void PaintDraw::setPenWidth(int val){
    penWidth = val;
}

int PaintDraw::getPenWidth(){
    return penWidth;
}

void PaintDraw::setEraserWidth(int val){
    eraserWidth = val;
}

int PaintDraw::getEraserWidth(){
    return eraserWidth;
}

QColor PaintDraw::getFColor(){
   return fColor;
}

QColor PaintDraw::getBColor(){
    return bColor;
}

void PaintDraw::setBColor(QColor color){
    bColor = color;
    image.fill(bColor);
    QPainter painter(&image);
    update();
}

void PaintDraw::setFColor(QColor color){
    fColor = color;
}

bool PaintDraw::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    update();
    return true;
}

bool PaintDraw::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());
    if (visibleImage.save(fileName, fileFormat)) {
        return true;
    } else {
        return false;
    }
}


void PaintDraw::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void PaintDraw::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    update();
}

void PaintDraw::eraseLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(getBColor(), getEraserWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    update();
    lastPoint = endPoint;
}

void PaintDraw::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        painting = true;
    }
}

void PaintDraw::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && painting) {
        if(getButtonSelected() == MainWindow::buttonPen || getButtonSelected() == MainWindow::buttonLine){
            drawLineTo(event->pos());
        }else if(getButtonSelected() == MainWindow::buttonRect){
            paintRect(event->pos());
        }else if(getButtonSelected() == MainWindow::buttonEraser){
            eraseLineTo(event->pos());
        }

    }
    painting = false;
}

void PaintDraw::mouseMoveEvent(QMouseEvent *event)
{
    cout<<"selected button"<< getButtonSelected();
    if(getButtonSelected() == MainWindow::buttonLine)
    {
       cout<<"\nLine selected test move\n";

    }
    if ((event->buttons() & Qt::LeftButton) && painting)
    {
        if(getButtonSelected() == MainWindow::buttonPen){
            cout<<"\n calling pen in move\n";
            drawLineTo(event->pos());
        }else if(getButtonSelected() == MainWindow::buttonEraser){
            cout<<"\n calling erase in move\n";
            eraseLineTo(event->pos());
        }

    }
}

void PaintDraw::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(getFColor(), getPenWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    update();
    lastPoint = endPoint;
}

void PaintDraw::paintRect(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(getFColor(), getPenWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(lastPoint.x(),lastPoint.y(),abs(endPoint.x() - lastPoint.x()),abs(endPoint.y() - lastPoint.y()));
    update();
    lastPoint = endPoint;
}


void PaintDraw::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void PaintDraw::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintDraw::paintEvent(QPaintEvent* e)
{
    QPainter paint(this);
    if (! image.isNull())
    {
        paint.drawImage(QPoint(0,0), (image));
    }
}
