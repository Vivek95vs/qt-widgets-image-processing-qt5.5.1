/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QCustomPlot *customPlot;
    QPushButton *Load_Image;
    QPushButton *Select_ROI;
    QPushButton *Pix_Cal;
    QPushButton *Graph_plot;
    QPushButton *smoothening;
    QPushButton *Invert;
    QPushButton *Row;
    QPushButton *pix;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1195, 853);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 561, 661));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(600, 10, 581, 661));
        Load_Image = new QPushButton(centralWidget);
        Load_Image->setObjectName(QStringLiteral("Load_Image"));
        Load_Image->setGeometry(QRect(30, 710, 91, 23));
        Select_ROI = new QPushButton(centralWidget);
        Select_ROI->setObjectName(QStringLiteral("Select_ROI"));
        Select_ROI->setGeometry(QRect(160, 710, 111, 23));
        Pix_Cal = new QPushButton(centralWidget);
        Pix_Cal->setObjectName(QStringLiteral("Pix_Cal"));
        Pix_Cal->setGeometry(QRect(320, 710, 91, 23));
        Graph_plot = new QPushButton(centralWidget);
        Graph_plot->setObjectName(QStringLiteral("Graph_plot"));
        Graph_plot->setGeometry(QRect(450, 710, 75, 23));
        smoothening = new QPushButton(centralWidget);
        smoothening->setObjectName(QStringLiteral("smoothening"));
        smoothening->setGeometry(QRect(570, 710, 75, 23));
        Invert = new QPushButton(centralWidget);
        Invert->setObjectName(QStringLiteral("Invert"));
        Invert->setGeometry(QRect(670, 710, 75, 23));
        Row = new QPushButton(centralWidget);
        Row->setObjectName(QStringLiteral("Row"));
        Row->setGeometry(QRect(30, 750, 75, 23));
        pix = new QPushButton(centralWidget);
        pix->setObjectName(QStringLiteral("pix"));
        pix->setGeometry(QRect(140, 750, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1195, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Load_Image->setText(QApplication::translate("MainWindow", "Load Raw Image", 0));
        Select_ROI->setText(QApplication::translate("MainWindow", "Draw Rect-Area", 0));
        Pix_Cal->setText(QApplication::translate("MainWindow", "Pixel Calculate", 0));
        Graph_plot->setText(QApplication::translate("MainWindow", "Plot Graph", 0));
        smoothening->setText(QApplication::translate("MainWindow", "Smoothening", 0));
        Invert->setText(QApplication::translate("MainWindow", "Invert", 0));
        Row->setText(QApplication::translate("MainWindow", "Row", 0));
        pix->setText(QApplication::translate("MainWindow", "Pix", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
