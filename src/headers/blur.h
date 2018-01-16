/*
header file associated to blur.cpp
    - contains the functions related to the 'Main course 1'
    - the goal is to simulate the blur you get due to finger pressure
      variations
*/

#ifndef BLUR_H
#define BLUR_H


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void clean_to_weak_iso(Mat &image, int x_s, int y_s, int x, int y);

void weak_to_clean_iso(Mat &image, int x_s, int y_s, int x, int y);

void test_blur(Mat &image);

Mat elliptic_condition(Mat &image, int x_s, int y_s, int x_lim, int y_lim);


#endif //BLUR_H
