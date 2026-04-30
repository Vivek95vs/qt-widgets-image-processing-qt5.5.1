#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct TagElements
{
    std::string Seq1;
    std::string lastTS;
    std::string stepname1;
    std::string stepparam1;
    std::string stepparam2;
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
        QList<TagElements> *tagList;

private slots:
    void on_read_xml_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
