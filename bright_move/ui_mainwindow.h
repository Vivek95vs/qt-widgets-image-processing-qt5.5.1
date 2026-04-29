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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *Load_Image;
    QPushButton *Brightness;
    QPushButton *Contrast;
    QPushButton *Window_width;
    QPushButton *Window_center;
    QSlider *brightness;
    QSlider *horizontalSlider_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1322, 992);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 1271, 861));
        Load_Image = new QPushButton(centralWidget);
        Load_Image->setObjectName(QStringLiteral("Load_Image"));
        Load_Image->setGeometry(QRect(20, 900, 75, 23));
        Brightness = new QPushButton(centralWidget);
        Brightness->setObjectName(QStringLiteral("Brightness"));
        Brightness->setGeometry(QRect(130, 900, 75, 23));
        Contrast = new QPushButton(centralWidget);
        Contrast->setObjectName(QStringLiteral("Contrast"));
        Contrast->setGeometry(QRect(240, 900, 75, 23));
        Window_width = new QPushButton(centralWidget);
        Window_width->setObjectName(QStringLiteral("Window_width"));
        Window_width->setGeometry(QRect(350, 900, 75, 23));
        Window_center = new QPushButton(centralWidget);
        Window_center->setObjectName(QStringLiteral("Window_center"));
        Window_center->setGeometry(QRect(470, 900, 75, 23));
        brightness = new QSlider(centralWidget);
        brightness->setObjectName(QStringLiteral("brightness"));
        brightness->setGeometry(QRect(590, 900, 160, 22));
        brightness->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(790, 900, 160, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1322, 21));
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
        Load_Image->setText(QApplication::translate("MainWindow", "Load", 0));
        Brightness->setText(QApplication::translate("MainWindow", "Bright", 0));
        Contrast->setText(QApplication::translate("MainWindow", "Contrast", 0));
        Window_width->setText(QApplication::translate("MainWindow", "WW", 0));
        Window_center->setText(QApplication::translate("MainWindow", "WC", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
