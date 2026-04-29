#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qmessagebox.h>
//#include <qpopupmenu.h>
#include <QMenu>
#include <qmenubar.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <QMainWindow>
#include "paintdraw.h"

class MainWindow: public QMainWindow {
    // All classes that contain signals or slots
    // must mention Q_OBJECT in their declaration.
    Q_OBJECT

    public:
    MainWindow(QWidget* parent = 0, const char *name=0);
    ~MainWindow();
    enum btn {
        buttonOpen,
        buttonNew,
        buttonSave,
        buttonClearAll,
        buttonBColor,
        buttoFColor,
        buttonRedo,
        buttonUndo,
        buttonLine,
        buttonRect,
        buttonEraser,
        buttonPen,
        buttonResize
    };

    /* mouse event handler */
    //void mousePressEvent (QMouseEvent *);

    /* paint handler */
    // void paintEvent(QPaintEvent *);

private slots:
    void OnLoadImage();
    void create();
    void save();
    void quit();
    bool saveFile();
    void undo();
    void redo();
    void clrCanvas();
    void changeForegroundColor();
    void changeBackgroundColor();

    void penProp();
    void lineProp();
    void eraserProp();
    void rectangleProp();
    void lineSet();
    void rectSet();
    void penSet();
    void eraser();
    void resize();
private:

    PaintDraw *paintDraw;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolMenu;
    QActionGroup *alignmentGroup;
    QAction *newImageAct;
    QAction *saveImageAct;
    QAction  *loadImageAct;
    QAction *quitAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *clrAct;
    QAction *bgChangeAct;
    QAction *fgChangeAct;

    QAction *linePropAct;
    QAction *penPropAct;
    QAction *eraserPropAct;
    QAction *rectPropAct;
    void createActions();
    void createMenus();


};
#endif // MAINWINDOW_H
