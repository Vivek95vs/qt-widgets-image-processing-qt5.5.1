#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "myworker.h"
#include <QThread>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QThread *Thread;
    MyWorker *worker;

private slots:

    void onNumberChanged(int);
    void on_PB_START_clicked();

    void on_PB_STOP_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
