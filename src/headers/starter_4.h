#ifndef STARTER_4_H
#define STARTER_4_H

#include <opencv2/opencv.hpp>


using namespace cv;
using std::cout;
using std::endl;

void binarization(Mat &image, Mat &);

float threshold_computation(const Mat &image);

void print_vector(vector<float> vect);

std::vector<int> levels_computation(Mat &image);

std::vector<float> normalized_levels(Mat &image);

float mean_level(vector<float> levels, int k);

float cumulative_moment_0(vector<float> levels, int k);

int index_max(vector<float> vect);

int optimal_threshold(Mat &image);

#endif //STARTER_4_H
