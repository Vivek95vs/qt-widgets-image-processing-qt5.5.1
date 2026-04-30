#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Enhancement_RadSample();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_bufffer_check_clicked();

    void on_buffertest_clicked();

    void on_ImageBuff_return_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
