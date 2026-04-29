#include <qmainwindow.h>
#include <qmessagebox.h>
#include <QMenu>
#include <qmenubar.h>
#include <qapplication.h>
#include <qpixmap.h>
#include<QPen>
#include<QWidget>
#include<QPainter>

#ifndef PAINTDRAW
#define PAINTDRAW


class PaintDraw : public QWidget {

    Q_OBJECT


public:

    PaintDraw(QWidget *parent = 0);
    QColor getFColor();
    QColor getBColor();
    void setBColor(QColor);
    void setFColor(QColor);
    void setButtonSelected(int);
    int getButtonSelected();
    int getPenWidth();
    void setPenWidth(int);
    int getEraserWidth();
    void setEraserWidth(int);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void eraseLineTo(const QPoint &endPoint);
    void paintRect(const QPoint &endPoint) ;



public slots:
    void setBrush(const QBrush &brush);
    void clearImage();


private:

    QPen pen;
    QBrush brush;
    bool painting;
    int penWidth;
    int eraserWidth;
    QImage image;
    QPoint lastPoint;
    QPixmap pixmap;
    int buttonSelected;
    QColor fColor = Qt::black;
    QColor bColor = Qt::white;


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;

};

#endif // PAINTDRAW
