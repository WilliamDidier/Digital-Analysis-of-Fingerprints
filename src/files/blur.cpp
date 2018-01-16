/* documentation available in 'blur.h' */

#include "blur.h"
#include "math.h"
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


void clean_to_weak_iso(Mat &image, int x_s, int y_s, int x, int y) {
  //computation of the euclidian distance to the spot
  float distance = sqrt(pow(x_s - x, 2) + pow(y_s - y, 2));
  //apply the effects of the blur on the pixel at (x,y)
  float intensity = image.at<float>(y, x);
  //std::cout << intensity << std::endl;
  image.at<float>(y, x) = exp(-distance/100)*intensity;
  //std::cout << (1 - exp(-distance))*intensity << std::endl;
}


void weak_to_clean_iso(Mat &image, int x_s, int y_s, int x, int y) {
  //computation of the euclidian distance to the spot
  float distance = sqrt(pow(x_s - x, 2) + pow(y_s - y, 2));
  //apply the effects of the blur on the pixel at (x,y)
  float intensity = image.at<float>(y, x);
  //std::cout << intensity << std::endl;
  image.at<float>(y, x) = exp(distance/500)*intensity;
  if (image.at<float>(y,x) > 1.0){
    image.at<float>(y, x) = 1.0;
  }
  //std::cout << (1 - exp(-distance))*intensity << std::endl;
}


void test_blur(Mat &image) {
    int nRows = image.rows;
    int nCols = image.cols;
    int x_s = nCols / 2;
    int y_s = nRows / 2;
    std::cout << "nCols : " << image.cols << " nRows : " << image.rows << std::endl;
    for (int i = 0; i < nCols; i++) {
      for (int j = 0; j < nRows; j++) {
          clean_to_weak_iso(image, x_s, y_s, i, j);
      }
    }
}

//fonction pour faire weak to clean
/*
void test_blur(Mat &image) {
    int nRows = image.rows;
    int nCols = image.cols;
    int x_s = nCols / 2;
    int y_s = nRows / 2;
    std::cout << "nCols : " << image.cols << " nRows : " << image.rows << std::endl;
    for (int i = 0; i < nCols; i++) {
      for (int j = 0; j < nRows; j++) {
        //std::cout << "i : " << i << " j : " << j << std::endl;
        if(image.at<float>(j,i) > 0.40){
          image.at<float>(j,i) = 1.0;
        } else {
          isotropic_blur2(image, x_s, y_s, i, j);
        }
      }
    }
}
*/

/*
Mat elliptic_condition(Mat &image, int x_s, int y_s, int x_lim, int y_lim) {
    Mat conditions;
    int nRows = image.rows;
    int nCols = image.cols;
    conditions.create(nRows, nCols, CV_32F);

}
*/
