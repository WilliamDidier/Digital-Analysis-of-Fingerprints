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

Mat ellipse(Point2f parameters, Point2f pressure_center, Point2f dimensions);

void apply_iso(Mat &image);
