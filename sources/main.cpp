#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter_1.h"
using namespace cv;


Mat symetry_y(Mat &image) {
    /* returns the symetry along the y axis */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nRows, nCols, CV_8UC1);
    for (uint i = 0; i < nCols; ++i) {
      for (uint j = 0; j < nRows; ++j) {
        //gets the intensity value of image
        Scalar intensity = image.at<uchar>(j, i);
        //fills 'image_sym' according to the symetry
        image_sym.at<uchar>(j, nCols - i) = intensity[0];
      }
    }
    return(image_sym);
}

Mat symetry_diag(Mat &image) {
    /* returns the symetry along the x/y diagonal */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nCols, nRows, CV_8UC1);
    for (uint i = 0; i < nCols; ++i) {
      for (uint j = 0; j < nRows; ++j) {
        //gets the intensity value of image
        Scalar intensity = image.at<uchar>(j, i);
        //fills 'image_sym' according to the symetry
      }
    }
    return(image_sym);
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    Mat grey_image;
    cvtColor(image, grey_image, COLOR_BGR2GRAY);
    // convert_to_float(grey_image);
    // draw_uniform_rectangle(570,570,7,100,0.0, grey_image);
    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", grey_image);
    // waitKey(0);
    Mat image_sym = symetry_diag(grey_image);
    //std::cout << image_sym << std::endl;
    imwrite("sym.png", image_sym);

    return 0;
}
