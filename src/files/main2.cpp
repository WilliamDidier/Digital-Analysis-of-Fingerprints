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
  Rect roi = Rect(x, y, width, height);
  Mat big_image = Mat::ones(cols+width, rows+height, CV_32FC1);
  return big_image(roi);
}
