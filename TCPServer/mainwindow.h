#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<client.h>
#include <QMainWindow>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
   QTcpSocket *clsock;
    ~MainWindow();

private slots:
    void on_clientclick_clicked();
    void isConnected();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
