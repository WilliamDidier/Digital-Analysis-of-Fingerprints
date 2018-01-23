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

vector<int> rotation(int i, int j, int angle );

Mat rotate_img(Mat image, int angle);

Mat interpolation_moy_16(Mat image);

Mat interpolation_nearest_neighboor(Mat image);

int P(int x);

float  polynome(int x);

int bicubic(int i, int j);

Mat interpolation_bicubic(Mat image);




























#endif
