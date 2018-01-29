#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter3.h"
#include "starter_1.h"
#include <math.h>
#include "starter2.h"
#define PI 3.14159265

vector<int> rotation( int i, int j, float angle ){
  int max = 0;
  float i_prime = cos(PI*angle/180)*i - sin(PI*angle/180)*j ;
  float j_prime = sin(PI*angle/180)*i + cos(PI*angle/180)*j ;
  vector<int> tab(2);
  tab[0] = floor(i_prime + 0.5);
  tab[1] = floor(j_prime + 0.5);
  return tab;
}


Mat rotate_img_to_dest(Mat image, float angle){
  int rows = image.rows;
  int cols = image.cols;
  int dim_output_x = int(sin(PI*angle/180)*cols + rows*cos(PI*angle/180));
  int dim_output_y = int(sin(PI*angle/180)*rows + cols*cos(PI*angle/180));
  Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
       vector<int> tab(2);
       tab = rotation(i,j, angle);
       if( tab[0] >= -sin(PI*angle/180)*cols && tab[1] >= 0 && tab[1] < dim_output_x && tab[0] < cols){
        Res.at<float>(tab[0]+sin(PI*angle/180)*cols, tab[1]) = intensity[0];
       }
    }
  }
  Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
  return Res(roi);
}

Mat interpolation_moy_16(Mat image){
  int rows = image.rows;
  int cols = image.cols;
  Mat big_image;

  copyMakeBorder(image, big_image, 1, 1, 1, 1, BORDER_CONSTANT, Scalar::all(1));

  for(int i = 0; i < rows; i++ ){
    for(int j = 0; j < cols; j++){
      Scalar intensity = image.at<float>(i, j);
        float moy = (big_image.at<float>(i+2, j+1)+big_image.at<float>(i, j+1)+
        big_image.at<float>(i+1, j+2)+big_image.at<float>(i+1, j)
        +big_image.at<float>(i+2, j+2)+big_image.at<float>(i, j)
        +big_image.at<float>(i+2, j)+ big_image.at<float>(i, j+2))/8.;
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
      if (intensity[0] == 0){
        image.at<float>(i,j) = big_image.at<float>(i+2,j+1);
       }
    }
  }
  return image;
}


Mat rotate_img_from_source(Mat image, float angle){
    vector<int> decal(3);
    decal = decal_angle(image, angle);
    int rows = image.rows;
    int cols = image.cols;
    float opp_angle = -decal[2];
    int dim_output_x = int(fabs(sin(PI*decal[2]/180.))*cols + rows*fabs(cos(PI*decal[2]/180.)));
    int dim_output_y = int(fabs(sin(PI*decal[2]/180.))*rows + cols*fabs(cos(PI*decal[2]/180.)));
    Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
    for(int i = -decal[0]; i < dim_output_x-decal[0]; i++ ){
      for(int j = decal[1]; j < dim_output_y + decal[1]; j++){
          vector<int> tab(2);
          tab = rotation(i,j, opp_angle);
          if( tab[0] >= 0 && tab[1] >= 0 && tab[1] <= cols && tab[0] <= rows){
            float intensity = image.at<float>(tab[0], tab[1]);
            Res.at<float>(i + decal[0], j - decal[1]) = intensity;
          }
       }
    }
    Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
    return Res(roi);
}

float step_bilinear(float x, float y, Mat image){
  float res ;
  float floorx = float(floor(x));
  float floory = float(floor(y));
  float ceilx = float(ceil(x));
  float ceily = float(ceil(y));

  float dx = (x-floorx)/(ceilx-floorx);
  float dy = (y-floory)/(ceily-floory);

  float intensity1 = image.at<float>(floorx,  floory);
  float intensity2 = image.at<float>(ceilx,  floory);
  float intensity3 = image.at<float>(ceilx,  ceily);
  float intensity4 = image.at<float>(floorx,  ceily);

  res = (1-dx)*(1-dy)*intensity1+dx*(1-dy)*intensity2+dx*dy*intensity3+(1-dx)*dy*intensity4;
  if (res > 1){
    res = 1;
  }
  return res;
  }


Mat rotate_img_from_source_bilinear(Mat image, float angle){
      vector<int> decal(3);
      decal = decal_angle(image, angle);
      int rows = image.rows;
      int cols = image.cols;
      float opp_angle = -decal[2];
      int dim_output_x = int(fabs(sin(PI*decal[2]/180.))*cols + rows*fabs(cos(PI*decal[2]/180.)));
      int dim_output_y = int(fabs(sin(PI*decal[2]/180.))*rows + cols*fabs(cos(PI*decal[2]/180.)));
      Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
      for(int i = -decal[0]; i < dim_output_x-decal[0]; i++ ){
        for(int j = decal[1]; j < dim_output_y + decal[1]; j++){
            vector<float> tab(2);
            tab = rotation_bilinear(i,j, opp_angle);
            if( tab[0] >= 0 && tab[1] >= 0 && tab[1] <= cols && tab[0] <= rows){
              float intensity = step_bilinear(tab[0], tab[1], image);
              Res.at<float>(i + decal[0], j - decal[1]) = intensity;
            }
         }
      }
      Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
      return Res(roi);
}


float derive_x(float x, float y, Mat image){
    float res;
    float floorx = float(floor(x));
    float floory = float(floor(y));
    float floorx_1 = float(floor(x))-1;
    float ceilx = float(ceil(x));

    float intensity1 = image.at<float>(floorx-1,  floory);
    float intensity2 = image.at<float>(ceilx,  floory);

    res = (intensity2 -intensity1)/(ceilx-floorx_1);

    return res;
  }

float derive_y(float x, float y, Mat image){
    float res;
    float floorx = float(floor(x));
    float floory = float(floor(y));
    float floory_1 = float(floor(y))-1;
    float ceily = float(ceil(y));

    float intensity1 = image.at<float>(floorx,  floory_1);
    float intensity2 = image.at<float>(floorx,  ceily);

    res = (intensity2 -intensity1)/(ceily-floory_1);

    return res;
  }

float derive_xy(float x, float y, Mat image){
    float res;
    float floorx = float(floor(x));
    float floory = float(floor(y));
    float floory_1 = float(floor(y))-1;
    float ceily = float(ceil(y));
    float floorx_1 = float(floor(x))-1;
    float ceilx = float(ceil(x));

    float intensity1 = image.at<float>(floorx_1,  floory_1);
    float intensity2 = image.at<float>(floorx_1,  ceily);
    float intensity3 = image.at<float>(ceilx,  floory_1);
    float intensity4 = image.at<float>(ceilx,  ceily);

    res = (intensity4-intensity3-intensity2+intensity1)/((ceilx-floorx_1)*(ceily-floory_1));
    return res;
  }

Mat coeff_bicubic(float x, float y, Mat image){
  float floorx = float(floor(x));
  float floory = float(floor(y));
  float ceilx = float(ceil(x));
  float ceily = float(ceil(y));

  float intensity1 = image.at<float>(floorx,  floory);
  float intensity2 = image.at<float>(ceilx,  floory);
  float intensity3 = image.at<float>(ceilx,  ceily);
  float intensity4 = image.at<float>(floorx,  ceily);

  Mat M = (Mat_<float>(4,4) << intensity1, intensity4, derive_y(x,y, image), derive_y(x,y+1,image),
                               intensity2, intensity3, derive_y(x+1,y,image), derive_y(x+1,y+1,image),
                               derive_x(x,y,image), derive_x(x, y+1,image), derive_xy(x,y,image), derive_xy(x, y+1,image),
                               derive_x(x+1,y,image), derive_x(x+1, y+1,image), derive_xy(x+1,y,image), derive_xy(x+1, y+1,image));
  Mat A = (Mat_<float>(4,4) << 1,0,0,0,
                                0,0,1,0,
                                -3,3,-2,-1,
                                2,-2,1,1);

  Mat A_inv = (Mat_<float>(4,4) << 1,0,-3,2,
                                    0,0,3,-2,
                                    0,1,-2,1,
                                    0,0,-1,1);
  Mat res(Size(4,4),CV_32F);
  res = A*M*A_inv;
  return res;
  }

float cubic_interpolation(float x, float y, Mat image){
    float res;
    Mat coeff = coeff_bicubic(x,y,image);
    float floorx = float(floor(x));
    float floory = float(floor(y));
    float ceilx = float(ceil(x));
    float ceily = float(ceil(y));

    float dx = (x-floorx)/(ceilx-floorx);
    float dy = (y-floory)/(ceily-floory);

    vector<float> res_int(4);
    for(int i=0; i < 4; i++){
      float puis = 1;
      for(int j = 0; j < 4; j++){
        res_int[i] += coeff.at<float>(j,i)*puis;
        puis *= dx;
      }
    }
    res = res_int[0]+res_int[1]*dy+res_int[2]*dy*dy+res_int[3]*dy*dy*dy;
    if (res >1){
      res = 1;
    }
    return res;
  }

Mat rotate_img_from_source_bicubic(Mat image, float angle){
      vector<int> decal(3);
      decal = decal_angle(image, angle);
      int rows = image.rows;
      int cols = image.cols;
      float opp_angle = -decal[2];
      int dim_output_x = int(fabs(sin(PI*decal[2]/180.))*cols + rows*fabs(cos(PI*decal[2]/180.)));
      int dim_output_y = int(fabs(sin(PI*decal[2]/180.))*rows + cols*fabs(cos(PI*decal[2]/180.)));
      Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
      for(int i = -decal[0]; i < dim_output_x-decal[0]; i++ ){
        for(int j = decal[1]; j < dim_output_y + decal[1]; j++){
            vector<float> tab(2);
            tab = rotation_bilinear(i,j, opp_angle);
            if( tab[0] >= 0 && tab[1] >= 0 && tab[1] <= cols && tab[0] <= rows){
              float intensity = cubic_interpolation(tab[0], tab[1], image);
              Res.at<float>(i + decal[0], j - decal[1]) = intensity;
            }
         }
      }
      Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
      return Res(roi);
}

float distance(float x, float y){
  float res = sqrt(x*x+y*y);
}

float weight(float x, float y, Mat image){
  float floorx = float(floor(x));
  float floory = float(floor(y));
  float ceilx = floorx+1;
  float ceily = floory+1;
  if (floorx == x && floory == y){
    return image.at<float>(floorx,  floory);
  }else{
    float dist_left_top = distance(x-floorx, y-floory);
    float dist_right_top = distance(x-ceilx, y-floory);
    float dist_left_bottom = distance(x-floorx, y-ceily);
    float dist_right_bottom = distance(x-ceilx, y-ceily);

    float intensity1 = image.at<float>(floorx,  floory);
    float intensity2 = image.at<float>(ceilx,  floory);
    float intensity3 = image.at<float>(ceilx,  ceily);
    float intensity4 = image.at<float>(floorx,  ceily);

    float res = (1./dist_left_top)*intensity1+(1./dist_right_top)*intensity2+(1./dist_left_bottom)*intensity4+(1./dist_right_bottom)*intensity3;
    return res/((1./dist_left_top)+(1./dist_right_top)+(1./dist_left_bottom)+(1./dist_right_bottom));
  }
}
vector<float> rotation_bilinear( int i, int j, float angle ){
  vector<float> tab(2);
  tab[0] = cos(PI*angle/180.)*i - sin(PI*angle/180.)*j ;
  tab[1] = sin(PI*angle/180.)*i + cos(PI*angle/180.)*j ;

  return tab;
}


vector<int> decal_angle(Mat image, float angle){
  int rows = image.rows;
  int cols = image.cols;
  int decal_pos = 0;
  int decal_neg = 0;
  if ( angle > 0){
    decal_pos = int(sin(PI*angle/180.)*cols);
  }else{
    decal_neg = int(sin(PI*angle/180.)*rows);
  }
  vector<int> decal(2);
  decal[0] = decal_pos;
  decal[1] = decal_neg;
  return decal;
}

Mat rotate_img_from_source_weighted(Mat image, float angle){
      vector<int> decal(2);
      decal = decal_angle(image, angle);
      int rows = image.rows;
      int cols = image.cols;
      float opp_angle = -decal[2];
      int dim_output_x = int(fabs(sin(PI*decal[2]/180.))*cols + rows*fabs(cos(PI*decal[2]/180.)));
      int dim_output_y = int(fabs(sin(PI*decal[2]/180.))*rows + cols*fabs(cos(PI*decal[2]/180.)));
      Mat Res = Mat::zeros(dim_output_x,dim_output_y, CV_32FC1);
      for(int i = -decal[0]; i < dim_output_x-decal[0]; i++ ){
        for(int j = decal[1]; j < dim_output_y + decal[1]; j++){
            vector<float> tab(2);
            tab = rotation_bilinear(i,j, opp_angle);
            if( tab[0] >= 0 && tab[1] >= 0 && tab[1] <= cols && tab[0] <= rows){
              float intensity = weight(tab[0], tab[1], image);
              Res.at<float>(i + decal[0], j - decal[1]) = intensity;
            }
         }
      }
      Rect roi = Rect(dim_output_y/2-cols/2+1, dim_output_x/2-rows/2, cols, rows);
      return Res(roi);
}
