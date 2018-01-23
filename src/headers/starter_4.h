#ifndef STARTER_4_H
#define STARTER_4_H

#include <opencv2/opencv.hpp>


using namespace cv;
using std::cout;
using std::endl;

void binarization(const Mat &image, Mat &);

float threshold_computation(const Mat &image);

void print_vector(vector<int> vect);

std::vector<int> levels_computation(Mat &image);

#endif //STARTER_4_H
