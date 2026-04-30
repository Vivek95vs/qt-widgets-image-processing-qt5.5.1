#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include "QDesktopServices"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Download_clicked()
{
    QNetworkAccessManager *manager=new QNetworkAccessManager;
          QString url="https://www.africau.edu/images/default/sample.pdf";
          QNetworkReply *reply = manager->get(QNetworkRequest(url));
          QEventLoop loop;
          connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
          loop.exec();
          QString filename="D:\\INSTALL.txt";
          QFile file(filename);
          file.open(QIODevice::WriteOnly);
          file.write(reply->readAll());
          delete reply;
}

void MainWindow::on_open_clicked()
{
    QString myUrl="https://www.simplilearn.com/ice9/free_resources_article_thumb/what_is_image_Processing.jpg";
//    QString myUrl="https://www.africau.edu/images/default/sample.pdf";
//    QDesktopServices::openUrl(QUrl(myUrl,QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl::fromLocalFile(myUrl));
}
