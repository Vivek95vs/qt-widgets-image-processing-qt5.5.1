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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QPushButton *Dicomtoraw;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *Access;
    QPushButton *Blank_raw;
    QPushButton *compress_CBCT;
    QPushButton *on_crop_raw;
    QPushButton *vertical_crop;
    QPushButton *Converttobinary;
    QPushButton *Block_input;
    QPushButton *Decrypt;
    QPushButton *Dicom_lateral_crop;
    QPushButton *longitudinalfive;
    QPushButton *lateralfive;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1203, 822);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(60, 40, 991, 651));
        Dicomtoraw = new QPushButton(centralWidget);
        Dicomtoraw->setObjectName(QStringLiteral("Dicomtoraw"));
        Dicomtoraw->setGeometry(QRect(60, 710, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(240, 710, 331, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 710, 71, 21));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(700, 710, 113, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(650, 710, 47, 16));
        Access = new QPushButton(centralWidget);
        Access->setObjectName(QStringLiteral("Access"));
        Access->setGeometry(QRect(60, 740, 75, 23));
        Blank_raw = new QPushButton(centralWidget);
        Blank_raw->setObjectName(QStringLiteral("Blank_raw"));
        Blank_raw->setGeometry(QRect(150, 740, 101, 23));
        compress_CBCT = new QPushButton(centralWidget);
        compress_CBCT->setObjectName(QStringLiteral("compress_CBCT"));
        compress_CBCT->setGeometry(QRect(270, 740, 101, 23));
        on_crop_raw = new QPushButton(centralWidget);
        on_crop_raw->setObjectName(QStringLiteral("on_crop_raw"));
        on_crop_raw->setGeometry(QRect(390, 740, 111, 23));
        vertical_crop = new QPushButton(centralWidget);
        vertical_crop->setObjectName(QStringLiteral("vertical_crop"));
        vertical_crop->setGeometry(QRect(510, 740, 121, 23));
        Converttobinary = new QPushButton(centralWidget);
        Converttobinary->setObjectName(QStringLiteral("Converttobinary"));
        Converttobinary->setGeometry(QRect(650, 740, 131, 23));
        Block_input = new QPushButton(centralWidget);
        Block_input->setObjectName(QStringLiteral("Block_input"));
        Block_input->setGeometry(QRect(800, 740, 75, 23));
        Decrypt = new QPushButton(centralWidget);
        Decrypt->setObjectName(QStringLiteral("Decrypt"));
        Decrypt->setGeometry(QRect(890, 740, 75, 23));
        Dicom_lateral_crop = new QPushButton(centralWidget);
        Dicom_lateral_crop->setObjectName(QStringLiteral("Dicom_lateral_crop"));
        Dicom_lateral_crop->setGeometry(QRect(830, 710, 111, 23));
        longitudinalfive = new QPushButton(centralWidget);
        longitudinalfive->setObjectName(QStringLiteral("longitudinalfive"));
        longitudinalfive->setGeometry(QRect(990, 710, 80, 21));
        lateralfive = new QPushButton(centralWidget);
        lateralfive->setObjectName(QStringLiteral("lateralfive"));
        lateralfive->setGeometry(QRect(990, 740, 80, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1203, 20));
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
        Dicomtoraw->setText(QApplication::translate("MainWindow", "Dicom to RAw", 0));
        label->setText(QApplication::translate("MainWindow", "Save Path:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Number", 0));
        Access->setText(QApplication::translate("MainWindow", "Acces PC", 0));
        Blank_raw->setText(QApplication::translate("MainWindow", "Blank Raw image", 0));
        compress_CBCT->setText(QApplication::translate("MainWindow", "Compress CBCT", 0));
        on_crop_raw->setText(QApplication::translate("MainWindow", "horizontal Crop Raw", 0));
        vertical_crop->setText(QApplication::translate("MainWindow", "Vertical Crop Raw", 0));
        Converttobinary->setText(QApplication::translate("MainWindow", "Convert image to binary", 0));
        Block_input->setText(QApplication::translate("MainWindow", "Block input", 0));
        Decrypt->setText(QApplication::translate("MainWindow", "Decrypt", 0));
        Dicom_lateral_crop->setText(QApplication::translate("MainWindow", "Dicom lateral crop", 0));
        longitudinalfive->setText(QApplication::translate("MainWindow", "Longitudinalfive", 0));
        lateralfive->setText(QApplication::translate("MainWindow", "lateralfive", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
