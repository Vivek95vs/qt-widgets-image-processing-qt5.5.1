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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClear;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionSave;
    QAction *actionBrush;
    QAction *actionLine;
    QAction *actionRectangle;
    QAction *actionEllipse;
    QAction *actionColor;
    QAction *actionWidth;
    QAction *actionInfo;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuAbout;
    QMenu *menuOptions_2;
    QMenu *menuBrush_Settings;
    QMenu *menuChoose_Shape;
    QToolBar *mainToolBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(521, 404);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/resource/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon1);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/resource/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon2);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/resource/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionBrush = new QAction(MainWindow);
        actionBrush->setObjectName(QStringLiteral("actionBrush"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/resource/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBrush->setIcon(icon4);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QStringLiteral("actionLine"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/resource/line.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine->setIcon(icon5);
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QStringLiteral("actionRectangle"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/resource/rect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRectangle->setIcon(icon6);
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QStringLiteral("actionEllipse"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/resource/circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEllipse->setIcon(icon7);
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/resource/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColor->setIcon(icon8);
        actionWidth = new QAction(MainWindow);
        actionWidth->setObjectName(QStringLiteral("actionWidth"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/resource/width.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWidth->setIcon(icon9);
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/resource/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInfo->setIcon(icon10);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 521, 29));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuOptions_2 = new QMenu(menuBar);
        menuOptions_2->setObjectName(QStringLiteral("menuOptions_2"));
        menuBrush_Settings = new QMenu(menuOptions_2);
        menuBrush_Settings->setObjectName(QStringLiteral("menuBrush_Settings"));
        menuChoose_Shape = new QMenu(menuOptions_2);
        menuChoose_Shape->setObjectName(QStringLiteral("menuChoose_Shape"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBar);
        MainWindow->insertToolBarBreak(toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuOptions_2->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionClear);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionUndo);
        menuOptions->addAction(actionRedo);
        menuAbout->addAction(actionInfo);
        menuOptions_2->addAction(menuBrush_Settings->menuAction());
        menuOptions_2->addAction(menuChoose_Shape->menuAction());
        menuBrush_Settings->addAction(actionColor);
        menuBrush_Settings->addAction(actionWidth);
        menuChoose_Shape->addAction(actionBrush);
        menuChoose_Shape->addAction(actionLine);
        menuChoose_Shape->addAction(actionRectangle);
        menuChoose_Shape->addAction(actionEllipse);
        mainToolBar->addAction(actionBrush);
        mainToolBar->addAction(actionLine);
        mainToolBar->addAction(actionRectangle);
        mainToolBar->addAction(actionEllipse);
        toolBar_2->addAction(actionUndo);
        toolBar_2->addAction(actionRedo);
        toolBar_2->addAction(actionColor);
        toolBar_2->addAction(actionWidth);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionClear->setText(QApplication::translate("MainWindow", "&Clear", 0));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "&Redo", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionSave->setText(QApplication::translate("MainWindow", "&Save As", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionBrush->setText(QApplication::translate("MainWindow", "&Brush", 0));
        actionLine->setText(QApplication::translate("MainWindow", "&Line", 0));
        actionRectangle->setText(QApplication::translate("MainWindow", "&Rectangle", 0));
        actionEllipse->setText(QApplication::translate("MainWindow", "&Ellipse", 0));
        actionColor->setText(QApplication::translate("MainWindow", "&Color", 0));
#ifndef QT_NO_TOOLTIP
        actionColor->setToolTip(QApplication::translate("MainWindow", "Select color to draw", 0));
#endif // QT_NO_TOOLTIP
        actionWidth->setText(QApplication::translate("MainWindow", "&Width", 0));
#ifndef QT_NO_TOOLTIP
        actionWidth->setToolTip(QApplication::translate("MainWindow", "Set line width", 0));
#endif // QT_NO_TOOLTIP
        actionInfo->setText(QApplication::translate("MainWindow", "&Info", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "&Edit", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "&About", 0));
        menuOptions_2->setTitle(QApplication::translate("MainWindow", "&Options", 0));
        menuBrush_Settings->setTitle(QApplication::translate("MainWindow", "&Brush Settings", 0));
        menuChoose_Shape->setTitle(QApplication::translate("MainWindow", "&Choose Shape", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
