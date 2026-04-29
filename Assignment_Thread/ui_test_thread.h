/********************************************************************************
** Form generated from reading UI file 'test_thread.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_THREAD_H
#define UI_TEST_THREAD_H

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

class Ui_Test_Thread
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *progressBar1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QProgressBar *progressBar2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QProgressBar *progressBar3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *PB_Start;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Stop;

    void setupUi(QDialog *Test_Thread)
    {
        if (Test_Thread->objectName().isEmpty())
            Test_Thread->setObjectName(QStringLiteral("Test_Thread"));
        Test_Thread->resize(773, 531);
        layoutWidget = new QWidget(Test_Thread);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 50, 511, 331));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        progressBar1 = new QProgressBar(layoutWidget);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout->addWidget(progressBar1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        progressBar2 = new QProgressBar(layoutWidget);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setValue(24);

        horizontalLayout_2->addWidget(progressBar2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        progressBar3 = new QProgressBar(layoutWidget);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout_3->addWidget(progressBar3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        PB_Start = new QPushButton(layoutWidget);
        PB_Start->setObjectName(QStringLiteral("PB_Start"));

        horizontalLayout_4->addWidget(PB_Start);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        PB_Stop = new QPushButton(layoutWidget);
        PB_Stop->setObjectName(QStringLiteral("PB_Stop"));

        horizontalLayout_4->addWidget(PB_Stop);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(Test_Thread);

        QMetaObject::connectSlotsByName(Test_Thread);
    } // setupUi

    void retranslateUi(QDialog *Test_Thread)
    {
        Test_Thread->setWindowTitle(QApplication::translate("Test_Thread", "Test_Thread", 0));
        label->setText(QApplication::translate("Test_Thread", "Producer Level", 0));
        label_2->setText(QApplication::translate("Test_Thread", "Consumer Level", 0));
        label_3->setText(QApplication::translate("Test_Thread", "Buffer Level", 0));
        PB_Start->setText(QApplication::translate("Test_Thread", "Start", 0));
        PB_Stop->setText(QApplication::translate("Test_Thread", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class Test_Thread: public Ui_Test_Thread {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_THREAD_H
