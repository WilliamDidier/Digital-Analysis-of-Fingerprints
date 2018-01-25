#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "morphological_filtering.h"

Structuring_Element::dilatation(Mat &image) {
  int startx,starty;
  for (uint i = 0; i < src.cols; i++){
    for (uint j = 0; j < src.rows; j++){
      if (image.at<float>(j,i) == 0){
        startx = i - center.x;
        starty = j - center.y;
        for (int ii =0; ii < size; ii++){
          for(int jj = 0; jj < size; jj++){
            if (element.at<float>(jj,ii)){
              image.at<float>(starty+jj,startx+ii) = 0.0;
            }
          }
        }
      }
    }
  }
}

Structuring_Element::erosion(Mat &image) {
  for (uint i = 0; i < src.cols; i++){
    for (uint j = 0; j < src.rows; j++){

    }
  }
}
