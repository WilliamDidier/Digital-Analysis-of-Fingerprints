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

Point2i decrease_rotation(int x, int y, int i, int j, float angle){
  Point2i pt;
  float angle_decrease = angle*exp(-((i-x)*(i-x)+(j-y)*(j-y)));
  angle = angle_decrease*PI/180;
  pt.x = cos(angle)*i - sin(angle)*j ;
  pt.y = sin(angle)*i + cos(angle)*j ;
  return tab;
}

Mat rotate_elasticity(Mat image, float angle){
    vector<int> decal(2);
    decal = decal_angle(image, angle);
    int rows = image.rows;
    int cols = image.cols;
    float opp_angle = -angle;
    int dim_output_x = int(fabs(sin(PI*angle/180.))*cols + rows*fabs(cos(PI*angle/180.)));
    int dim_output_y = int(fabs(sin(PI*angle/180.))*rows + cols*fabs(cos(PI*angle/180.)));
    Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
    for(int i = -decal[0]; i < dim_output_x-decal[0]; i++ ){
      for(int j = decal[1]; j < dim_output_y + decal[1]; j++){
          Point2i pt;
          pt = decrease_rotation(cols/2, rows/2, i,j, opp_angle);
          if( pt.x >= 0 && pt.y >= 0 && pt.y <= cols && pt.x <= rows){
            float intensity = cubic_interpolation(pt.x, pt.y, image);

            Res.at<float>(i + decal[0], j - decal[1]) = intensity;
          }
       }
    }
    // Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
    return Res;
}
