/*
header file associated to 'starter3.cpp'
contains the functions related to the starter 3
*/
/**
  This is a Doxygenb documentation.
  @file starter3.h
  @brief Header for the functions of the Starter 3
  @author Romain C. & Théo M. & Théo L. & William D.
  @ date 2018, January the 16th


*/
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>

using namespace cv;

float produit_coefbycoef(Mat A, Mat B);

Mat Convol(Mat X, Mat H);

Mat Convol_Shifted(Mat X, Mat H);

Mat transfo_fourier( Mat image);

Mat img_magnitude(Mat img_complexe);

Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows);

Mat convolution_fft(Mat x, Mat h);

Mat Normalized_kernel(int NbCols, int NbRows);

float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y);

Mat Gaussian_kernel(int size, float sigma_x, float sigma_y);
