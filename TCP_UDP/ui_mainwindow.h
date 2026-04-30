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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line_6;
    QTabWidget *tabWidget;
    QWidget *tab_tcpClient;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_targetIP;
    QLineEdit *lineEdit_TcpClientTargetIP;
    QFrame *line_4;
    QLabel *label_targetPort;
    QLineEdit *lineEdit_TcpClientTargetPort;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_TcpClient;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *textBrowser_TcpClientMessage;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_TcpClientSend;
    QFrame *line_5;
    QPushButton *button_TcpClientSend;
    QWidget *tab_tcpServer;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_listenPort;
    QLineEdit *lineEdit_TcpServerListenPort;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_TcpServer;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_8;
    QTextBrowser *textBrowser_TcpServerMessage;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_TcpServerSend;
    QFrame *line_7;
    QPushButton *button_TcpServerSend;
    QWidget *tab_udp;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_UdpListenPort;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *button_Udp;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_11;
    QTextBrowser *textBrowser_UdpMessage;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *lineEdit_UdpTargetIP;
    QFrame *line_2;
    QLabel *label_4;
    QLineEdit *lineEdit_UdpTargetPort;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_UdpSend;
    QFrame *line_8;
    QPushButton *button_UdpSend;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 600);
        MainWindow->setMinimumSize(QSize(500, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_6);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab_tcpClient = new QWidget();
        tab_tcpClient->setObjectName(QStringLiteral("tab_tcpClient"));
        verticalLayout_5 = new QVBoxLayout(tab_tcpClient);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_4 = new QGroupBox(tab_tcpClient);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_targetIP = new QLabel(groupBox_4);
        label_targetIP->setObjectName(QStringLiteral("label_targetIP"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_targetIP->sizePolicy().hasHeightForWidth());
        label_targetIP->setSizePolicy(sizePolicy);
        label_targetIP->setMinimumSize(QSize(0, 0));
        label_targetIP->setBaseSize(QSize(0, 0));

        horizontalLayout_7->addWidget(label_targetIP);

        lineEdit_TcpClientTargetIP = new QLineEdit(groupBox_4);
        lineEdit_TcpClientTargetIP->setObjectName(QStringLiteral("lineEdit_TcpClientTargetIP"));
        lineEdit_TcpClientTargetIP->setMinimumSize(QSize(150, 0));
        lineEdit_TcpClientTargetIP->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_7->addWidget(lineEdit_TcpClientTargetIP);

        line_4 = new QFrame(groupBox_4);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_4);

        label_targetPort = new QLabel(groupBox_4);
        label_targetPort->setObjectName(QStringLiteral("label_targetPort"));
        sizePolicy.setHeightForWidth(label_targetPort->sizePolicy().hasHeightForWidth());
        label_targetPort->setSizePolicy(sizePolicy);
        label_targetPort->setMinimumSize(QSize(0, 0));

        horizontalLayout_7->addWidget(label_targetPort);

        lineEdit_TcpClientTargetPort = new QLineEdit(groupBox_4);
        lineEdit_TcpClientTargetPort->setObjectName(QStringLiteral("lineEdit_TcpClientTargetPort"));
        lineEdit_TcpClientTargetPort->setMinimumSize(QSize(80, 0));
        lineEdit_TcpClientTargetPort->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(lineEdit_TcpClientTargetPort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        button_TcpClient = new QPushButton(groupBox_4);
        button_TcpClient->setObjectName(QStringLiteral("button_TcpClient"));

        horizontalLayout_7->addWidget(button_TcpClient);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_5->addWidget(groupBox_4);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_4);

        groupBox_2 = new QGroupBox(tab_tcpClient);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        textBrowser_TcpClientMessage = new QTextBrowser(groupBox_2);
        textBrowser_TcpClientMessage->setObjectName(QStringLiteral("textBrowser_TcpClientMessage"));

        verticalLayout_4->addWidget(textBrowser_TcpClientMessage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_TcpClientSend = new QLineEdit(groupBox_2);
        lineEdit_TcpClientSend->setObjectName(QStringLiteral("lineEdit_TcpClientSend"));

        horizontalLayout->addWidget(lineEdit_TcpClientSend);

        line_5 = new QFrame(groupBox_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        button_TcpClientSend = new QPushButton(groupBox_2);
        button_TcpClientSend->setObjectName(QStringLiteral("button_TcpClientSend"));

        horizontalLayout->addWidget(button_TcpClientSend);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(groupBox_2);

        tabWidget->addTab(tab_tcpClient, QString());
        tab_tcpServer = new QWidget();
        tab_tcpServer->setObjectName(QStringLiteral("tab_tcpServer"));
        verticalLayout_7 = new QVBoxLayout(tab_tcpServer);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBox = new QGroupBox(tab_tcpServer);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_listenPort = new QLabel(groupBox);
        label_listenPort->setObjectName(QStringLiteral("label_listenPort"));
        sizePolicy.setHeightForWidth(label_listenPort->sizePolicy().hasHeightForWidth());
        label_listenPort->setSizePolicy(sizePolicy);
        label_listenPort->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(label_listenPort);

        lineEdit_TcpServerListenPort = new QLineEdit(groupBox);
        lineEdit_TcpServerListenPort->setObjectName(QStringLiteral("lineEdit_TcpServerListenPort"));
        lineEdit_TcpServerListenPort->setMinimumSize(QSize(80, 0));
        lineEdit_TcpServerListenPort->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(lineEdit_TcpServerListenPort);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        button_TcpServer = new QPushButton(groupBox);
        button_TcpServer->setObjectName(QStringLiteral("button_TcpServer"));

        horizontalLayout_3->addWidget(button_TcpServer);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_7->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer);

        groupBox_5 = new QGroupBox(tab_tcpServer);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_8 = new QVBoxLayout(groupBox_5);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        textBrowser_TcpServerMessage = new QTextBrowser(groupBox_5);
        textBrowser_TcpServerMessage->setObjectName(QStringLiteral("textBrowser_TcpServerMessage"));

        verticalLayout_8->addWidget(textBrowser_TcpServerMessage);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_TcpServerSend = new QLineEdit(groupBox_5);
        lineEdit_TcpServerSend->setObjectName(QStringLiteral("lineEdit_TcpServerSend"));

        horizontalLayout_2->addWidget(lineEdit_TcpServerSend);

        line_7 = new QFrame(groupBox_5);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_7);

        button_TcpServerSend = new QPushButton(groupBox_5);
        button_TcpServerSend->setObjectName(QStringLiteral("button_TcpServerSend"));

        horizontalLayout_2->addWidget(button_TcpServerSend);


        verticalLayout_8->addLayout(horizontalLayout_2);


        verticalLayout_7->addWidget(groupBox_5);

        tabWidget->addTab(tab_tcpServer, QString());
        tab_udp = new QWidget();
        tab_udp->setObjectName(QStringLiteral("tab_udp"));
        verticalLayout_9 = new QVBoxLayout(tab_udp);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        groupBox_6 = new QGroupBox(tab_udp);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_10 = new QVBoxLayout(groupBox_6);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_UdpListenPort = new QLineEdit(groupBox_6);
        lineEdit_UdpListenPort->setObjectName(QStringLiteral("lineEdit_UdpListenPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_UdpListenPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpListenPort->setSizePolicy(sizePolicy1);
        lineEdit_UdpListenPort->setMinimumSize(QSize(80, 0));
        lineEdit_UdpListenPort->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(lineEdit_UdpListenPort);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        button_Udp = new QPushButton(groupBox_6);
        button_Udp->setObjectName(QStringLiteral("button_Udp"));

        horizontalLayout_4->addWidget(button_Udp);


        verticalLayout_10->addLayout(horizontalLayout_4);


        verticalLayout_9->addWidget(groupBox_6);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_5);

        groupBox_8 = new QGroupBox(tab_udp);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_11 = new QVBoxLayout(groupBox_8);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        textBrowser_UdpMessage = new QTextBrowser(groupBox_8);
        textBrowser_UdpMessage->setObjectName(QStringLiteral("textBrowser_UdpMessage"));

        verticalLayout_11->addWidget(textBrowser_UdpMessage);

        groupBox_7 = new QGroupBox(groupBox_8);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_12 = new QVBoxLayout(groupBox_7);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(groupBox_7);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_8->addWidget(label);

        lineEdit_UdpTargetIP = new QLineEdit(groupBox_7);
        lineEdit_UdpTargetIP->setObjectName(QStringLiteral("lineEdit_UdpTargetIP"));
        sizePolicy1.setHeightForWidth(lineEdit_UdpTargetIP->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetIP->setSizePolicy(sizePolicy1);
        lineEdit_UdpTargetIP->setMinimumSize(QSize(200, 0));
        lineEdit_UdpTargetIP->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_8->addWidget(lineEdit_UdpTargetIP);

        line_2 = new QFrame(groupBox_7);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_2);

        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        lineEdit_UdpTargetPort = new QLineEdit(groupBox_7);
        lineEdit_UdpTargetPort->setObjectName(QStringLiteral("lineEdit_UdpTargetPort"));
        lineEdit_UdpTargetPort->setEnabled(true);
        sizePolicy1.setHeightForWidth(lineEdit_UdpTargetPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetPort->setSizePolicy(sizePolicy1);
        lineEdit_UdpTargetPort->setMinimumSize(QSize(80, 0));
        lineEdit_UdpTargetPort->setMaximumSize(QSize(80, 16777215));
        lineEdit_UdpTargetPort->setBaseSize(QSize(0, 0));

        horizontalLayout_8->addWidget(lineEdit_UdpTargetPort);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_12->addLayout(horizontalLayout_8);

        line_3 = new QFrame(groupBox_7);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_UdpSend = new QLineEdit(groupBox_7);
        lineEdit_UdpSend->setObjectName(QStringLiteral("lineEdit_UdpSend"));

        horizontalLayout_6->addWidget(lineEdit_UdpSend);

        line_8 = new QFrame(groupBox_7);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_8);

        button_UdpSend = new QPushButton(groupBox_7);
        button_UdpSend->setObjectName(QStringLiteral("button_UdpSend"));

        horizontalLayout_6->addWidget(button_UdpSend);


        verticalLayout_12->addLayout(horizontalLayout_6);


        verticalLayout_11->addWidget(groupBox_7);


        verticalLayout_9->addWidget(groupBox_8);

        tabWidget->addTab(tab_udp, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Socket Test", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Connect to:", 0));
        label_targetIP->setText(QApplication::translate("MainWindow", "IP:", 0));
        label_targetPort->setText(QApplication::translate("MainWindow", "Port:", 0));
        button_TcpClient->setText(QApplication::translate("MainWindow", "Connect", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Message:", 0));
        button_TcpClientSend->setText(QApplication::translate("MainWindow", "Send", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_tcpClient), QApplication::translate("MainWindow", "TCP Client", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Listen on:", 0));
        label_listenPort->setText(QApplication::translate("MainWindow", "Port:", 0));
        button_TcpServer->setText(QApplication::translate("MainWindow", "Start", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Message:", 0));
        button_TcpServerSend->setText(QApplication::translate("MainWindow", "Send", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_tcpServer), QApplication::translate("MainWindow", "TCP Server", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Listen on:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Port:", 0));
        button_Udp->setText(QApplication::translate("MainWindow", "Start", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Message:", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Send to:", 0));
        label->setText(QApplication::translate("MainWindow", "IP:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Port:", 0));
        button_UdpSend->setText(QApplication::translate("MainWindow", "Send", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_udp), QApplication::translate("MainWindow", "UDP", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
