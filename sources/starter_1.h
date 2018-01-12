#ifndef STARTER_1
#define STARTER_1

#include <opencv2/opencv.hpp>

using namespace cv;

Mat convert_to_float(Mat image){
  Mat dst;
  image.convertTo(dst, CV_32F, 1.0/255.0);
  return(dst);
}

int draw_uniform_rectangle (uint x, uint y, uint sx, uint sy, float color, Mat image){
  assert ((x+sx <= image.cols) && (y+sy <= image.rows));
  Rect r(x,y,sx,sy);
  image = image(r);
  image = Scalar(color);
  return 0;
}

#endif
