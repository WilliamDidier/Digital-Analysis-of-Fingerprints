#include <opencv2/opencv.hpp>

#include "starter_4.h"
#include "starter_1.h"
#include <vector>

using namespace cv;
using std::cout;
using std::endl;


void binarization(const Mat &image, Mat &bin_image) {

  int nRows = image.rows;
  int nCols = image.cols;
  //Mat bin_image;
  //bin_image.create(nRows, nCols, CV_32F);
  //bin_image.create(nRows, nCols, CV_32F);

  float threshold = 0.5;

  for (uint i = 0; i < nCols; i++) {
    for (uint j = 0; j < nRows; j++) {
      bin_image.at<float>(j, i) = (image.at<float>(j, i) > threshold);
    }
  }

  //return(bin_image);
}

void print_vector(vector<int> vect) {
    for (uint i = 0; i < vect.size(); i++) {
        cout << vect[i] << endl;
    }
}

std::vector<int> levels_computation(Mat &image) {

    Mat dst;
    convert_to_int(image, dst);

    std::vector<int> levels(255, 0);
    for (uint i = 0; i < image.cols; i++) {
      for (uint j = 0; j < image.rows; j++) {
        int intensity = dst.at<int>(j, i);
        cout << intensity << endl;
        levels[intensity] += 1;
      }
    }

    return(levels);
}
