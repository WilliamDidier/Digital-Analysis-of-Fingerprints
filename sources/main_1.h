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
        if (protected_zone.at<float>(i,j) == 1f) {
            Point2i point(i,j);
            coefficient_computation(true, pressure_center, point);
            change_intensity(image, pressure_center, point);
        }
      }
    }
}

#endif //MAIN_1_H
