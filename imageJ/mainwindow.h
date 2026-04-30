#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateImage();
private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    cv::Mat originalImage;
    QSlider *minSlider, *maxSlider, *brightnessSlider, *contrastSlider;
    cv::Mat adjustImage(const cv::Mat &image, int min, int max, int brightness, int contrast);
    QImage matToQImage(const cv::Mat &mat);
};

#endif // MAINWINDOW_H
