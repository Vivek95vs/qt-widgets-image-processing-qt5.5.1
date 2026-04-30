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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *PB_Ruler_Horizontal;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *PB_Vertical_Ruler;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PB_Draw_Anlgle;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *PB_Load_Image;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Clockwise_Rotate;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_Anticlockwise_Rotate;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1134, 900);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 1101, 781));
        graphicsView->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 810, 1091, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        PB_Ruler_Horizontal = new QPushButton(layoutWidget);
        PB_Ruler_Horizontal->setObjectName(QStringLiteral("PB_Ruler_Horizontal"));
        PB_Ruler_Horizontal->setCheckable(true);
        PB_Ruler_Horizontal->setChecked(false);

        horizontalLayout->addWidget(PB_Ruler_Horizontal);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        PB_Vertical_Ruler = new QPushButton(layoutWidget);
        PB_Vertical_Ruler->setObjectName(QStringLiteral("PB_Vertical_Ruler"));
        PB_Vertical_Ruler->setCheckable(true);

        horizontalLayout->addWidget(PB_Vertical_Ruler);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PB_Draw_Anlgle = new QPushButton(layoutWidget);
        PB_Draw_Anlgle->setObjectName(QStringLiteral("PB_Draw_Anlgle"));

        horizontalLayout->addWidget(PB_Draw_Anlgle);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        PB_Load_Image = new QPushButton(layoutWidget);
        PB_Load_Image->setObjectName(QStringLiteral("PB_Load_Image"));

        horizontalLayout->addWidget(PB_Load_Image);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        PB_Clockwise_Rotate = new QPushButton(layoutWidget);
        PB_Clockwise_Rotate->setObjectName(QStringLiteral("PB_Clockwise_Rotate"));

        horizontalLayout->addWidget(PB_Clockwise_Rotate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PB_Anticlockwise_Rotate = new QPushButton(layoutWidget);
        PB_Anticlockwise_Rotate->setObjectName(QStringLiteral("PB_Anticlockwise_Rotate"));

        horizontalLayout->addWidget(PB_Anticlockwise_Rotate);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1134, 21));
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
        PB_Ruler_Horizontal->setText(QApplication::translate("MainWindow", "Horizontal ruler", 0));
        PB_Vertical_Ruler->setText(QApplication::translate("MainWindow", "Vertical ruler", 0));
        PB_Draw_Anlgle->setText(QApplication::translate("MainWindow", "Draw Angle", 0));
        PB_Load_Image->setText(QApplication::translate("MainWindow", "Load Image", 0));
        PB_Clockwise_Rotate->setText(QApplication::translate("MainWindow", "Clockwise Rotate", 0));
        PB_Anticlockwise_Rotate->setText(QApplication::translate("MainWindow", "Anticlockwise Rotate", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
