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
/**
  @fn Mat Convol(Mat X, Mat H)
  @brief give X**H, centered on the downright coefficient of the matrix H
  @param Input : 2 matrix
  @return the matrix of convolution
  @author Théo M. & Romain
*/
Mat Convol(Mat X, Mat H);

/**
  @fn Mat Convol_Shifted(Mat X, Mat H)
  @brief give X**H, centered on the centered coefficient of the matrix H
  @param Input : 2 matrix, H must be a square matrix with an odd dimension
  @return the matrix of convolution
  @author Théo M. & Romain
*/
Mat Convol_Shifted(Mat X, Mat H);

/**
  @fn Mat transfo_fourier( Mat image)
  @brief give a complex Matrix which is the result of the fourier transform of initial matrix
  @param Input : one matrix
  @return the fourier transform of the matrix
  @author Théo M. & Romain
*/
Mat transfo_fourier( Mat image);

/**
@fn Mat img_magnitude(Mat img_complexe)
@brief give the trasform fourier image since a complex matrix
@param Input : A complex matrix
@return a real matrix as a representation of magnitude
@author Théo M. & Romain
*/
Mat img_magnitude(Mat img_complexe);

/**
@fn Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows)
@brief give the inverse transform fourier since a complex matrix
@param Input : A complex matrix, it number of colons and it number of rows
@return a real matrix
@author Théo M. & Romain
*/
Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows);

/**
@fn Mat convolution_fft(Mat x, Mat h)
@brief give the convolution of the two matrix thanks to FFT
@param Input : two matrix
@return a real matrix
@author Théo M. & Romain
*/
Mat convolution_fft(Mat x, Mat h);
