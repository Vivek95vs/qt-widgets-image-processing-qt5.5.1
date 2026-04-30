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
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PB_LoadImage1;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PB_LoadImage2;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Overlay;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *graphicsView1;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView2;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1121, 850);
        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 780, 911, 41));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PB_LoadImage1 = new QPushButton(widget);
        PB_LoadImage1->setObjectName(QStringLiteral("PB_LoadImage1"));

        horizontalLayout_2->addWidget(PB_LoadImage1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        PB_LoadImage2 = new QPushButton(widget);
        PB_LoadImage2->setObjectName(QStringLiteral("PB_LoadImage2"));

        horizontalLayout_2->addWidget(PB_LoadImage2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        PB_Overlay = new QPushButton(widget);
        PB_Overlay->setObjectName(QStringLiteral("PB_Overlay"));

        horizontalLayout_2->addWidget(PB_Overlay);

        widget1 = new QWidget(Dialog);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(50, 10, 981, 771));
        verticalLayout_4 = new QVBoxLayout(widget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        graphicsView1 = new QGraphicsView(widget1);
        graphicsView1->setObjectName(QStringLiteral("graphicsView1"));

        verticalLayout_3->addWidget(graphicsView1);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphicsView2 = new QGraphicsView(widget1);
        graphicsView2->setObjectName(QStringLiteral("graphicsView2"));

        verticalLayout_2->addWidget(graphicsView2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);

        graphicsView3 = new QGraphicsView(widget1);
        graphicsView3->setObjectName(QStringLiteral("graphicsView3"));

        verticalLayout_4->addWidget(graphicsView3);

        graphicsView3->raise();
        graphicsView2->raise();
        graphicsView1->raise();
        PB_LoadImage1->raise();
        PB_LoadImage2->raise();
        PB_Overlay->raise();
        graphicsView1->raise();
        graphicsView1->raise();
        graphicsView3->raise();
        graphicsView3->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        PB_LoadImage1->setText(QApplication::translate("Dialog", "Load Image 1", 0));
        PB_LoadImage2->setText(QApplication::translate("Dialog", "Load Image 2", 0));
        PB_Overlay->setText(QApplication::translate("Dialog", "Overlay", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
