#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setDisabled(true);
    ui->search->setDisabled(true);
    ui->Save->setDisabled(true);
    ui->columnNum->setDisabled(true);
    ui->sortorder->setDisabled(true);
//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    csvModel = new QStandardItemModel(this);
    msg= new QMessageBox(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

void MainWindow::on_loadcsv_clicked()
{

    ui->tableView->setModel(csvModel);
//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFile file("test1.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QList<QStandardItem *> standardItemsList;
            for (QString item : line.split(",")) {
                standardItemsList.append(new QStandardItem(item));
            }

            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
}

void MainWindow::on_search_clicked()
{
    qDebug()<<"count val"<<val;
    for (int index = 0; index < csvModel->columnCount(); index++)
    {
        QList<QStandardItem*> foundLst = csvModel->findItems(val.trimmed(), Qt::MatchExactly, index);
        count = foundLst.count();
        qDebug()<<"count val--1"<<count<<index;

        if(count>0)
        {
                qDebug()<<"count"<<count;
                for(int k=0; k<count; k++)
                {
                     QModelIndex modelIndex = csvModel->indexFromItem(foundLst[k]);
//                     qDebug()<< "column= " << index << "row=" << modelIndex.row();
                    ((QStandardItemModel*)modelIndex.model())->item(modelIndex.row(),index)->setData(QBrush(Qt::green),Qt::BackgroundRole);

                     return;
                }
        }
    }

    if(count==0)
    {
       //qDebug()<<"value"<<count;
       msg->setText("No Data found");
       msg->show();
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    for (int index = 0; index < csvModel->columnCount(); index++)
    {
        QList<QStandardItem*> foundLst = csvModel->findItems(val, Qt::MatchExactly, index);
        count = foundLst.count();
        //qDebug()<<"count val"<<count<<index;
        if(count>0)
        {
                //qDebug()<<"count"<<count;
                for(int k=0; k<count; k++)
                {
                     QModelIndex modelIndex = csvModel->indexFromItem(foundLst[k]);
                     //qDebug()<< "column= " << index << "row=" << modelIndex.row();
                    ((QStandardItemModel*)modelIndex.model())->item(modelIndex.row(),index)->setData(QBrush(Qt::white),Qt::BackgroundRole);
                }
        }

    }
    val= ui->lineEdit->text().trimmed();

    qDebug()<<"val"<<val;
}

void MainWindow::searchval()
{
    ui->frame->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->type()==QKeyEvent::KeyPress)
    {
        if(event->matches(QKeySequence::Find))
        {
        ui->lineEdit->setEnabled(true);
        ui->search->setEnabled(true);
        }
    }
}

void MainWindow::on_Save_clicked()
{
    QString textData;
    int rows = csvModel->rowCount();
    int columns = csvModel->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += csvModel->data(csvModel->index(i,j)).toString();
                textData += "," ;
        }
        textData += "\n";
    }

    QFile csvFile("test1.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void MainWindow::on_Edit_clicked()
{
//    on_lineEdit_editingFinished();

    ui->Save->setEnabled(true);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void MainWindow::on_sort_clicked()
{
//    on_lineEdit_editingFinished();

    ui->columnNum->clear();
    ui->columnNum->setEnabled(true);
    for (int i = 0; i < csvModel->columnCount(); i++)
    {
        QString data = QString::number(i);
        ui->columnNum->addItem(data);
    }
}

void MainWindow::on_columnNum_currentIndexChanged(int num)
{
    selectedcolumn = num;
    ui->sortorder->setEnabled(true);
    ui->sortorder->setCurrentText("");
}

void MainWindow::on_sortorder_currentIndexChanged(const QString &arg1)
{
    qDebug()<<"colnum"<<selectedcolumn;

    if(arg1 == "Ascending Order")
    {
        ui->tableView->sortByColumn(selectedcolumn,Qt::AscendingOrder);
    }

    else if(arg1 == "Descending Order")
    {
        ui->tableView->sortByColumn(selectedcolumn,Qt::DescendingOrder);
    }

    else
    {

    }
}
