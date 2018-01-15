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
float coefficient_computation(bool clean_to_weak, Point2f pressure_center, Point2f point);

void change_intensity(Mat &image, Point2f pressure_center, Point2f point);


/* */
void apply_iso(Mat &image);


/* */
Point2f parameters_computation(Mat &image);

bool test_ellipse(Point2f parameters, Point2i pressure_center, Point2i coordinates) {
    float res = pow((coordinates.x - pressure_center.x)/parameters.x, 2);
    res += pow((coordinates.y - pressure_center.y)/parameters.y, 2);
    res = sqrt(res);
    return(res<=1);
}

Mat ellipse(Point2i parameters, Point2i pressure_center, Point2i dimensions) {
    int nRows = dimensions.x;
    int nCols = dimensions.y;
    Mat res;
    res.create(nRows, nCols, CV_32F);
    for (uint i = 0; i < nRows; i++) {
      for (uint j = 0; j < nCols; j++) {
        res.at<float>(j, i) = test_ellipse(parameters, pressure_center, Point2i(i,j)) ? 0. : 1.;
      }
    }
    return(res);
}

void apply_iso(Mat &image);

#endif //MAIN_1_H
