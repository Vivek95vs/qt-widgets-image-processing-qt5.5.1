/********************************************************************************
** Form generated from reading UI file 'operation_img.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATION_IMG_H
#define UI_OPERATION_IMG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_operation_Img
{
public:
    QGraphicsView *graphicsView;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *PB_LoadImage1;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Overlay;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_Quadrant;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *PB_CheckerBoard;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PB_Toggle;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *PB_Rectangle;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *PB_Ellipse;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *PB_RectChange;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *PB_FreeHand;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *PB_Clearall;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *PB_Delete;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *PB_LoadImage2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PB_HorizRuler;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *PB_Image;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *PB_VertiRuler;
    QWidget *widget;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *operation_Img)
    {
        if (operation_Img->objectName().isEmpty())
            operation_Img->setObjectName(QStringLiteral("operation_Img"));
        operation_Img->resize(1131, 879);
        graphicsView = new QGraphicsView(operation_Img);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 70, 1041, 691));
        layoutWidget = new QWidget(operation_Img);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 840, 1111, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        PB_LoadImage1 = new QPushButton(layoutWidget);
        PB_LoadImage1->setObjectName(QStringLiteral("PB_LoadImage1"));

        horizontalLayout->addWidget(PB_LoadImage1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        PB_Overlay = new QPushButton(layoutWidget);
        PB_Overlay->setObjectName(QStringLiteral("PB_Overlay"));

        horizontalLayout->addWidget(PB_Overlay);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PB_Quadrant = new QPushButton(layoutWidget);
        PB_Quadrant->setObjectName(QStringLiteral("PB_Quadrant"));

        horizontalLayout->addWidget(PB_Quadrant);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        PB_CheckerBoard = new QPushButton(layoutWidget);
        PB_CheckerBoard->setObjectName(QStringLiteral("PB_CheckerBoard"));

        horizontalLayout->addWidget(PB_CheckerBoard);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PB_Toggle = new QPushButton(layoutWidget);
        PB_Toggle->setObjectName(QStringLiteral("PB_Toggle"));
        PB_Toggle->setCheckable(true);
        PB_Toggle->setChecked(false);

        horizontalLayout->addWidget(PB_Toggle);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        PB_Rectangle = new QPushButton(layoutWidget);
        PB_Rectangle->setObjectName(QStringLiteral("PB_Rectangle"));

        horizontalLayout->addWidget(PB_Rectangle);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        PB_Ellipse = new QPushButton(layoutWidget);
        PB_Ellipse->setObjectName(QStringLiteral("PB_Ellipse"));

        horizontalLayout->addWidget(PB_Ellipse);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        PB_RectChange = new QPushButton(layoutWidget);
        PB_RectChange->setObjectName(QStringLiteral("PB_RectChange"));

        horizontalLayout->addWidget(PB_RectChange);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        PB_FreeHand = new QPushButton(layoutWidget);
        PB_FreeHand->setObjectName(QStringLiteral("PB_FreeHand"));

        horizontalLayout->addWidget(PB_FreeHand);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        PB_Clearall = new QPushButton(layoutWidget);
        PB_Clearall->setObjectName(QStringLiteral("PB_Clearall"));

        horizontalLayout->addWidget(PB_Clearall);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        PB_Delete = new QPushButton(layoutWidget);
        PB_Delete->setObjectName(QStringLiteral("PB_Delete"));

        horizontalLayout->addWidget(PB_Delete);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        PB_LoadImage2 = new QPushButton(layoutWidget);
        PB_LoadImage2->setObjectName(QStringLiteral("PB_LoadImage2"));

        horizontalLayout->addWidget(PB_LoadImage2);

        layoutWidget1 = new QWidget(operation_Img);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 20, 1001, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PB_HorizRuler = new QPushButton(layoutWidget1);
        PB_HorizRuler->setObjectName(QStringLiteral("PB_HorizRuler"));
        PB_HorizRuler->setCheckable(true);
        PB_HorizRuler->setChecked(false);

        horizontalLayout_2->addWidget(PB_HorizRuler);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_13);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_15);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_16);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_14);

        PB_Image = new QPushButton(layoutWidget1);
        PB_Image->setObjectName(QStringLiteral("PB_Image"));

        horizontalLayout_2->addWidget(PB_Image);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);

        PB_VertiRuler = new QPushButton(layoutWidget1);
        PB_VertiRuler->setObjectName(QStringLiteral("PB_VertiRuler"));
        PB_VertiRuler->setCheckable(true);
        PB_VertiRuler->setChecked(false);

        horizontalLayout_2->addWidget(PB_VertiRuler);

        widget = new QWidget(operation_Img);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(360, 770, 321, 61));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 20, 113, 20));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 111, 21));

        retranslateUi(operation_Img);

        QMetaObject::connectSlotsByName(operation_Img);
    } // setupUi

    void retranslateUi(QDialog *operation_Img)
    {
        operation_Img->setWindowTitle(QApplication::translate("operation_Img", "operation_Img", 0));
        PB_LoadImage1->setText(QApplication::translate("operation_Img", "Load Image 1", 0));
        PB_Overlay->setText(QApplication::translate("operation_Img", "Overlay", 0));
        PB_Quadrant->setText(QApplication::translate("operation_Img", "Quadrant", 0));
        PB_CheckerBoard->setText(QApplication::translate("operation_Img", "Checker Board", 0));
        PB_Toggle->setText(QApplication::translate("operation_Img", "Toggle", 0));
        PB_Rectangle->setText(QApplication::translate("operation_Img", "Rectangle", 0));
        PB_Ellipse->setText(QApplication::translate("operation_Img", "Ellipse", 0));
        PB_RectChange->setText(QApplication::translate("operation_Img", "Rect_Change", 0));
        PB_FreeHand->setText(QApplication::translate("operation_Img", "Free Hand", 0));
        PB_Clearall->setText(QApplication::translate("operation_Img", "Clear all", 0));
        PB_Delete->setText(QApplication::translate("operation_Img", "Delete Selected Items", 0));
        PB_LoadImage2->setText(QApplication::translate("operation_Img", "Load Image 2", 0));
        PB_HorizRuler->setText(QApplication::translate("operation_Img", "Horizontal Ruler", 0));
        pushButton->setText(QApplication::translate("operation_Img", "Text", 0));
        pushButton_2->setText(QApplication::translate("operation_Img", "Delete seleted Text", 0));
        pushButton_3->setText(QApplication::translate("operation_Img", "Redraw text", 0));
        PB_Image->setText(QApplication::translate("operation_Img", "Load Mimage", 0));
        PB_VertiRuler->setText(QApplication::translate("operation_Img", "Vertical Ruler", 0));
        label->setText(QApplication::translate("operation_Img", "Diameter of circle :", 0));
    } // retranslateUi

};

namespace Ui {
    class operation_Img: public Ui_operation_Img {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATION_IMG_H
