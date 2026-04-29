#include <iostream>
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
#include<QDesktopWidget>
#include<QColorDialog>
#include<QDesktopWidget>
#include "mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget* parent, const char* name)
:QMainWindow(parent)
{
    name="Paint";
    paintDraw = new PaintDraw();
    QDesktopWidget dw;
    int x=dw.width()*0.7;
    int y=dw.height()*0.7;
    setFixedSize(x,y);

    QWidget::setWindowTitle(name);
    createActions();
    createMenus();
    setCentralWidget(paintDraw);

    QToolBar *toolBar= new QToolBar("toolBar", this);
    QToolButton *buttonOpen = new QToolButton;
    buttonOpen->setIcon(QIcon(":/icon/open_icon.bmp"));
    connect(buttonOpen,SIGNAL(clicked()),this,SLOT(OnLoadImage()));
    QToolButton *buttonNew = new QToolButton;
    buttonNew->setIcon(QIcon(":/icon/new_icon.bmp"));
    connect(buttonNew,SIGNAL(clicked()),this,SLOT(create()));
    QToolButton *buttonSave = new QToolButton;
    buttonSave->setIcon(QIcon(":/icon/save_icon.bmp"));
    connect(buttonSave,SIGNAL(clicked()),this,SLOT(saveFile()));
    QToolButton *buttonClearAll = new QToolButton;
    buttonClearAll->setIcon(QIcon(":/icon/clearall_icon.bmp"));
    connect(buttonClearAll,SIGNAL(clicked()),this,SLOT(clrCanvas()));
    QToolButton *buttonBColor = new QToolButton;
    buttonBColor->setIcon(QIcon(":/icon/bcolor_icon.bmp"));
    connect(buttonBColor,SIGNAL(clicked()),this,SLOT(changeBackgroundColor()));
    QToolButton *buttonFColor = new QToolButton;
    buttonFColor->setIcon(QIcon(":/icon/fcolor_icon.bmp"));
    connect(buttonFColor,SIGNAL(clicked()),this,SLOT(changeForegroundColor()));
    QToolButton *buttonRedo = new QToolButton;
    buttonRedo->setIcon(QIcon(":/icon/redo_icon.bmp"));
    connect(buttonRedo,SIGNAL(clicked()),this,SLOT(redo()));
    QToolButton *buttonUndo = new QToolButton;
    buttonUndo->setIcon(QIcon(":/icon/undo_icon.bmp"));
    connect(buttonUndo,SIGNAL(clicked()),this,SLOT(undo()));
    QToolButton *buttonLine = new QToolButton;
    buttonLine->setIcon(QIcon(":/icon/line_icon.bmp"));
    connect(buttonLine,SIGNAL(clicked()),this,SLOT(lineSet()));
    QToolButton *buttonRect = new QToolButton;
    buttonRect->setIcon(QIcon(":/icon/rect_icon.bmp"));
    connect(buttonRect,SIGNAL(clicked()),this,SLOT(rectSet()));
    QToolButton *buttonEraser = new QToolButton;
    buttonEraser->setIcon(QIcon(":/icon/eraser_icon.bmp"));
    connect(buttonEraser,SIGNAL(clicked()),this,SLOT(eraser()));
    QToolButton *buttonPen = new QToolButton;
    buttonPen->setIcon(QIcon(":/icon/pen_icon.bmp"));
    connect(buttonPen,SIGNAL(clicked()),this,SLOT(penSet()));
    QToolButton *buttonResize = new QToolButton;
    buttonResize->setIcon(QIcon(":/icon/resize_icon.bmp"));
    connect(buttonResize,SIGNAL(clicked()),this,SLOT(resize()));
    toolBar->addWidget(buttonOpen);
    toolBar->addSeparator();
    toolBar->addWidget(buttonNew);
    toolBar->addSeparator();
    toolBar->addWidget(buttonSave);
    toolBar->addSeparator();
    toolBar->addWidget(buttonClearAll);
    toolBar->addSeparator();
    toolBar->addWidget(buttonBColor);
    toolBar->addSeparator();
    toolBar->addWidget(buttonFColor);
    toolBar->addSeparator();
    toolBar->addWidget(buttonRedo);
    toolBar->addSeparator();
    toolBar->addWidget(buttonUndo);
    toolBar->addSeparator();
    toolBar->addWidget(buttonLine);
    toolBar->addSeparator();
    toolBar->addWidget(buttonRect);
    toolBar->addSeparator();
    toolBar->addWidget(buttonEraser);
    toolBar->addSeparator();
    toolBar->addWidget(buttonPen);
    toolBar->addSeparator();
    toolBar->addWidget(buttonResize);
    addToolBarBreak();
    addToolBar(Qt::TopToolBarArea, toolBar);
}


void MainWindow::clrCanvas()
{
    paintDraw->clearImage();

}
void MainWindow::create()
{

}
void MainWindow::save()
{
    /*QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat =new QByteArray();
            fileFormat= action->data().toByteArray();
    saveFile(fileFormat); */

}
bool MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
                               "/home",
                               tr("BMP(*.bmp)"));
    if (fileName.isEmpty()) {
        return false;
    } else {
        if(!fileName.contains(".bmp")){
            fileName = fileName.append(".bmp");
        }
        return paintDraw->saveImage(fileName, "BMP");
    }
}
void MainWindow::lineSet()
{
    cout<<"before line set";
    paintDraw->setButtonSelected(buttonLine);
}
void MainWindow::rectSet()
{
    cout<<"before rectangle";
    paintDraw->setButtonSelected(buttonRect);
}
void MainWindow::eraser()
{
    cout<<"before erase";
    paintDraw->setButtonSelected(buttonEraser);
}
void MainWindow::penSet()
{
    cout<<"before pen set";
    paintDraw->setButtonSelected(buttonPen);
}
void MainWindow::resize()
{
    cout<<"in resize";
    setFixedSize(400,300);

}
void MainWindow::quit()
{}

void MainWindow::undo()
{}

void MainWindow::redo()
{}

void MainWindow::changeBackgroundColor()
{
    paintDraw->setBColor(QColorDialog::getColor(Qt::black, this, "Background Color",  QColorDialog::DontUseNativeDialog));
}

void MainWindow::changeForegroundColor()
{
    paintDraw->setFColor(QColorDialog::getColor(Qt::black, this, "Foreground Color",  QColorDialog::DontUseNativeDialog));
}

void MainWindow::penProp()
{}
void MainWindow::lineProp()
{}
void MainWindow::eraserProp()
{}
void MainWindow::rectangleProp()
{}
void MainWindow::createActions()
{
    newImageAct = new QAction(tr("&New"), this);
    newImageAct->setShortcuts(QKeySequence::New);
    newImageAct->setStatusTip(tr("Create a new file"));
    connect(newImageAct, &QAction::triggered, this, &MainWindow::create);


    saveImageAct = new QAction(tr("&Save"), this);
    saveImageAct->setShortcuts(QKeySequence::Save);
    saveImageAct->setStatusTip(tr("Save file"));
    connect(saveImageAct, &QAction::triggered, this, &MainWindow::save);

    loadImageAct = new QAction(tr("&Load Image"), this);
    newImageAct->setShortcuts(QKeySequence::Open);
    newImageAct->setStatusTip(tr("Load file"));
    connect(loadImageAct, &QAction::triggered, this, &MainWindow::OnLoadImage);

    quitAct= new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Undo);
    newImageAct->setStatusTip(tr("Quit"));
    connect(quitAct, &QAction::triggered, this, &MainWindow::undo);

    undoAct= new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct= new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    clrAct= new QAction(tr("&Clear Canvas"), this);
    clrAct->setShortcuts(QKeySequence::Undo);
    clrAct->setStatusTip(tr("Clear Canvas"));
    connect(clrAct, &QAction::triggered, this, &MainWindow::clrCanvas);

    bgChangeAct=new QAction(tr("&Background Color.."), this);
    bgChangeAct->setStatusTip(tr("Background Color"));
    connect(bgChangeAct, &QAction::triggered, this, &MainWindow::changeBackgroundColor);

    fgChangeAct=new QAction(tr("&Foreground Color.."), this);
    fgChangeAct->setStatusTip(tr("Foreground Color"));
    connect(fgChangeAct, &QAction::triggered, this, &MainWindow::changeForegroundColor);

    penPropAct=new QAction(tr("&Pen Properties.."), this);
    penPropAct->setStatusTip(tr("Pen Properties.."));
    connect(penPropAct, &QAction::triggered, this, &MainWindow::penProp);

    linePropAct=new QAction(tr("&Line Properties.."), this);
    linePropAct->setStatusTip(tr("Line Properties"));
    connect(linePropAct, &QAction::triggered, this, &MainWindow::penProp);

    eraserPropAct=new QAction(tr("&Eraser Properties.."), this);
    eraserPropAct->setStatusTip(tr("Eraser Properties"));
    connect(eraserPropAct, &QAction::triggered, this, &MainWindow::eraserProp);

    rectPropAct=new QAction(tr("&Rectangle Properties.."), this);
    rectPropAct->setStatusTip(tr("Rectangle Properties"));
    connect(rectPropAct, &QAction::triggered, this, &MainWindow::rectangleProp);


}
void MainWindow ::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newImageAct);
    fileMenu->addAction(loadImageAct);
    fileMenu->addAction(saveImageAct);
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(clrAct);
    editMenu->addAction(bgChangeAct);
    editMenu->addAction(fgChangeAct);

    toolMenu= menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(linePropAct);
    toolMenu->addAction(penPropAct);
    toolMenu->addAction(eraserPropAct);
    toolMenu->addAction(rectPropAct);

}




MainWindow::~MainWindow()
{
    //delete paintdraw->image;
}

void MainWindow::OnLoadImage()
{

    QString s = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp)"));
    if (! s.isNull())
    {
      paintDraw->openImage(s);
    }

}

/*void MainWindow::mousePressEvent(QMouseEvent * e)
{
    QMessageBox::about( this, "bitmap", "Mouse click event!");
}*/
