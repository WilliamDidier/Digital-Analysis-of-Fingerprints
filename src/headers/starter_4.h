#ifndef STARTER_4_H
#define STARTER_4_H

#include <opencv2/opencv.hpp>

/**
  This is a Doxygen documentation.
  @file starter_4.h
  @brief Header for the functions of the Starter 4
  @author Théo L.
  @ date 2018, January the 25th
*/

using namespace cv;
using std::cout;
using std::endl;



/**
  @fn: print_vector(vector<float> vect)
  @brief: print all the values (float type) contained in a vector
  @param: vect: the vector concerned by the operation
  @return: nothing
  @author: Théo L.
*/
void print_vector(vector<float> vect);

/**
  @fn: std::vector<int> levels_computation(Mat &image)
  @brief: computes the histogram of grey levels in an image
  @param: image : the image from which the histogram will be computed
  @return: a vector of int
  @author: Théo L.
*/
std::vector<int> levels_computation(Mat &image);

/**
  @fn: std::vector<float> normalized_levels(Mat &image)
  @brief: computes a normalized histogram of grey levels w.r.t the number of
      pixels in an image
  @param: image: the image from which the histrogram has been computed
  @return: a vector of floats contained in [0;1]
  @author: Théo L.
*/
std::vector<float> normalized_levels(Mat &image);

/**
  @fn: float mean_level(vector<float> levels, int k)
  @brief: computes the mean of normalized levels at floor k
  @param: levels : the normalized histogram of grey levels
  @param: k : the floor
  @return: a float containing the mean
  @author: Théo L.
*/
float mean_level(vector<float> levels, int k);

/**
  @fn: float cumulative_moment_0(vector<float> levels, int k)
  @brief: computes the cumulative moment at order 0 of normalized levels at
      floor k
  @param: levels : the normalized histogram of grey levels
  @param: k : the floor
  @return: a float containing the cumulative moment at order 0
  @author: Théo L.
*/
float cumulative_moment_0(vector<float> levels, int k);

/**
  @fn: int index_max(vector<float> vect)
  @brief: returns the index of the max value in a float vector
  @param: vector : the input vector
  @return: an int containing the index
  @author: Théo L.
*/
int index_max(vector<float> vect);

/**
  @fn: int optimal_threshold(Mat &image)
  @brief: computes using the previous method an optimal threshold for image
      binarization
  @param: image : the image for which the threshold has to be computed
  @return: an int containing the threshold
  @author: Théo L.
*/
int optimal_threshold(Mat &image);

/**
  @fn: void binarization(Mat &image, Mat &bin_image)
  @brief: binarize an image according to a threshold
  @param: image : the image that will be processed
  @param: bin_image : the location where the result will be stored
  @return: nothing
  @author: Théo L.
*/
void binarization(Mat &image, Mat &bin_image);

#endif //STARTER_4_H
