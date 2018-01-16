/* A REPRENDRE
header file associated to main_1.cpp
    - contains the functions related to the 'Main course 1'
    - the goal is to simulate the blur you get due to finger pressure
      variations
WARNING : the pressure center has to be defined before computations
*/

#ifndef MAIN_1_H
#define MAIN_1_H


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

/* */
float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point){
  float distance = sqrt(pow(pressure_center.x - point.x, 2) + pow(pressure_center.y - point.y, 2));
  if (clean_to_weak){
    return exp(distance/100);
  } else {
    return exp(-distance/500);
  }
}

void change_intensity (Mat &image, Point2i point, float coef){
  image.at<float>(point) = coef*image.at<float>(point);
}

bool white_thresholding(Mat &image, Point2i pt, const float threshold){
  if (image.at<float>(pt) > 0.4){
    image.at<float>(pt) = 1.0;
    return true;
  }
  return false;
}

/* apply an isotropic transformation on the image */
void clean_to_weak_iso(Mat &image, const Point2i pressure_center){
  for (unsigned int x = 0; x < image.rows; x++){
    for (unsigned int y = 0; y < image.cols; y++){
      Point2i pt = Point(y,x);
      float coef = coefficient_computation(true, pressure_center, pt);
      change_intensity(image, pt, coef);
    }
  }
}

void weak_to_clean_iso(Mat &image, const Point2i pressure_center){
  for (unsigned int x = 0; x < image.rows; x++){
    for (unsigned int y = 0; y < image.cols; y++){
      Point2i pt = Point(y,x);
      if  (!white_thresholding(image, pt, 0.4)){
        float coef = coefficient_computation(false, pressure_center, pt);
        change_intensity(image, pt, coef);
      }
    }
  }
}


/* apply an anisotropic transformation on the image */
Point2i parameters_computation(Mat &image){
  int x_min = image.cols;
  int y_max = 0;
  int i = 0;
  int j = 0;
  for (int y = 0; y < image.rows; y++){
    for (int x = 0; x < image.cols; x++){
      if (image.at<float>(y,x) < 0.2){
        if(x < x_min){
          x_min = x;
        }
          y_max = y;
          break;
      }
    }
  }
  return Point2i(x_min, y_max);
}


bool test_ellipse(Point2f parameters, Point2i pressure_center, Point2i coordinates) {
    float res = pow((coordinates.x - pressure_center.x)/parameters.x, 2);
    res += pow((coordinates.y - pressure_center.y)/parameters.y, 2);
    res = sqrt(res);
    return(res>=1);
}

Mat ellipse(Point2i parameters, Point2i pressure_center, Point2i dimensions) {
    int nRows = dimensions.x;
    int nCols = dimensions.y;
    Mat res;
    res.create(nRows, nCols, CV_32F);
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        cout << "i " << i << " j " << j << " " << test_ellipse(parameters, pressure_center, Point2i(i,j)) << endl;
        res.at<float>(i, j) = test_ellipse(parameters, pressure_center, Point2i(i,j));
      }
    }
    return(res);
}

void apply_iso(Mat &image) {
    int nRows = image.rows;
    int nCols = image.cols;
    Point2f parameters = parameters_computation(image);
    Point2f pressure_center;
    Mat protected_zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        if (protected_zone.at<float>(i,j) == 1.) {
            Point2i point(j,i);
            float coef = coefficient_computation(true, pressure_center, point);
            change_intensity(image, point, coef);
        }
      }
    }
}

#endif //MAIN_1_H
