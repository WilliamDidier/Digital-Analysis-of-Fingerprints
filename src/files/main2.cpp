#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter3.h"
#include "starter_1.h"
#include <math.h>
#include "starter2.h"
#include "main2.h"
#define PI 3.14159265


Mat get_zone(int x, int y, int width, int height, Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Rect zone = Rect(Point2f(x,y), Size2f(width, height));
  Mat big_image ;
  copyMakeBorder(image, big_image, width, width, height, height, BORDER_CONSTANT, Scalar::all(0));
  return big_image(zone);
}

vector<float> decrease_rotation(int x, int y, int i, int j, float angle){
  vector<float> tab(2);
  float dist = distance(x-i,j-y);
  angle = angle*PI/180 * exp(-dist*dist/1000);
  tab[0] = cos(angle)*(i-x) - sin(angle)*(j-y)+x ;
  tab[1] = sin(angle)*(i-x) + cos(angle)*(j-y)+y ;
  return tab;
}

Mat rotate_elasticity(Mat image, float angle){
    int rows = image.rows;
    int cols = image.cols;
    float opp_angle = -angle;
    Mat Res = Mat::zeros(rows,cols, CV_32FC1);
    for(int i = 0; i < rows; i++ ){
      for(int j = 0; j < cols ; j++){
          vector<float> tab(2);
          tab = decrease_rotation(rows/2, cols/2, i,j, opp_angle);
          if( tab[0] >= 0 && tab[1] >= 0 && tab[1] <= cols && tab[0] <= rows){
            float intensity = weight(tab[0], tab[1], image);
            Res.at<float>(i , j ) = intensity;
          }
       }
    }
    // Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
    return Res;
}
