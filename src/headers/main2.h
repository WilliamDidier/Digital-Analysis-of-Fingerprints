/*
header file associated to 'main2.cpp'
contains the functions related to the main 2
*/
/**
  This is a Doxygen documentation.
  \file main2.h
  \brief Header for the functions of the main 2
  \author Romain C. & Théo M. & Théo L. & William D.
  \ date 2018, January the 16th


*/
#ifndef MAIN2
#define MAIN2
Mat get_zone(int x, int y, int width, int height, Mat image);

vector<float> decrease_rotation(int x, int y, int i, int j, float angle);

Mat rotate_elasticity(Mat image, float angle);

#endif
