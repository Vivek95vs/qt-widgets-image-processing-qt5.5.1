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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTableView *tableView;
    QCustomPlot *plot;
    QPushButton *applyPlotWindow;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *xMin_doubleSpinBox;
    QDoubleSpinBox *xMax_doubleSpinBox;
    QDoubleSpinBox *minY_doubleSpinBox;
    QDoubleSpinBox *maxY_doubleSpinBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveChanges_pushButton;
    QPushButton *discardChanges_pushButton;
    QPushButton *browse_pushButton;
    QLabel *CSVFileLabel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1223, 880);
        tableView = new QTableView(Dialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 321, 791));
        plot = new QCustomPlot(Dialog);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(360, 80, 851, 721));
        applyPlotWindow = new QPushButton(Dialog);
        applyPlotWindow->setObjectName(QStringLiteral("applyPlotWindow"));
        applyPlotWindow->setGeometry(QRect(1110, 820, 111, 51));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(370, 850, 731, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        xMin_doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        xMin_doubleSpinBox->setObjectName(QStringLiteral("xMin_doubleSpinBox"));

        horizontalLayout_2->addWidget(xMin_doubleSpinBox);

        xMax_doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        xMax_doubleSpinBox->setObjectName(QStringLiteral("xMax_doubleSpinBox"));
        xMax_doubleSpinBox->setMaximum(10000);

        horizontalLayout_2->addWidget(xMax_doubleSpinBox);

        minY_doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        minY_doubleSpinBox->setObjectName(QStringLiteral("minY_doubleSpinBox"));

        horizontalLayout_2->addWidget(minY_doubleSpinBox);

        maxY_doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        maxY_doubleSpinBox->setObjectName(QStringLiteral("maxY_doubleSpinBox"));
        maxY_doubleSpinBox->setMaximum(10000);

        horizontalLayout_2->addWidget(maxY_doubleSpinBox);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(370, 820, 731, 21));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 820, 321, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        saveChanges_pushButton = new QPushButton(layoutWidget2);
        saveChanges_pushButton->setObjectName(QStringLiteral("saveChanges_pushButton"));
        saveChanges_pushButton->setMaximumSize(QSize(157, 100));

        horizontalLayout->addWidget(saveChanges_pushButton);

        discardChanges_pushButton = new QPushButton(layoutWidget2);
        discardChanges_pushButton->setObjectName(QStringLiteral("discardChanges_pushButton"));
        discardChanges_pushButton->setMaximumSize(QSize(156, 100));

        horizontalLayout->addWidget(discardChanges_pushButton);

        browse_pushButton = new QPushButton(Dialog);
        browse_pushButton->setObjectName(QStringLiteral("browse_pushButton"));
        browse_pushButton->setGeometry(QRect(380, 30, 91, 41));
        CSVFileLabel = new QLabel(Dialog);
        CSVFileLabel->setObjectName(QStringLiteral("CSVFileLabel"));
        CSVFileLabel->setGeometry(QRect(500, 30, 231, 31));
        CSVFileLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        layoutWidget->raise();
        layoutWidget->raise();
        tableView->raise();
        plot->raise();
        layoutWidget->raise();
        applyPlotWindow->raise();
        browse_pushButton->raise();
        CSVFileLabel->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        applyPlotWindow->setText(QApplication::translate("Dialog", "Apply", 0));
        label->setText(QApplication::translate("Dialog", "Min X", 0));
        label_2->setText(QApplication::translate("Dialog", "Max X", 0));
        label_3->setText(QApplication::translate("Dialog", "Min Y", 0));
        label_4->setText(QApplication::translate("Dialog", "Max Y", 0));
        saveChanges_pushButton->setText(QApplication::translate("Dialog", "Save Changes", 0));
        discardChanges_pushButton->setText(QApplication::translate("Dialog", "Discard Changes", 0));
        browse_pushButton->setText(QApplication::translate("Dialog", "Load CSV File", 0));
        CSVFileLabel->setText(QApplication::translate("Dialog", "No File Selected", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
