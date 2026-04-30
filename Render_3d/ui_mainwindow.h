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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *PB_load;
    QPushButton *PB_Rect;
    QPushButton *PB_Ellipse;
    QPushButton *PB_FreeHand;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1145, 903);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 50, 1031, 671));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PB_load = new QPushButton(centralWidget);
        PB_load->setObjectName(QStringLiteral("PB_load"));
        PB_load->setGeometry(QRect(40, 760, 75, 23));
        PB_load->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PB_Rect = new QPushButton(centralWidget);
        PB_Rect->setObjectName(QStringLiteral("PB_Rect"));
        PB_Rect->setGeometry(QRect(140, 760, 75, 23));
        PB_Rect->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PB_Ellipse = new QPushButton(centralWidget);
        PB_Ellipse->setObjectName(QStringLiteral("PB_Ellipse"));
        PB_Ellipse->setGeometry(QRect(250, 760, 75, 23));
        PB_Ellipse->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PB_FreeHand = new QPushButton(centralWidget);
        PB_FreeHand->setObjectName(QStringLiteral("PB_FreeHand"));
        PB_FreeHand->setGeometry(QRect(360, 760, 75, 23));
        PB_FreeHand->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1145, 21));
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
        PB_load->setText(QApplication::translate("MainWindow", "Load", 0));
        PB_Rect->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        PB_Ellipse->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        PB_FreeHand->setText(QApplication::translate("MainWindow", "Free Hand", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
