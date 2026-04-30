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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *loadcsv;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;
    QFrame *frame;
    QLineEdit *lineEdit;
    QPushButton *search;
    QLabel *label;
    QPushButton *Save;
    QPushButton *Edit;
    QComboBox *columnNum;
    QPushButton *sort;
    QComboBox *sortorder;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1183, 892);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        loadcsv = new QPushButton(centralWidget);
        loadcsv->setObjectName(QStringLiteral("loadcsv"));

        gridLayout->addWidget(loadcsv, 5, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 1, 1, 1);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 4, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 130, 351, 21));
        search = new QPushButton(frame);
        search->setObjectName(QStringLiteral("search"));
        search->setGeometry(QRect(420, 130, 131, 23));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 130, 31, 21));
        Save = new QPushButton(frame);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setGeometry(QRect(320, 210, 221, 23));
        Edit = new QPushButton(frame);
        Edit->setObjectName(QStringLiteral("Edit"));
        Edit->setGeometry(QRect(40, 210, 231, 23));
        columnNum = new QComboBox(frame);
        columnNum->setObjectName(QStringLiteral("columnNum"));
        columnNum->setGeometry(QRect(140, 50, 111, 21));
        sort = new QPushButton(frame);
        sort->setObjectName(QStringLiteral("sort"));
        sort->setGeometry(QRect(30, 50, 75, 23));
        sortorder = new QComboBox(frame);
        sortorder->setObjectName(QStringLiteral("sortorder"));
        sortorder->setGeometry(QRect(350, 50, 111, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 50, 47, 13));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 171, 16));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 100, 171, 16));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 180, 171, 16));

        gridLayout->addWidget(frame, 4, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1183, 21));
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
        loadcsv->setText(QApplication::translate("MainWindow", "Load csv", 0));
        search->setText(QApplication::translate("MainWindow", "Search", 0));
        label->setText(QApplication::translate("MainWindow", "Find:", 0));
        Save->setText(QApplication::translate("MainWindow", "Save", 0));
        Edit->setText(QApplication::translate("MainWindow", "Edit", 0));
        sort->setText(QApplication::translate("MainWindow", "Sort ", 0));
        sortorder->clear();
        sortorder->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "Ascending Order", 0)
         << QApplication::translate("MainWindow", "Descending Order", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "Order:", 0));
        label_3->setText(QApplication::translate("MainWindow", "1) Each Column Sorting", 0));
        label_4->setText(QApplication::translate("MainWindow", "2) CLTR + F and  search", 0));
        label_5->setText(QApplication::translate("MainWindow", "3) Edit & Save", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
