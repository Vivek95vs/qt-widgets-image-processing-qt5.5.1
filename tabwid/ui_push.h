/********************************************************************************
** Form generated from reading UI file 'push.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUSH_H
#define UI_PUSH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_push
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *push)
    {
        if (push->objectName().isEmpty())
            push->setObjectName(QStringLiteral("push"));
        push->resize(502, 476);
        pushButton = new QPushButton(push);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 70, 75, 23));

        retranslateUi(push);

        QMetaObject::connectSlotsByName(push);
    } // setupUi

    void retranslateUi(QWidget *push)
    {
        push->setWindowTitle(QApplication::translate("push", "Form", 0));
        pushButton->setText(QApplication::translate("push", "Dose", 0));
    } // retranslateUi

};

namespace Ui {
    class push: public Ui_push {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUSH_H
