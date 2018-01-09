#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int draw_uniform_rectangle (uint x, uint y, uint sx, uint sy, uint color, Mat image){

  Rect r(x,y,sx,sy);
  Mat crop_image;
  crop_image = image(r);
  crop_image = Scalar(color);
  return 0;
}

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
        image_sym.at<uchar>(i, j) = intensity[0];
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
    image = imread(argv[1], 0);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    Mat image_sym = symetry_diag(image);
    //std::cout << image_sym << std::endl;
    imwrite("sym.png", image_sym);
    return 0;
}
