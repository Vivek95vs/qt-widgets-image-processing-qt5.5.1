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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QPushButton *displayImage;
    QPushButton *deleteLines;
    QPushButton *lineSelection;
    QPushButton *drawLine;
    QPushButton *drawRectangle;
    QPushButton *drawEllipse;
    QPushButton *drawPolygon;
    QPushButton *brushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1014, 710);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(Dialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 9);

        displayImage = new QPushButton(Dialog);
        displayImage->setObjectName(QStringLiteral("displayImage"));

        gridLayout->addWidget(displayImage, 1, 0, 1, 1);

        deleteLines = new QPushButton(Dialog);
        deleteLines->setObjectName(QStringLiteral("deleteLines"));

        gridLayout->addWidget(deleteLines, 1, 1, 1, 1);

        lineSelection = new QPushButton(Dialog);
        lineSelection->setObjectName(QStringLiteral("lineSelection"));

        gridLayout->addWidget(lineSelection, 1, 2, 1, 1);

        drawLine = new QPushButton(Dialog);
        drawLine->setObjectName(QStringLiteral("drawLine"));

        gridLayout->addWidget(drawLine, 1, 3, 1, 1);

        drawRectangle = new QPushButton(Dialog);
        drawRectangle->setObjectName(QStringLiteral("drawRectangle"));

        gridLayout->addWidget(drawRectangle, 1, 4, 1, 1);

        drawEllipse = new QPushButton(Dialog);
        drawEllipse->setObjectName(QStringLiteral("drawEllipse"));

        gridLayout->addWidget(drawEllipse, 1, 5, 1, 1);

        drawPolygon = new QPushButton(Dialog);
        drawPolygon->setObjectName(QStringLiteral("drawPolygon"));

        gridLayout->addWidget(drawPolygon, 1, 6, 1, 1);

        brushButton = new QPushButton(Dialog);
        brushButton->setObjectName(QStringLiteral("brushButton"));

        gridLayout->addWidget(brushButton, 1, 7, 1, 1);

        horizontalSpacer = new QSpacerItem(371, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 8, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        displayImage->setText(QApplication::translate("Dialog", "Display Image", 0));
        deleteLines->setText(QApplication::translate("Dialog", "Delete All Items", 0));
        lineSelection->setText(QApplication::translate("Dialog", "Delete Selected Items", 0));
        drawLine->setText(QApplication::translate("Dialog", "Draw Line", 0));
        drawRectangle->setText(QApplication::translate("Dialog", "Draw Rectangle", 0));
        drawEllipse->setText(QApplication::translate("Dialog", "Draw Ellipse", 0));
        drawPolygon->setText(QApplication::translate("Dialog", "Draw Polygon", 0));
        brushButton->setText(QApplication::translate("Dialog", "Brush", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
