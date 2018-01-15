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


/* apply an isotropic transformation on the image */
void apply_iso(Mat &image);


/* apply an anisotropic transformation on the image */
Point2f parameters_computation(Mat &image);

Mat ellipse(Point2f parameters, Point2f pressure_center, Point2f dimensions);

void apply_iso(Mat &image);


#endif //MAIN_1_H
