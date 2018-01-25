#ifndef MORPHO_H
#define MORPHO_H


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

class Structuring_Element{
private:
  Mat element;
  Point2i center;
  int size;
public:
  dilatation(Mat &image);
  erosion(Mat & image);
};


#endif //MORPHO_H
