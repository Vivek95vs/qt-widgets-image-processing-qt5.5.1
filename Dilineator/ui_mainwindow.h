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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *PB_Load1;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_overlay;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_Quadrant;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *PB_checker;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PB_toggle;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *PB_Rect;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *PB_Rectangle;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *PB_clearall;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *PB_load2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1131, 893);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 1101, 771));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 800, 1091, 51));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        PB_Load1 = new QPushButton(widget);
        PB_Load1->setObjectName(QStringLiteral("PB_Load1"));

        horizontalLayout->addWidget(PB_Load1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        PB_overlay = new QPushButton(widget);
        PB_overlay->setObjectName(QStringLiteral("PB_overlay"));

        horizontalLayout->addWidget(PB_overlay);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PB_Quadrant = new QPushButton(widget);
        PB_Quadrant->setObjectName(QStringLiteral("PB_Quadrant"));

        horizontalLayout->addWidget(PB_Quadrant);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        PB_checker = new QPushButton(widget);
        PB_checker->setObjectName(QStringLiteral("PB_checker"));

        horizontalLayout->addWidget(PB_checker);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PB_toggle = new QPushButton(widget);
        PB_toggle->setObjectName(QStringLiteral("PB_toggle"));

        horizontalLayout->addWidget(PB_toggle);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        PB_Rect = new QPushButton(widget);
        PB_Rect->setObjectName(QStringLiteral("PB_Rect"));

        horizontalLayout->addWidget(PB_Rect);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        PB_Rectangle = new QPushButton(widget);
        PB_Rectangle->setObjectName(QStringLiteral("PB_Rectangle"));

        horizontalLayout->addWidget(PB_Rectangle);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        PB_clearall = new QPushButton(widget);
        PB_clearall->setObjectName(QStringLiteral("PB_clearall"));

        horizontalLayout->addWidget(PB_clearall);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        PB_load2 = new QPushButton(widget);
        PB_load2->setObjectName(QStringLiteral("PB_load2"));

        horizontalLayout->addWidget(PB_load2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1131, 21));
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
        PB_Load1->setText(QApplication::translate("MainWindow", "Load Image 1", 0));
        PB_overlay->setText(QApplication::translate("MainWindow", "Overlay", 0));
        PB_Quadrant->setText(QApplication::translate("MainWindow", "Quadrant", 0));
        PB_checker->setText(QApplication::translate("MainWindow", "Checker Board", 0));
        PB_toggle->setText(QApplication::translate("MainWindow", "Toggle", 0));
        PB_Rect->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        PB_Rectangle->setText(QApplication::translate("MainWindow", "Dilineator", 0));
        PB_clearall->setText(QApplication::translate("MainWindow", "clear all", 0));
        PB_load2->setText(QApplication::translate("MainWindow", "Load Image 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
