/********************************************************************************
** Form generated from reading UI file 'run_over.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUN_OVER_H
#define UI_RUN_OVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Run_Over
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label;
    QProgressBar *progressBar1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QProgressBar *progressBar2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QProgressBar *progressBar3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *PB_Start;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Terminate;

    void setupUi(QDialog *Run_Over)
    {
        if (Run_Over->objectName().isEmpty())
            Run_Over->setObjectName(QStringLiteral("Run_Over"));
        Run_Over->resize(747, 396);
        widget = new QWidget(Run_Over);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 60, 591, 301));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        progressBar1 = new QProgressBar(widget);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout->addWidget(progressBar1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        progressBar2 = new QProgressBar(widget);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setValue(24);

        horizontalLayout_2->addWidget(progressBar2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        progressBar3 = new QProgressBar(widget);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout_3->addWidget(progressBar3);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        PB_Start = new QPushButton(widget);
        PB_Start->setObjectName(QStringLiteral("PB_Start"));

        horizontalLayout_5->addWidget(PB_Start);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        PB_Terminate = new QPushButton(widget);
        PB_Terminate->setObjectName(QStringLiteral("PB_Terminate"));

        horizontalLayout_5->addWidget(PB_Terminate);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(Run_Over);

        QMetaObject::connectSlotsByName(Run_Over);
    } // setupUi

    void retranslateUi(QDialog *Run_Over)
    {
        Run_Over->setWindowTitle(QApplication::translate("Run_Over", "Run_Over", 0));
        label_4->setText(QApplication::translate("Run_Over", "Producer run", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("Run_Over", "Consumer run", 0));
        label_3->setText(QApplication::translate("Run_Over", "Buffer Level", 0));
        PB_Start->setText(QApplication::translate("Run_Over", "Start", 0));
        PB_Terminate->setText(QApplication::translate("Run_Over", "Terminate", 0));
    } // retranslateUi

};

namespace Ui {
    class Run_Over: public Ui_Run_Over {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUN_OVER_H
