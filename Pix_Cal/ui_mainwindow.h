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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *LoadRaw;
    QPushButton *Inverting;
    QPushButton *PixCal;
    QPushButton *Rowpixel;
    QPushButton *Smothening;
    QPushButton *Folder;
    QPushButton *Smooth_disp;
    QPushButton *Load;
    QPushButton *Dicom_raw;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1194, 852);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(30, 20, 1131, 691));
        LoadRaw = new QPushButton(centralWidget);
        LoadRaw->setObjectName(QStringLiteral("LoadRaw"));
        LoadRaw->setGeometry(QRect(150, 750, 75, 23));
        Inverting = new QPushButton(centralWidget);
        Inverting->setObjectName(QStringLiteral("Inverting"));
        Inverting->setGeometry(QRect(250, 750, 75, 23));
        PixCal = new QPushButton(centralWidget);
        PixCal->setObjectName(QStringLiteral("PixCal"));
        PixCal->setGeometry(QRect(360, 750, 75, 23));
        Rowpixel = new QPushButton(centralWidget);
        Rowpixel->setObjectName(QStringLiteral("Rowpixel"));
        Rowpixel->setGeometry(QRect(460, 750, 75, 23));
        Smothening = new QPushButton(centralWidget);
        Smothening->setObjectName(QStringLiteral("Smothening"));
        Smothening->setGeometry(QRect(560, 750, 75, 23));
        Folder = new QPushButton(centralWidget);
        Folder->setObjectName(QStringLiteral("Folder"));
        Folder->setGeometry(QRect(50, 750, 75, 23));
        Smooth_disp = new QPushButton(centralWidget);
        Smooth_disp->setObjectName(QStringLiteral("Smooth_disp"));
        Smooth_disp->setGeometry(QRect(660, 750, 121, 23));
        Load = new QPushButton(centralWidget);
        Load->setObjectName(QStringLiteral("Load"));
        Load->setGeometry(QRect(800, 750, 75, 23));
        Dicom_raw = new QPushButton(centralWidget);
        Dicom_raw->setObjectName(QStringLiteral("Dicom_raw"));
        Dicom_raw->setGeometry(QRect(900, 750, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1194, 21));
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
        LoadRaw->setText(QApplication::translate("MainWindow", "Load Raw", 0));
        Inverting->setText(QApplication::translate("MainWindow", "Invert", 0));
        PixCal->setText(QApplication::translate("MainWindow", "Pix Cal", 0));
        Rowpixel->setText(QApplication::translate("MainWindow", "RowPix", 0));
        Smothening->setText(QApplication::translate("MainWindow", "Smooth", 0));
        Folder->setText(QApplication::translate("MainWindow", "Load Folder", 0));
        Smooth_disp->setText(QApplication::translate("MainWindow", "Smoothened Image Disp", 0));
        Load->setText(QApplication::translate("MainWindow", "Load", 0));
        Dicom_raw->setText(QApplication::translate("MainWindow", "Dicom to raw", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
