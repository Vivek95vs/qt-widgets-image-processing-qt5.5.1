#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->urlEdit->setText("http://qt.com");
    ui->url->setText("http://qt.com");
//    ui->statusLabel->setWordWrap(true);

    ui->download->setDefault(true);
    ui->cancel->setAutoDefault(false);

    progressDialog = new QProgressDialog(this);

    connect(ui->urlEdit, SIGNAL(textChanged(QString)),
                this, SLOT(enableDownloadButton()));
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cancel_clicked()
{

}

void MainWindow::on_download_clicked()
{
    manager = new QNetworkAccessManager(this);

    // get url
    url = (ui->urlEdit->text());

    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();

    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName)) {
        if (QMessageBox::question(this, tr("HTTP"),
                tr("There already exists a file called %1 in "
                "the current directory. Overwrite?").arg(fileName),
                QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
                == QMessageBox::No)
                return;
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("HTTP"),
                      tr("Unable to save the file %1: %2.")
                      .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

    // used for progressDialog
    // This will be set true when canceled from progress dialog
    httpRequestAborted = false;

    progressDialog->setWindowTitle(tr("HTTP"));
    progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));

    // download button disabled after requesting download
    ui->downloadButton->setEnabled(false);

    startRequest(url);
}
