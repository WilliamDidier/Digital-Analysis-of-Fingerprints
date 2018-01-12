/*
header file associated to 'starter_1.cpp'
contains the functions related to the starter 1
*/

#ifndef STARTER_1
#define STARTER_1


#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

//convert the intensity range 0-255 (int) in a range 0-1 (float)
Mat convert_to_float(Mat image);

//do the inverse operation of convert_to_float (no really useful)
Mat convert_to_int(Mat image);

//à commenter didier
int draw_uniform_rectangle (Mat image, Rect r, float color);

//apply a symetry along the y axis to the image
Mat symetry_y(Mat &image);

//apply symetry along the x/y diagonal to the image
Mat symetry_diag(Mat &image);


#endif //STARTER_1
