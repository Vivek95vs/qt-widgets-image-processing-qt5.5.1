#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void actionGroupClicked(QAction*);

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    Scene* scene;

    void createActions();
    void createConnections();
    void createToolBar();

    QAction* lineAction;
    QAction* RectAction;
    QAction* selectAction;
    QActionGroup *actionGroup;
    QToolBar* drawingToolBar;

};

#endif // MAINWINDOW_H
