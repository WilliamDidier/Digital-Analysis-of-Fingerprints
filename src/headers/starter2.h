/*
header file associated to 'starter2.cpp'
contains the functions related to the starter 2
*/
/**
  This is a Doxygen documentation.
  \file starter2.h
  \brief Header for the functions of the Starter 2
  \author Romain C. & Théo M. & Théo L. & William D.
  \ date 2018, January the 16th


*/
#ifndef STARTER2
#define STARTER2

vector<int> rotation(int centre_x, int centre_y, int i, int j, int angle );

Mat rotate_img_from_source(Mat image, int angle, int centre_x, int centre_y);

Mat rotate_img_to_dest(Mat image, int angle, int centre_x, int centre_y);

Mat interpolation_moy_16(Mat image);

Mat interpolation_nearest_neighboor(Mat image);

int P(int x);

float  polynome(int x);

float bicubic(float dx, float dy, int i, int j, Mat image);

Mat interpolation_bicubic(Mat image);

vector<float> rotation_cubic( int i, int j, int angle );

Mat rotate_img_from_source_bilinear(Mat image, int angle);

vector<float> rotation_bilinear( int i, int j, int angle );

float derive_x(float x, float y, Mat image);

float derive_y(float x, float y, Mat image);

float derive_xy(float x, float y, Mat image);

Mat coeff_bicubic(float x, float y, Mat image);

float cubic_interpolation(float x, float y, Mat image);

Mat rotate_img_from_source_bicubic(Mat image, int angle);



























#endif
