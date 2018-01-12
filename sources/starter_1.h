#ifndef STARTER_1
#define STARTER_1

#include <opencv2/opencv.hpp>

using namespace cv;

Mat convert_to_float(Mat image){
  Mat dst;
  image.convertTo(dst, CV_32F, 1.0/255.0);
  return dst;
}

int draw_uniform_rectangle (Mat image, Rect r, float color){
  //assert ((x+sx <= image.cols) && (y+sy <= image.rows));
  image = image(r);
  image = Scalar(color);
  return 0;
}

Mat symetry_y(Mat &image) {
    /* returns the symetry along the y axis */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nRows, nCols, CV_32F);
    for (uint i = 0; i < nCols; ++i) {
      for (uint j = 0; j < nRows; ++j) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);
        //fills 'image_sym' according to the symetry
        image_sym.at<float>(j, nCols - i) = intensity[0];
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
    image_sym.create(nCols, nRows, CV_32F);
    for (uint i = 0; i < nCols; ++i) {
      for (uint j = 0; j < nRows; ++j) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);
        //fills 'image_sym' according to the symetry
        image_sym.at<float>(i, j) = intensity[0];
      }
    }
    return(image_sym);
}


#endif
