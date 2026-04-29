#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createActions()
{
    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setCheckable(true);

    RectAction = new QAction("Draw rectline", this);
    RectAction->setData(int(Scene::RectLine));
    RectAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(RectAction);
    actionGroup->addAction(selectAction);
}

void MainWindow::createConnections()
{
    connect(actionGroup, SIGNAL(triggered(QAction*)),this, SLOT(actionGroupClicked(QAction*)));
}

void MainWindow::actionGroupClicked(QAction *action)
{
    scene->setMode(Scene::Mode(action->data().toInt()));
}
