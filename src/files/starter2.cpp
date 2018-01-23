#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter3.h"
#include "starter_1.h"
#include <math.h>
#include "starter2.h"
#define PI 3.14159265

vector<int> rotation(int rows, int cols, int i, int j, int angle ){
  int max = 0;
  float i_prime = abs(cos(-PI*angle/180)*i - sin(-PI*angle/180)*j);
  float j_prime = abs(sin(-PI*angle/180)*i + cos(-PI*angle/180)*j);
  vector<int> tab(2);
  tab[0] = floor(i_prime + 0.5);
  tab[1] = floor(j_prime + 0.5);
  if (tab[0]>max ){
    max = tab[0];
  }
  std::cout << max << std::endl;
  return tab;
}

Mat rotate_img(Mat image, int angle){
  int rows = image.rows;
  int cols = image.cols;
  vector<int> maxi(2);

  Mat Res = Mat::ones(rows, cols, CV_32FC1);
  for(int i = 0; i < cols; i++ ){
    for(int j = 0; j < rows; j++){
        vector<int> tab(2);
        tab = rotation(rows, cols,i,j, angle);
         if( tab[0] >= 0 && tab[1] >= 0 && tab[1] < rows && tab[0] < cols){
          Scalar intensity = image.at<float>(tab[0], tab[1]);
          Res.at<float>(i, j) = intensity[0];
       }
    }
  }
  return Res;
}
Mat interpolation_moy_16(Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Mat big_image;

  copyMakeBorder(image, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));

  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
      // if (intensity[0] == 1){
        float moy = (big_image.at<float>(i+2, j+1)+big_image.at<float>(i, j+1)+
        big_image.at<float>(i+1, j+2)+big_image.at<float>(i+1, j)
        +big_image.at<float>(i+2, j+2)+big_image.at<float>(i, j)
        +big_image.at<float>(i+2, j)+ big_image.at<float>(i, j+2))/8.;
        // std::cout << moy << std::endl;
        image.at<float>(i,j) = moy;
       }
    }
    return image;
  }

Mat interpolation_nearest_neighboor(Mat image){
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

int P(int x){
  if (x > 0){
    return x;
  }
  else{
    return 0;
  }
}

float  polynome(int x){
  return (1./6.)*(P(x+2)*P(x+2)*P(x+2)-4*P(x+1)*P(x+1)*P(x+1)+6*P(x)*P(x)*P(x)-4*P(x-1)*P(x-1)*P(x-1));
}


float bicubic(int i, int j, Mat image){
  float res;
  for( int m = -1; m < 3; m++){
    for (int n =-1; n < 3; n++){
      Scalar intensity = image.at<float>(i+m, j+n);
      res += intensity[0]*polynome(m-1)*polynome(1-n);
    }
  }
  return res;
}

Mat interpolation_bicubic(Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Mat big_image;

  copyMakeBorder(image, big_image, 2, 2, 2, 2, BORDER_CONSTANT, Scalar::all(1));

  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
      image.at<float>(i,j) = bicubic(i+2,j+2, big_image);


    }
  }
  return image;
}
