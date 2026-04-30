#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <itkImage.h>
//#include <itkImageFileReader.h>
//#include <itkResampleImageFilter.h>
//#include <itkImageFileWriter.h>
//#include "itkNearestNeighborInterpolateImageFunction.h"
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/ofstd/ofstd.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    std::ifstream input("input.raw", std::ios::binary);
    if (!input) {
        std::cerr << "Error: Unable to open input.raw." << std::endl;
       // return -1;
    }

    // Specify the dimensions of the original image.
    int originalWidth = 800; // Replace with the actual width.
    int originalHeight = 600; // Replace with the actual height.

    // Specify the dimensions of the desired FoV.
    int newWidth = 450; // Replace with the desired width.
    int newHeight = 338; // Replace with the desired height.

    // Read the raw image data into a vector.
    std::vector<unsigned char> imageData(originalWidth * originalHeight);
    input.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
    input.close();

    // Calculate the scaling factors for resizing.
    double xScale = static_cast<double>(newWidth) / originalWidth;
    double yScale = static_cast<double>(newHeight) / originalHeight;

    // Create a vector to hold the resized image data.
    std::vector<unsigned char> resizedImageData(newWidth * newHeight);

    // Resize the image using nearest-neighbor interpolation.
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int sourceX = static_cast<int>(x / xScale);
            int sourceY = static_cast<int>(y / yScale);
            int sourceIndex = sourceY * originalWidth + sourceX;
            int targetIndex = y * newWidth + x;
            resizedImageData[targetIndex] = imageData[sourceIndex];
        }
    }

    // Save the resized image to a file.
    std::ofstream output("output.raw", std::ios::binary);
    if (!output) {
        std::cerr << "Error: Unable to open output.raw for writing." << std::endl;
        //return -1;
    }
    output.write(reinterpret_cast<const char*>(resizedImageData.data()), resizedImageData.size());
    output.close();

    std::cout << "Resized raw image saved as output.raw." << std::endl;

    //return 0;
}

