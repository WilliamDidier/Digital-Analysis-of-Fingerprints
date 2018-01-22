#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter3.h"
#include "starter_1.h"
#include <cmath>
#include "starter2.h"
#define PI 3.14159265

vector<int> rotation(int i, int j, int angle ){
  float i_prime = abs(cos(PI*angle/180)*i - sin(PI*angle/180)*j);
  float j_prime = abs(sin(PI*angle/180)*i + cos(PI*angle/180)*j);
  vector<int> tab(2);
  tab[0] = floor(i_prime + 0.5);
  tab[1] = floor(j_prime + 0.5);
  return tab;
}

Mat rotate_img(Mat image, int angle){
  int rows = image.rows;
  int cols = image.cols;
  Mat Res = Mat::ones(cols, rows, CV_32FC1);
  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
       vector<int> tab(2);
       tab = rotation(i,j, angle);
      if( tab[0] >= 0 && tab[1] >= 0 && tab[1] < rows && tab[0] < cols){
        Res.at<float>(tab[0], tab[1]) = intensity[0];
      }
    }
  }

  return Res;
}

Mat interpolation_1(Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Mat big_image;

  copyMakeBorder(image, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));

  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
      if (intensity[0] == 1){
        float moy = (big_image.at<float>(i+2, j+1)+big_image.at<float>(i, j+1)+
        big_image.at<float>(i+1, j+2)+big_image.at<float>(i+1, j)
        +big_image.at<float>(i+2, j+2)+big_image.at<float>(i, j)
        +big_image.at<float>(i+2, j)+ big_image.at<float>(i, j+2))/8.;
        // std::cout << moy << std::endl;
        image.at<float>(i,j) = moy;
       }
    }
  }
  return image;
}
Mat interpolation_2(Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Mat big_image;

  copyMakeBorder(image, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));

  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
      if (intensity[0] == 1){
        image.at<float>(i,j) = big_image.at<float>(i+2,j+1);
       }
    }
  }
  return image;
}
