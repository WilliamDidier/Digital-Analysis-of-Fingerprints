#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include"starter_1.h"
#include"main_1.h"

using namespace cv;


float distance_computation(const Point2i pressure_center, Point2i point, bool anisotropic) {
    if (!anisotropic) {
        return(sqrt(pow(pressure_center.x - point.x, 2) + pow(pressure_center.y - point.y, 2)));
    } else {
        return(sqrt(pow(pressure_center.x - point.x, 2) + 2*pow(pressure_center.y - point.y, 2)));
    }
}


float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point){
  float distance = distance_computation(pressure_center, point, false);
  if (clean_to_weak){
    return exp(sqrt(distance)/10);
  } else {
    return exp(-distance/500);
  }
}


void change_intensity (Mat &image, Point2i point, float coef){
  image.at<float>(point) = coef*image.at<float>(point);
}


bool white_thresholding(Mat &image, Point2i point, const float threshold){
  if (image.at<float>(point) > 0.4){
    image.at<float>(point) = 1.0;
    return true;
  }
  return false;
}


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


int fingerprint_boundaries_x(Mat &image){
  for (int i = 0; i < image.cols; i++){
    for (int j = 0; j < image.rows; j++){
      if (image.at<float>(j,i) < 0.2){
         return i;
      }
    }
  }
  cout << "No x found..." << endl;
  return(-1);
}

int fingerprint_boundaries_y(Mat &image){
  for (int j = 0; j < image.rows; j++){
    for (int i = 0; i < image.cols; i++){
      if (image.at<float>(j,i) < 0.2){
         return j;
      }
    }
  }
  cout << "No y found..." << endl;
  return(-1);
}

Point2i fingerprint_boundaries(Mat &image) {
  int x = fingerprint_boundaries_x(image);
  int y = fingerprint_boundaries_y(image);
  Point2i res(y, x);
  return res;
}


Point2i pressure_center_computation(Mat &image){
    Mat gblur;
    image.copyTo(gblur);
    GaussianBlur(image, gblur, Size(17, 17), 0, 0);
    double minVal = 0;
    double maxVal = 0;
    Point minLoc, maxLoc;
    minMaxLoc(gblur, &minVal, &maxVal, &minLoc, &maxLoc);
    Point2i pressure_center(minLoc.y, minLoc.x);
    return pressure_center;
}


Point2i parameters_computation(Mat &image, Point2i pressure_center) {
    Point2i boundaries = fingerprint_boundaries(image);
    Point2i parameters;
    parameters.x = (pressure_center.x - boundaries.x)*2 / 3;
    parameters.y = (pressure_center.y - boundaries.y)*3 / 4;
    return(parameters);
}


bool test_ellipse(Point2f parameters, Point2i const pressure_center, Point2i coordinates) {
    float res = pow((coordinates.x - pressure_center.x)/parameters.x, 2); // à refaire avec la fonction distance
    res += pow((coordinates.y - pressure_center.y)/parameters.y, 2);
    res = sqrt(res);
    return(res>=1);
}


Mat ellipse(Point2i parameters, Point2i const pressure_center, Point2i dimensions) {
    int nRows = dimensions.x;
    int nCols = dimensions.y;
    Mat res;
    res.create(nRows, nCols, CV_32F);
    for (uint j = 0; j < nCols; j++) {
      for (uint i = 0; i < nRows; i++) {
        res.at<float>(i, j) = test_ellipse(parameters, pressure_center, Point2i(i,j));
      }
    }
    return(res);
}


void apply_aniso(Mat &image, Point2i const pressure_center) {
    int nRows = image.rows;
    int nCols = image.cols;
    Point2f parameters = parameters_computation(image, pressure_center);
    cout << parameters << endl;
    Mat protected_zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));
    //imwrite("../output/test_iso_ellipse.png", convert_to_int(protected_zone));
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
