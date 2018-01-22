#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include "starter3.h"
#include "starter_1.h"

using namespace cv;

float produit_coefbycoef(Mat A, Mat B){
  /**
    @fn float produit_coefbycoef(Mat A, Mat B)
    @brief make the sum of product term by term of two matrix
    @param Input : 2 matrix with the same size
    @return a float
    @author Théo M. & Romain
  */
  float res = 0;
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < A.cols; j++){
      //one get the co  image.copyTo(big_image(roi));ordinates i and j of each matrix
      float tmp = A.at<float>(i,j);
      float tmp2 = B.at<float>(i,j);
      res += tmp*tmp2;
    }
  }
  return res;
}

Mat Convol(Mat X, Mat H){

  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  //  one create a float matrix which has the same dimension than X
  Mat Res(RowX, ColX, CV_32FC1);
  // One complete the matrix X with colH-1 zeros on the left and at the bottom ( to remove the bordure issues)
  // To do that, one create a matrix of dimension greater than X
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  // one select the region of dimension X
  Rect roi = Rect(ColH-1,0,ColX,RowX);
  // One copy X on the region
  X.copyTo(BigX(roi));
  // For each pixel of X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){  /**
    @fn Mat convolution_fft(Mat x, Mat h)
    @brief give the convolution of the two matrix thanks to FFT
    @param Input : two matrix
    @return a real matrix
    @author Théo M. & Romain
  */
      //... one sélect a small image of dimension H having for beginning the current pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // ... and finally one complet the result matrix by the sum of product term by term of two matrix
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}

Mat Convol_Shifted(Mat X, Mat H){

  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  //  one create a float matrix which has the same dimension than X
  Mat Res(RowX, ColX, CV_32FC1);
  // One complete the matrix X with colH-1 zeros around X ( to remove the bordure issues)
  // To do that, one create a matrix of dimension greater than X
  Mat BigX = Mat::ones(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  // one select the region of dimension X
  Rect roi = Rect((ColH-1)/2,(RowH-1)/2,ColX,RowX);
  // One copy X on the region
  X.copyTo(BigX(roi));
  // For each pixel of X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      //... one sélect a small image of dimension H having for beginning the current pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // ... and finally one complet the result matrix by the sum of product term by term of two matrix
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}



Mat transfo_fourier( Mat image){

  Mat optimal;
  //extend the matrix with the optimal size
  int  nbRows =   getOptimalDFTSize( image.rows );
  int  nbCols =   getOptimalDFTSize( image.cols );
  //add zeros on the boundaries
  copyMakeBorder(image, optimal, 0, nbRows - image.rows, 0, nbCols - image.cols, BORDER_CONSTANT, Scalar::all(0));
  Mat tab[] = {Mat_<float>(optimal), Mat::zeros(optimal.size(), CV_32F)};
  Mat img_complexe;
  // convert the real matrix to a complex matrix
  merge(tab, 2, img_complexe);
  dft(img_complexe, img_complexe);
  return img_complexe;

}

Mat img_magnitude(Mat img_complexe){
  Mat tab[] = {Mat_<float>(img_complexe), Mat::zeros(img_complexe.size(), CV_32F)};
  //split the real part and the complex part
  split(img_complexe, tab);
  // one take the norm of the matrix, that is to say the magnitude
  magnitude(tab[0], tab[1], tab[0]);
  Mat res = tab[0];
  // one put on a logarithmic scale
  res += Scalar::all(1);
  log(res, res);
  // one resize the matrix at the initial size
  res = res(Rect(0, 0, res.cols & -2, res.rows & -2));
  //one transform the matrix with float between 0 and 1
  normalize(res, res, 0, 1, NORM_MINMAX);
  return res;Mat O = Mat::ones(2, 2, CV_32F);
}

Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows){

  Mat res;http://math.mad.free.fr/depot/numpy/courbe.html
  // we apply the idft with a real resultRowX+RowH-1
  idft(image, res, DFT_REAL_OUTPUT|DFT_SCALE);
  Mat finalImage;
  //we noramlize the matrix such that these numbers were between 0 and 1
  normalize(res, finalImage, 0, 1, NORM_MINMAX);
  return finalImage(Rect(0, 0, nbCols, nbRows));
}


Mat periodic_image( Mat image){
  int Rows = image.rows;
  int Cols = image.cols;
  Mat symetry_ya = symetry_y(image);
  Mat symetry_xa = symetry_x(image);
  Mat big_image = Mat::ones(2*Rows, 2*Cols, CV_32FC1);
  Rect roi = Rect(0, 0, Cols, Rows);
  image.copyTo(big_image(roi));
  roi = Rect(Cols-1, 0, Cols, Rows);
  symetry_ya.copyTo(big_image(roi));
  roi = Rect(0, Rows-1, Cols, Rows);
  symetry_xa.copyTo(big_image(roi));
  return big_image;
}

Mat convolution_fft(Mat x, Mat h){

  // Mat trans_mat = (Mat_<double>(2,3) << 1, 0, 1, 0, 1, 1);
  // warpAffine(x,x,trans_mat,x.size());
  int cols = x.cols;
  int rows = x.rows;
  x = periodic_image(x);
  Mat X = transfo_fourier(x);
  //one complete h with zero to reach the size of X
  copyMakeBorder(h, h, 0, x.rows - h.rows, 0, x.cols - h.cols, BORDER_CONSTANT, Scalar::all(0));
  Mat H = transfo_fourier(h);

  Mat Y;
  // we multiply term by term the two matrix
  mulSpectrums(X,H,Y,0,false);
  Mat res = inv_transfo_fourier(Y, x.cols, x.rows);
  Rect roi = Rect(0,0,cols, rows);
  x = res(roi);
  return x;
}


Mat Normalized_kernel(int NbCols, int NbRows){
  Mat kernel(NbRows,NbCols,CV_32FC1, Scalar(1./((float) NbCols*NbRows)));
  return kernel;
}


float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y){
  return exp(-(x-esp_x)*(x-esp_x)/(2*sigma_x*sigma_x) + -(y-esp_y)*(y-esp_y)/(2*sigma_y*sigma_y));
}

Mat Gaussian_kernel(int size, float sigma_x, float sigma_y){
  Mat kernel(size,size,CV_32FC1);
  float middle = ((float) size-1.)/2.;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      kernel.at<float>(j,i) = gauss2D((float) i, (float) j, middle, middle, sigma_x, sigma_y);
    }
  }
  kernel = kernel / ((float) norm(kernel, NORM_L1));
  return kernel;
}



















//
