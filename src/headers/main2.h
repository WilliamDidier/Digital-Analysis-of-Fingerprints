#ifndef MAIN2
#define MAIN2
/**
@file main2.h
@brief Header for the functions of the Main course 2
@author Romain C.
*/
Mat get_zone(int x, int y, int width, int height, Mat image);

vector<float> decrease_rotation(int x, int y, int i, int j, float angle);

Mat rotate_elasticity(Mat image, float angle);

#endif
