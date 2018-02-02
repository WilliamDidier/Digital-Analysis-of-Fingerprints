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

#ifndef STARTER3
#define STARTER3

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
void Convol_Shifted(Mat &X, Mat &dst, Mat &H);

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
@fn void periodic_shift(Mat &src, Mat &dst, int p)
@brief for a matrix M of size m*n, give the matrix M' where M'[i,j] = M[(i+p)%m, (j+p)%n]
@param Input : Two matrix : the source and the destination, and a integer that correspond to the shift
@return a real matrix
@author William
*/

void periodic_shift(Mat &src, Mat &dst, int p);

/**
@fn Mat convolution_fft(Mat x, Mat h)
@brief give the convolution of the two matrix thanks to FFT
@param Input : two matrix
@return a real matrix
@author Théo M. & Romain
*/

void convolution_fft(Mat &x, Mat &dst, Mat &h);

/**
@fn Mat Normalized_kernel(int NbCols, int NbRows)
@brief give a normalized kernel of size NbCols*NbRows. Each coefficient is equal to 1/(NbCols*NbRows)
@param Input : Two integers positives
@return a real matrix
@author Théo M. & Romain
*/

Mat Normalized_kernel(int NbCols, int NbRows);

/**
@fn float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y)
@brief give the value of the 2D-Gaussian at the point (x,y)
@param Input : The two coordinates where we compute the value of the gaussian, and four float for the parameters of the gaussian
@return a float
@author Théo M. & Romain
*/

float gauss2D(float x, float y, float esp_x, float esp_y, float sigma_x, float sigma_y);

/**
@fn Gaussian_kernel(int size, float sigma_x, float sigma_y, float energy)
@brief give a Matrix filled with coefficient computed with a 2D Gaussian function
@param Input : An odd integer for the size of the square matrix, two float for the parameters of the gaussian, and a float for the norm of the matrix
@return a float
@author Théo M. & Romain
*/

Mat Gaussian_kernel(int size, float sigma_x, float sigma_y, float energy);

/**
@fn Mat Convol_Shifted_xy(Mat X, uint size_h)
@brief Give the convolution of the image with a gaussian kernel where sigma_x and sigma_y depends on coordinates
@param Input : The input matrix, and the size of the varying kernel
@return a matrix
@author Théo M.
*/

Mat Convol_Shifted_xy(Mat X, uint size_h);

/**
@fn Mat Convol_Shifted_xy(Mat X, uint size_h)
@brief Give the convolution of the image with a gaussian kernel where sigma_x, sigma_y, and the norm depends on coordinates
@param Input : The input matrix, and the size of the varying kernel
@return a matrix
@author Théo M.
*/
Mat Convol_Shifted_xy_energy(Mat X, uint size_h);

#endif
