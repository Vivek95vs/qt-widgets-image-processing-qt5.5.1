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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
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
    QGraphicsView *graphicsView;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *PB_LoadDicom_Image;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QLabel *Brightandcontrastname;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *Slider_Bright;
    QLabel *Bright;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *Slider_Contrast;
    QLabel *Contrast;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QComboBox *combo1;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *Load_Raw;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *WCandWWname;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSlider *Slider_WC;
    QLabel *WC;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *Slider_WW;
    QLabel *WW;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *PB_MedianFilter;
    QPushButton *PB_Reset;
    QPushButton *PB_Invert_Filter;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1132, 899);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(50, 40, 1051, 711));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 760, 1041, 103));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        PB_LoadDicom_Image = new QPushButton(layoutWidget);
        PB_LoadDicom_Image->setObjectName(QStringLiteral("PB_LoadDicom_Image"));

        horizontalLayout_5->addWidget(PB_LoadDicom_Image);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Brightandcontrastname = new QLabel(layoutWidget);
        Brightandcontrastname->setObjectName(QStringLiteral("Brightandcontrastname"));

        verticalLayout->addWidget(Brightandcontrastname);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        Slider_Bright = new QSlider(layoutWidget);
        Slider_Bright->setObjectName(QStringLiteral("Slider_Bright"));
        Slider_Bright->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Slider_Bright);

        Bright = new QLabel(layoutWidget);
        Bright->setObjectName(QStringLiteral("Bright"));

        horizontalLayout_2->addWidget(Bright);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        Slider_Contrast = new QSlider(layoutWidget);
        Slider_Contrast->setObjectName(QStringLiteral("Slider_Contrast"));
        Slider_Contrast->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(Slider_Contrast);

        Contrast = new QLabel(layoutWidget);
        Contrast->setObjectName(QStringLiteral("Contrast"));

        horizontalLayout->addWidget(Contrast);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        combo1 = new QComboBox(groupBox);
        combo1->setObjectName(QStringLiteral("combo1"));
        combo1->setGeometry(QRect(0, 30, 69, 22));

        horizontalLayout_5->addWidget(groupBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        Load_Raw = new QPushButton(layoutWidget);
        Load_Raw->setObjectName(QStringLiteral("Load_Raw"));

        horizontalLayout_5->addWidget(Load_Raw);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        WCandWWname = new QLabel(layoutWidget);
        WCandWWname->setObjectName(QStringLiteral("WCandWWname"));

        verticalLayout_2->addWidget(WCandWWname);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        Slider_WC = new QSlider(layoutWidget);
        Slider_WC->setObjectName(QStringLiteral("Slider_WC"));
        Slider_WC->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(Slider_WC);

        WC = new QLabel(layoutWidget);
        WC->setObjectName(QStringLiteral("WC"));

        horizontalLayout_4->addWidget(WC);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        Slider_WW = new QSlider(layoutWidget);
        Slider_WW->setObjectName(QStringLiteral("Slider_WW"));
        Slider_WW->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(Slider_WW);

        WW = new QLabel(layoutWidget);
        WW->setObjectName(QStringLiteral("WW"));

        horizontalLayout_3->addWidget(WW);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        PB_MedianFilter = new QPushButton(layoutWidget);
        PB_MedianFilter->setObjectName(QStringLiteral("PB_MedianFilter"));

        verticalLayout_3->addWidget(PB_MedianFilter);

        PB_Reset = new QPushButton(layoutWidget);
        PB_Reset->setObjectName(QStringLiteral("PB_Reset"));

        verticalLayout_3->addWidget(PB_Reset);

        PB_Invert_Filter = new QPushButton(layoutWidget);
        PB_Invert_Filter->setObjectName(QStringLiteral("PB_Invert_Filter"));

        verticalLayout_3->addWidget(PB_Invert_Filter);


        horizontalLayout_5->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1132, 21));
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
        PB_LoadDicom_Image->setText(QApplication::translate("MainWindow", "Load DICOM IMAGE", 0));
        Brightandcontrastname->setText(QApplication::translate("MainWindow", "Brightness and Contrast", 0));
        label->setText(QApplication::translate("MainWindow", "Brightness", 0));
        Bright->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Contrast", 0));
        Contrast->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Alpha Value", 0));
        Load_Raw->setText(QApplication::translate("MainWindow", "Load Raw-Hist Imagin", 0));
        WCandWWname->setText(QApplication::translate("MainWindow", "WC and WW", 0));
        label_3->setText(QApplication::translate("MainWindow", "WC", 0));
        WC->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "WW", 0));
        WW->setText(QString());
        PB_MedianFilter->setText(QApplication::translate("MainWindow", "Median Filter", 0));
        PB_Reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        PB_Invert_Filter->setText(QApplication::translate("MainWindow", "Invert Filter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
