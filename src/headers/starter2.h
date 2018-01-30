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

vector<int> rotation(int x, int y, int i, int j, float angle );

Mat rotate_img_from_source(Mat image, float angle);

Mat rotate_img_to_dest(Mat image, float angle);

Mat interpolation_moy_16(Mat image);

Mat interpolation_nearest_neighboor(Mat image);

float step_bilinear(float x, float y, Mat image);

Mat interpolation_bicubic(Mat image);


Mat rotate_img_from_source_bilinear(Mat image, float angle);

vector<float> rotation_bilinear(int x, int y, int i, int j, float angle );

float derive_x(float x, float y, Mat image);

float derive_y(float x, float y, Mat image);

float derive_xy(float x, float y, Mat image);

Mat coeff_bicubic(float x, float y, Mat image);

float cubic_interpolation(float x, float y, Mat image);

Mat rotate_img_from_source_bicubic(Mat image, float angle);

float distance(float x, float y);

float weight( float x, float y, Mat image);

Mat rotate_img_from_source_weighted(Mat image, float angle);




























#endif
