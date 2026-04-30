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
    QPushButton *ImageMerge;
    QPushButton *single_crop;
    QGraphicsView *graphicsViewAP;
    QPushButton *Two_imagecrop;
    QPushButton *three_imagecrop;
    QPushButton *Original_image;
    QPushButton *Four_Image_crop;
    QPushButton *pushButton_2;
    QPushButton *Two_Dicom_crop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1178, 1030);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ImageMerge = new QPushButton(centralWidget);
        ImageMerge->setObjectName(QStringLiteral("ImageMerge"));
        ImageMerge->setGeometry(QRect(20, 910, 75, 23));
        single_crop = new QPushButton(centralWidget);
        single_crop->setObjectName(QStringLiteral("single_crop"));
        single_crop->setGeometry(QRect(20, 760, 141, 23));
        graphicsViewAP = new QGraphicsView(centralWidget);
        graphicsViewAP->setObjectName(QStringLiteral("graphicsViewAP"));
        graphicsViewAP->setGeometry(QRect(200, 10, 945, 945));
        graphicsViewAP->setMouseTracking(false);
        graphicsViewAP->setStyleSheet(QLatin1String("background-color: rgb(0,0,0);\n"
"border: none;"));
        graphicsViewAP->setFrameShape(QFrame::NoFrame);
        graphicsViewAP->setFrameShadow(QFrame::Plain);
        Two_imagecrop = new QPushButton(centralWidget);
        Two_imagecrop->setObjectName(QStringLiteral("Two_imagecrop"));
        Two_imagecrop->setGeometry(QRect(20, 790, 141, 23));
        three_imagecrop = new QPushButton(centralWidget);
        three_imagecrop->setObjectName(QStringLiteral("three_imagecrop"));
        three_imagecrop->setGeometry(QRect(20, 820, 141, 23));
        Original_image = new QPushButton(centralWidget);
        Original_image->setObjectName(QStringLiteral("Original_image"));
        Original_image->setGeometry(QRect(20, 730, 141, 23));
        Four_Image_crop = new QPushButton(centralWidget);
        Four_Image_crop->setObjectName(QStringLiteral("Four_Image_crop"));
        Four_Image_crop->setGeometry(QRect(20, 850, 141, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 880, 141, 23));
        Two_Dicom_crop = new QPushButton(centralWidget);
        Two_Dicom_crop->setObjectName(QStringLiteral("Two_Dicom_crop"));
        Two_Dicom_crop->setGeometry(QRect(30, 630, 131, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1178, 21));
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
        ImageMerge->setText(QApplication::translate("MainWindow", "ImageMerge", 0));
        single_crop->setText(QApplication::translate("MainWindow", "Single Image Crop", 0));
#ifndef QT_NO_TOOLTIP
        graphicsViewAP->setToolTip(QApplication::translate("MainWindow", "2D", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        graphicsViewAP->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        Two_imagecrop->setText(QApplication::translate("MainWindow", "Two Image Crop", 0));
        three_imagecrop->setText(QApplication::translate("MainWindow", "Three Image Crop", 0));
        Original_image->setText(QApplication::translate("MainWindow", "Original Image", 0));
        Four_Image_crop->setText(QApplication::translate("MainWindow", "Four Image Crop", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Five Image Crop", 0));
        Two_Dicom_crop->setText(QApplication::translate("MainWindow", "Two Dicom Crop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
