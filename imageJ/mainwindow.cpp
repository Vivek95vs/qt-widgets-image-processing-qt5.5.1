#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Setup sliders for minimum, maximum, brightness, and contrast
//    minSlider = createSlider(0, 255, "Minimum");
//    maxSlider = createSlider(0, 255, "Maximum", 255);
//    brightnessSlider = createSlider(-100, 100, "Brightness");
//    contrastSlider = createSlider(-100, 100, "Contrast");

    minSlider = new QSlider(Qt::Horizontal);
    minSlider->setRange(0, 255);
    minSlider->setValue(0);
    minSlider->setToolTip("Minimum");

    maxSlider = new QSlider(Qt::Horizontal);
    maxSlider->setRange(0, 255);
    maxSlider->setValue(255);
    maxSlider->setToolTip("Maximum");

    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setRange(-100, 100);
    brightnessSlider->setValue(0);
    brightnessSlider->setToolTip("Brightness");

    contrastSlider = new QSlider(Qt::Horizontal);
    contrastSlider->setRange(-100, 100);
    contrastSlider->setValue(0);
    contrastSlider->setToolTip("Contrast");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(minSlider);
    layout->addWidget(maxSlider);
    layout->addWidget(brightnessSlider);
    layout->addWidget(contrastSlider);
    setLayout(layout);

    // Connect signals to update the image
    connect(minSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);
    connect(maxSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);
    connect(brightnessSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);
    connect(contrastSlider, &QSlider::valueChanged, this, &MainWindow::updateImage);

    // Initial update
    updateImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}


cv::Mat MainWindow::adjustImage(const cv::Mat &image, int min, int max, int brightness, int contrast) {
    cv::Mat adjustedImage;

    // Apply brightness and contrast adjustments
    double alpha = 1.0 + contrast / 100.0;  // Contrast scaling factor
    double beta = brightness;              // Brightness offset
    image.convertTo(adjustedImage, CV_8U, alpha, beta);

    // Apply minimum and maximum intensity thresholds
    cv::threshold(adjustedImage, adjustedImage, max, 255, cv::THRESH_TRUNC); // Cap at max
    cv::threshold(adjustedImage, adjustedImage, min, 255, cv::THRESH_TOZERO); // Set below min to 0

    return adjustedImage;
}

QImage MainWindow::matToQImage(const cv::Mat &mat) {
    if (mat.channels() == 1)
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    else if (mat.channels() == 3)
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    else
        return QImage();
}

void MainWindow::updateImage() {

    originalImage = cv::imread("D:\\logo_pmt.png", cv::IMREAD_GRAYSCALE); // Adjust the path and format
    if (originalImage.empty()) {
        qWarning("Failed to load image!");
        return;
    }

    // Convert to 8-bit grayscale if needed
    if (originalImage.depth() != CV_8U)
        originalImage.convertTo(originalImage, CV_8U);

    // Setup QLabel to display the image
    imageLabel = new QLabel;
    imageLabel->setAlignment(Qt::AlignCenter);
//    if (originalImage.empty())
//        return;

    int min = minSlider->value();
    int max = maxSlider->value();
    int brightness = brightnessSlider->value();
    int contrast = contrastSlider->value();

    cv::Mat newImage = adjustImage(originalImage, min, max, brightness, contrast);
    imageLabel->setPixmap(QPixmap::fromImage(matToQImage(newImage)));
}
