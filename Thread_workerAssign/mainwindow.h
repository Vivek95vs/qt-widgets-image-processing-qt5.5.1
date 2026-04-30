#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QThread *Thread;
    MainWindow *worker;

private:
    Ui::MainWindow *ui;

 private slots:

    void doWork();
    void on_PB_Start_clicked();
    void on_PB_Stop_clicked();
};

#endif // MAINWINDOW_H
