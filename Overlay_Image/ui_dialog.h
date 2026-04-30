/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView1;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PB_LoadImage1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *PB_CheckerBoard;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PB_Quad;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_Overlay;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *PB_Togglecheck;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *PB_Toggle;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_LoadImage2;
    QGraphicsView *graphicsView3;
    QGraphicsView *graphicsView2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1132, 891);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 361, 191));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView1 = new QGraphicsView(layoutWidget);
        graphicsView1->setObjectName(QStringLiteral("graphicsView1"));

        verticalLayout->addWidget(graphicsView1);


        horizontalLayout_3->addLayout(verticalLayout);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 840, 891, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PB_LoadImage1 = new QPushButton(layoutWidget1);
        PB_LoadImage1->setObjectName(QStringLiteral("PB_LoadImage1"));

        horizontalLayout_2->addWidget(PB_LoadImage1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        PB_CheckerBoard = new QPushButton(layoutWidget1);
        PB_CheckerBoard->setObjectName(QStringLiteral("PB_CheckerBoard"));

        horizontalLayout_2->addWidget(PB_CheckerBoard);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        PB_Quad = new QPushButton(layoutWidget1);
        PB_Quad->setObjectName(QStringLiteral("PB_Quad"));

        horizontalLayout_2->addWidget(PB_Quad);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        PB_Overlay = new QPushButton(layoutWidget1);
        PB_Overlay->setObjectName(QStringLiteral("PB_Overlay"));

        horizontalLayout_2->addWidget(PB_Overlay);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        PB_Togglecheck = new QPushButton(layoutWidget1);
        PB_Togglecheck->setObjectName(QStringLiteral("PB_Togglecheck"));
        PB_Togglecheck->setCheckable(true);
        PB_Togglecheck->setChecked(true);

        horizontalLayout_2->addWidget(PB_Togglecheck);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCheckable(false);
        pushButton->setChecked(false);

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        PB_Toggle = new QPushButton(layoutWidget1);
        PB_Toggle->setObjectName(QStringLiteral("PB_Toggle"));
        PB_Toggle->setCheckable(false);
        PB_Toggle->setChecked(false);

        horizontalLayout_2->addWidget(PB_Toggle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        PB_LoadImage2 = new QPushButton(layoutWidget1);
        PB_LoadImage2->setObjectName(QStringLiteral("PB_LoadImage2"));

        horizontalLayout_2->addWidget(PB_LoadImage2);

        graphicsView3 = new QGraphicsView(Dialog);
        graphicsView3->setObjectName(QStringLiteral("graphicsView3"));
        graphicsView3->setGeometry(QRect(40, 240, 1071, 591));
        graphicsView2 = new QGraphicsView(Dialog);
        graphicsView2->setObjectName(QStringLiteral("graphicsView2"));
        graphicsView2->setGeometry(QRect(710, 30, 391, 191));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        PB_LoadImage1->setText(QApplication::translate("Dialog", "Load Image 1", 0));
        PB_CheckerBoard->setText(QApplication::translate("Dialog", "Checker Board", 0));
        PB_Quad->setText(QApplication::translate("Dialog", "Quadrant", 0));
#ifndef QT_NO_STATUSTIP
        PB_Overlay->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        PB_Overlay->setText(QApplication::translate("Dialog", "Overlay", 0));
        PB_Togglecheck->setText(QApplication::translate("Dialog", "Toggle checked", 0));
        pushButton->setText(QApplication::translate("Dialog", "Toggle bool", 0));
        PB_Toggle->setText(QApplication::translate("Dialog", "Toggle", 0));
        PB_LoadImage2->setText(QApplication::translate("Dialog", "Load Image 2", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
