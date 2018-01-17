#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include"starter_1.h"
#include"main_1.h"

using namespace cv;


/**
  This is a Doxygen documentation.
  \file main_1.cpp
  \brief Header for the functions of the Main course 1
  \author Théo L. & William D.
  \ date 2018, January the 15th
*/

float distance_computation(const Point2i pressure_center, Point2i point, bool anisotropic) {
    if (anisotropic) {
        return(sqrt(pow(pressure_center.x - point.x, 2) + pow(pressure_center.y - point.y, 2)));
    } else {
        return(sqrt(pow(pressure_center.x - point.x, 2) + 2*pow(pressure_center.y - point.y, 2)));
    }
}

/**
  \fn float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point)
  \brief Computes the coefficient c(x,y) such that g(x,y) = c(x,y)f(x,y)
  \param clean_to_weak Boolean that indicates which coefficient whould be
   computed, depending on the transformation we are doing
  \param pressure_center The pressure_center of the fingerprint.
  \param point The point (x,y) at which we compute the coefficient c(x,y)
  \return The floating point number c(x,y)
  \author William D.
*/
float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point){
  float distance = sqrt(pow(pressure_center.x - point.x, 2) + pow(pressure_center.y - point.y, 2));
  if (clean_to_weak){
    return exp(sqrt(distance)/10);
  } else {
    return exp(-distance/500);
  }
}

/**
  \fn void change_intensity (Mat &image, Point2i point, float coef)
  \brief Changes the intendity of the image at the point (x,y)
  \param &image Image that will be modified
  \param point The point (x,y) at which we change the intensity
  \param coef Floating point number that multiplies the intensity
  \return Nothing : the data is directly modified by the function.
  \author William D.
*/
void change_intensity (Mat &image, Point2i point, float coef){
  image.at<float>(point) = coef*image.at<float>(point);
}

/**
  \fn bool white_thresholding(Mat &image, Point2i pt, const float threshold)
  \brief Applies a thresholding to the intensity of the image at a given point.
  \param &image Image that will be modified
  \param pt The point (x,y) at which we apply the thresholding
  \param threshold Floating point number such that if the intensity at the
  point (x,y) is greater than the threshold, it is set to 1.0. Has to be <1.0
  \return A boolean that indicates wether or not the threshold has been applied
  \author William D.
*/
bool white_thresholding(Mat &image, Point2i point, const float threshold){
  if (image.at<float>(point) > 0.4){
    image.at<float>(point) = 1.0;
    return true;
  }
  return false;
}


/* applies an isotropic transformation on the image */
/**
  \fn void clean_to_weak_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates the weakening of the pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
void clean_to_weak_iso(Mat &image, const Point2i pressure_center){
  for (unsigned int x = 0; x < image.rows; x++){
    for (unsigned int y = 0; y < image.cols; y++){
      Point2i pt = Point(y,x);
      float coef = coefficient_computation(true, pressure_center, pt);
      change_intensity(image, pt, coef);
    }
  }
}

/**
  \fn void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates a bigger pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
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


/**
  \fn void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates a bigger pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
Point2i fingerprint_boudaries(Mat &image){
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
  return Point2i(y_max, x_min); //g interverti les 2
}

Point2i parameters_computation(Mat &image) {
    Point2i pressure_center;
    Point2i boundaries = fingerprint_boudaries(image);
    Point2i parameters;
    parameters.x = (pressure_center.x - boundaries.x)*3 / 4;
    parameters.y = (pressure_center.y - boundaries.y)*2 / 3;
    return(parameters);
}

/*
    @brief: tests if a given point is in the ellipse or not
    @
 */
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
        res.at<float>(i, j) = test_ellipse(parameters, pressure_center, Point2i(i,j));
      }
    }
    return(res);
}

/* apply an anisotropic transformation on the image */
void apply_iso(Mat &image, Point2i pressure_center) {
    int nRows = image.rows;
    int nCols = image.cols;
    Point2f parameters = parameters_computation(image);
    cout << parameters << endl;
    Mat protected_zone = ellipse(parameters, pressure_center, Point2i(nRows, nCols));
    imwrite("./test_iso_ellipse.png", convert_to_int(protected_zone));
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
