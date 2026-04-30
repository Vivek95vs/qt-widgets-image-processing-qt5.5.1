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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
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
    QPushButton *PB_LOAD;
    QSlider *Maxslider;
    QSlider *minslider;
    QSlider *brightness;
    QSlider *contrast;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *Max_label;
    QLabel *Min_label;
    QLabel *Bright_label;
    QLabel *contrast_label;
    QPushButton *Auto;
    QPushButton *Reset;
    QLabel *Hist_label;
    QCheckBox *checkBox;
    QSlider *minslider_2;
    QGroupBox *groupBox;
    QSlider *threeDslider;
    QScrollBar *verticalScrollBar;
    QGroupBox *groupBox_2;
    QPushButton *SaveDB;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1471, 876);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(270, 30, 911, 751));
        PB_LOAD = new QPushButton(centralWidget);
        PB_LOAD->setObjectName(QStringLiteral("PB_LOAD"));
        PB_LOAD->setGeometry(QRect(20, 790, 75, 23));
        Maxslider = new QSlider(centralWidget);
        Maxslider->setObjectName(QStringLiteral("Maxslider"));
        Maxslider->setGeometry(QRect(20, 490, 251, 21));
        Maxslider->setStyleSheet(QLatin1String("QSlider::groove:horizontal\n"
"{\n"
"\n"
"height:10px;\n"
"width:225px;\n"
"background:rgb(10,182,242);\n"
"border-radius:10px;\n"
"\n"
"}\n"
"\n"
"QSlider::handle:horizontal\n"
"{\n"
"\n"
"background:rgb(10,182,242);\n"
"border:rgb(0,0,255);\n"
"width:20px;\n"
"margin:-5px;\n"
"border-radius:10px;\n"
"\n"
"}\n"
"\n"
"QSlider:add-page:horizontal\n"
"{\n"
"\n"
"\n"
"height:30px;\n"
"background:rgb(200,200,200);\n"
"border:3px solid rgb(255,0,0);\n"
"border-radius:18px;\n"
"}"));
        Maxslider->setOrientation(Qt::Horizontal);
        minslider = new QSlider(centralWidget);
        minslider->setObjectName(QStringLiteral("minslider"));
        minslider->setGeometry(QRect(90, 530, 160, 22));
        minslider->setStyleSheet(QLatin1String("QSlider::handle:horizontal\n"
"{\n"
"\n"
"background:rgb(10,182,242);\n"
"border:rgb(0,0,255);\n"
"width:20px;\n"
"margin:-5px;\n"
"border-radius:10px;\n"
"\n"
"}"));
        minslider->setOrientation(Qt::Horizontal);
        brightness = new QSlider(centralWidget);
        brightness->setObjectName(QStringLiteral("brightness"));
        brightness->setGeometry(QRect(90, 580, 160, 22));
        brightness->setOrientation(Qt::Horizontal);
        contrast = new QSlider(centralWidget);
        contrast->setObjectName(QStringLiteral("contrast"));
        contrast->setGeometry(QRect(90, 630, 160, 22));
        contrast->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 490, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 540, 47, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(16, 580, 51, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 630, 47, 13));
        Max_label = new QLabel(centralWidget);
        Max_label->setObjectName(QStringLiteral("Max_label"));
        Max_label->setGeometry(QRect(140, 510, 47, 16));
        Min_label = new QLabel(centralWidget);
        Min_label->setObjectName(QStringLiteral("Min_label"));
        Min_label->setGeometry(QRect(140, 550, 47, 16));
        Bright_label = new QLabel(centralWidget);
        Bright_label->setObjectName(QStringLiteral("Bright_label"));
        Bright_label->setGeometry(QRect(140, 600, 47, 16));
        contrast_label = new QLabel(centralWidget);
        contrast_label->setObjectName(QStringLiteral("contrast_label"));
        contrast_label->setGeometry(QRect(140, 650, 47, 16));
        Auto = new QPushButton(centralWidget);
        Auto->setObjectName(QStringLiteral("Auto"));
        Auto->setGeometry(QRect(20, 680, 75, 23));
        Reset = new QPushButton(centralWidget);
        Reset->setObjectName(QStringLiteral("Reset"));
        Reset->setGeometry(QRect(120, 680, 75, 23));
        Hist_label = new QLabel(centralWidget);
        Hist_label->setObjectName(QStringLiteral("Hist_label"));
        Hist_label->setGeometry(QRect(10, 289, 241, 151));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(40, 450, 101, 17));
        minslider_2 = new QSlider(centralWidget);
        minslider_2->setObjectName(QStringLiteral("minslider_2"));
        minslider_2->setGeometry(QRect(19, 740, 241, 22));
        minslider_2->setStyleSheet(QLatin1String("QSlider {\n"
"    background: rgb(240, 240, 240); /* Slider background */\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    height: 10px;\n"
"    width: 215px;\n"
"    background: rgb(240, 240, 240);\n"
"    border: 1px solid rgb(10, 182, 242); /* Corrected border property */\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: rgb(10, 182, 242);\n"
"    width: 14px;\n"
"    margin: -3px;\n"
" 	border: 1px solid rgb(50, 50, 50);\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background: rgb(10, 182, 242); /* Color of the slider track filled as the handle moves */\n"
"    border-radius: 10px;\n"
"}"));
        minslider_2->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1260, 90, 120, 571));
        groupBox->setStyleSheet(QLatin1String("QGroupBox{\n"
"background-color:rgb(240,240,240);\n"
"border: none;\n"
"}"));
        threeDslider = new QSlider(groupBox);
        threeDslider->setObjectName(QStringLiteral("threeDslider"));
        threeDslider->setGeometry(QRect(80, 30, 19, 511));
        threeDslider->setStyleSheet(QLatin1String("QSlider::groove:vertical { \n"
"	background-color: black;\n"
"	border: 0px solid #424242; \n"
"	height: 511px; \n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:vertical { \n"
"	background-color: red; \n"
"	border: 2px solid red; \n"
"	width: 16px; \n"
"	height: 20px; \n"
"	line-height: 20px; \n"
"	margin-top: -5px; \n"
"	margin-bottom: -5px; \n"
"	border-radius: 10px; \n"
"}\n"
"\n"
"QSlider::handle:vertical:hover { \n"
"	border-radius: 10px;\n"
"}"));
        threeDslider->setOrientation(Qt::Vertical);
        verticalScrollBar = new QScrollBar(groupBox);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(30, 30, 5, 511));
        verticalScrollBar->setStyleSheet(QLatin1String("QScrollBar:vertical {\n"
"    width: 10px;  /* Width of the scrollbar */\n"
"    background: #f0f0f0;  /* Background color for the track */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #5e5e5e;  /* Handle color */\n"
"    border-radius: 2.5px;  /* Rounded corners for the handle */\n"
"    min-height: 10px;  /* Minimum height of the handle */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #3e3e3e;  /* Handle color on hover */\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    background: none;  /* Optional: Hide the arrows */\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: none;  /* Optional: Hide the background of the page */\n"
"}"));
        verticalScrollBar->setOrientation(Qt::Vertical);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(19, 90, 241, 111));
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox{\n"
"background-color:rgb(50,50,50);\n"
"border: none;\n"
"}"));
        SaveDB = new QPushButton(groupBox_2);
        SaveDB->setObjectName(QStringLiteral("SaveDB"));
        SaveDB->setGeometry(QRect(10, 40, 221, 20));
        SaveDB->setStyleSheet(QLatin1String("color: rgb(0,0,0);\n"
"background-color: rgb(255, 255, 255);"));
        SaveDB->setFlat(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1471, 21));
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
        PB_LOAD->setText(QApplication::translate("MainWindow", "Load", 0));
        label->setText(QApplication::translate("MainWindow", "Maximum", 0));
        label_2->setText(QApplication::translate("MainWindow", "Minimum", 0));
        label_3->setText(QApplication::translate("MainWindow", "Brightness", 0));
        label_4->setText(QApplication::translate("MainWindow", "Contrast", 0));
        Max_label->setText(QString());
        Min_label->setText(QString());
        Bright_label->setText(QString());
        contrast_label->setText(QString());
        Auto->setText(QApplication::translate("MainWindow", "Auto", 0));
        Reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        Hist_label->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "Check", 0));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        SaveDB->setText(QApplication::translate("MainWindow", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
