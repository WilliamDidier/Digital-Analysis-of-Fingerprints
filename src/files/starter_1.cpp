/**
  This is a Doxygen documentation.
  \file starter_1.cpp
  \brief Functions of the Starter 1
  \author Romain C. & Théo M. & Théo L. & William D.
  \ date 2018, January the 16th


*/

#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;
using std::cout;
using std::endl;
/**
  \fn Mat convert_to_float(Mat image)
  \brief Casts the data of a Mat from ints to floats, returning the corresponding header.
  \param image Image that you want to switch to float values
  \return New header pointing to the data casted to floats.
  \author Théo L.
*/
//Mat convert_to_float(Mat & image){
void convert_to_float(Mat & image, Mat & dst){

  //Mat dst;
  image.convertTo(dst, CV_32F, 1.0/255.0);
  //return(dst);
}

/**
  \fn Mat convert_to_int(Mat image)
  \param image Image that you want to switch to int values
  \return New header pointing to the data casted to ints.
  \author Théo L.
*/
//Mat convert_to_int(Mat & image) {
void convert_to_int(Mat & image, Mat &dst) {
  //Mat dst;
  image.convertTo(dst, CV_8UC1, 255);
  //return(dst);
}


/**
  \fn int draw_uniform_rectangle (Mat image, Rect r, float color)
  \brief Draws a rectangle of the given size and color on the image rperesented by image.
  \param Image image on chich you want to insert a rectangle. Has to be casted to float values.
  \param r Region of the image that will be colored. Has to be included in the image
  \param color Floating point nuber corresponding to the color of the rectangle. Has to be between 0.0(black) and 1.0(white)
  \return Nothing : the data is modified through the passed-by copy of the image.
  \author William D.
*/
void draw_uniform_rectangle (Mat image, Rect r, float color){
  image = image(r);
  image = Scalar(color);
}


/**
  \fn symetry_y(Mat &image)
  \brief
  \param &image
  \return
  \author Romain C. & Théo M.
*/
Mat symetry_y(Mat &image) {
    /* returns the symetry along the y axis */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nRows, nCols, CV_32F);
    for (uint i = 0; i < nCols; i++) {
      for (uint j = 0; j < nRows; j++) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);

        //fills 'image_sym' according to the symetry
        image_sym.at<float>(j, nCols - i) = intensity[0];
      }
    }
    return(image_sym);
}

/**
  \fn symetry_x(Mat &image)
  \brief
  \param &image
  \return
  \author Romain C. & Théo M.
*/
Mat symetry_x(Mat &image) {
    /* returns the symetry along the y axis */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nRows, nCols, CV_32F);
    for (uint i = 0; i < nCols; i++) {
      for (uint j = 0; j < nRows; j++) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);
        //fills 'image_sym' according to the symetry
        image_sym.at<float>(nRows-j-1, i) = intensity[0];
      }
    }
    return(image_sym);
}

/**
  \fn symetry_y(Mat &image)
  \brief
  \param &image      if(neg == 1){
        Res = symetry_y(Res);
      }
  \return
  \author Romain C. & Théo M.
*/
Mat symetry_diag(Mat &image) {
    /* returns the symetry along the x/y diagonal */
    int nRows = image.rows;
    int nCols = image.cols;
    Mat image_sym;
    //creation of a Mat with the same size as 'image'
    image_sym.create(nCols, nRows, CV_32F);
    for (uint i = 0; i < nCols; i++) {
      for (uint j = 0; j < nRows; j++) {
        //gets the intensity value of image
        Scalar intensity = image.at<float>(j, i);
        //fills 'image_sym' according to the symetry
        image_sym.at<float>(i, j) = intensity[0];
      }
    }
    return(image_sym);
}
