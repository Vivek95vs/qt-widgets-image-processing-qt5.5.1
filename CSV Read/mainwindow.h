#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "QMessageBox"
#include "QKeyEvent"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString val;
    int count;
    int selectedcolumn;

private slots:
    void on_loadcsv_clicked();

    void on_search_clicked();

    void on_lineEdit_editingFinished();

    void searchval();

//    void on_edit_clicked();

    void on_Save_clicked();

    void on_Edit_clicked();

    void on_sort_clicked();

    void on_columnNum_currentIndexChanged(int num);

    void on_sortorder_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;
    QMessageBox *msg;

protected:
        void keyPressEvent(QKeyEvent *event);


};

#endif // MAINWINDOW_H
