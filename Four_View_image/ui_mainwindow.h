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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Rendering;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_Ellipse;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *PB_Rectangle;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *PB_clear;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *PB_Freehand;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *PB_Rect;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PB_Circle;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *PB_Delete;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *PB_Clear;
    QHBoxLayout *horizontalLayout_6;
    QGraphicsView *graphicsView_AX;
    QGraphicsView *graphicsView_FRONT;
    QGraphicsView *graphicsView_SAG;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Axial;
    QSlider *Lowerthresh;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_11;
    QLabel *MInThresh;
    QSpacerItem *horizontalSpacer_12;
    QSlider *Upperthresh;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_13;
    QLabel *MaxThresh;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer;
    QPushButton *Frontal;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *Sagital;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1148, 987);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        MainWindow->setTabShape(QTabWidget::Triangular);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 1091, 871));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Rendering = new QPushButton(widget);
        Rendering->setObjectName(QStringLiteral("Rendering"));

        horizontalLayout_3->addWidget(Rendering);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        PB_Ellipse = new QPushButton(widget);
        PB_Ellipse->setObjectName(QStringLiteral("PB_Ellipse"));

        horizontalLayout_3->addWidget(PB_Ellipse);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        PB_Rectangle = new QPushButton(widget);
        PB_Rectangle->setObjectName(QStringLiteral("PB_Rectangle"));

        horizontalLayout_3->addWidget(PB_Rectangle);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        PB_clear = new QPushButton(widget);
        PB_clear->setObjectName(QStringLiteral("PB_clear"));

        horizontalLayout_3->addWidget(PB_clear);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        PB_Freehand = new QPushButton(widget);
        PB_Freehand->setObjectName(QStringLiteral("PB_Freehand"));

        horizontalLayout->addWidget(PB_Freehand);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        PB_Rect = new QPushButton(widget);
        PB_Rect->setObjectName(QStringLiteral("PB_Rect"));

        horizontalLayout->addWidget(PB_Rect);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PB_Circle = new QPushButton(widget);
        PB_Circle->setObjectName(QStringLiteral("PB_Circle"));

        horizontalLayout->addWidget(PB_Circle);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        PB_Delete = new QPushButton(widget);
        PB_Delete->setObjectName(QStringLiteral("PB_Delete"));

        horizontalLayout->addWidget(PB_Delete);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        PB_Clear = new QPushButton(widget);
        PB_Clear->setObjectName(QStringLiteral("PB_Clear"));

        horizontalLayout->addWidget(PB_Clear);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        graphicsView_AX = new QGraphicsView(widget);
        graphicsView_AX->setObjectName(QStringLiteral("graphicsView_AX"));

        horizontalLayout_6->addWidget(graphicsView_AX);

        graphicsView_FRONT = new QGraphicsView(widget);
        graphicsView_FRONT->setObjectName(QStringLiteral("graphicsView_FRONT"));

        horizontalLayout_6->addWidget(graphicsView_FRONT);

        graphicsView_SAG = new QGraphicsView(widget);
        graphicsView_SAG->setObjectName(QStringLiteral("graphicsView_SAG"));

        horizontalLayout_6->addWidget(graphicsView_SAG);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Axial = new QPushButton(widget);
        Axial->setObjectName(QStringLiteral("Axial"));

        verticalLayout_2->addWidget(Axial);

        Lowerthresh = new QSlider(widget);
        Lowerthresh->setObjectName(QStringLiteral("Lowerthresh"));
        Lowerthresh->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Lowerthresh);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);

        MInThresh = new QLabel(widget);
        MInThresh->setObjectName(QStringLiteral("MInThresh"));

        horizontalLayout_2->addWidget(MInThresh);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        verticalLayout_2->addLayout(horizontalLayout_2);

        Upperthresh = new QSlider(widget);
        Upperthresh->setObjectName(QStringLiteral("Upperthresh"));
        Upperthresh->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Upperthresh);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        MaxThresh = new QLabel(widget);
        MaxThresh->setObjectName(QStringLiteral("MaxThresh"));

        horizontalLayout_4->addWidget(MaxThresh);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        Frontal = new QPushButton(widget);
        Frontal->setObjectName(QStringLiteral("Frontal"));

        horizontalLayout_5->addWidget(Frontal);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        Sagital = new QPushButton(widget);
        Sagital->setObjectName(QStringLiteral("Sagital"));

        horizontalLayout_5->addWidget(Sagital);


        verticalLayout_4->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        graphicsView_SAG->raise();
        graphicsView_AX->raise();
        graphicsView_FRONT->raise();
        MInThresh->raise();
        MaxThresh->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1148, 21));
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
        Rendering->setText(QApplication::translate("MainWindow", "3D RENDER", 0));
        PB_Ellipse->setText(QApplication::translate("MainWindow", "VTK-Ellipse", 0));
        PB_Rectangle->setText(QApplication::translate("MainWindow", "VTK-Rectangle", 0));
        PB_clear->setText(QApplication::translate("MainWindow", "VTK-Clear", 0));
        PB_Freehand->setText(QApplication::translate("MainWindow", "FreeHand", 0));
        PB_Rect->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        PB_Circle->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        PB_Delete->setText(QApplication::translate("MainWindow", "Delete Item", 0));
        PB_Clear->setText(QApplication::translate("MainWindow", "ClearScreen", 0));
        Axial->setText(QApplication::translate("MainWindow", "AXIAL", 0));
        MInThresh->setText(QString());
        MaxThresh->setText(QString());
        Frontal->setText(QApplication::translate("MainWindow", "FRONTAL", 0));
        Sagital->setText(QApplication::translate("MainWindow", "SAGITAL", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
