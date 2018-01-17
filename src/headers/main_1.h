/* A REPRENDRE
header file associated to main_1.cpp
    - contains the functions related to the 'Main course 1'
    - the goal is to simulate the blur you get due to finger pressure
      variations
WARNING : the pressure center has to be defined before computations
*/

#ifndef MAIN_1_H
#define MAIN_1_H


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include"starter_1.h"

using namespace cv;

/**
  This is a Doxygen documentation.
  \file main_1.h
  \brief Header for the functions of the Main course 1
  \author Théo L. & William D.
  \ date 2018, January the 15th
*/

float distance_computation(const Point2i pressure_center, Point2i point, bool anisotropic);

/**
  \fn float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point)
  \brief Computes the coefficient c(x,y) such that g(x,y) = c(x,y)f(x,y)
  \param clean_to_weak Boolean that indicates which coefficient whould be
   computed, depending on the transformation we are doing
  \param pressure_center The pressure_center of the fingerprint.
  \param point The point (x,y) at which we compute the coefficient c(x,y)
  \return The floating point number c(x,y)
  \author William D.
*/
float coefficient_computation(bool clean_to_weak, const Point2i pressure_center, Point2i point);

/**
  \fn void change_intensity (Mat &image, Point2i point, float coef)
  \brief Changes the intendity of the image at the point (x,y)
  \param &image Image that will be modified
  \param point The point (x,y) at which we change the intensity
  \param coef Floating point number that multiplies the intensity
  \return Nothing : the data is directly modified by the function.
  \author William D.
*/
void change_intensity (Mat &image, Point2i point, float coef);

/**
  \fn bool white_thresholding(Mat &image, Point2i pt, const float threshold)
  \brief Applies a thresholding to the intensity of the image at a given point.
  \param &image Image that will be modified
  \param pt The point (x,y) at which we apply the thresholding
  \param threshold Floating point number such that if the intensity at the
  point (x,y) is greater than the threshold, it is set to 1.0. Has to be <1.0
  \return A boolean that indicates wether or not the threshold has been applied
  \author William D.
*/
bool white_thresholding(Mat &image, Point2i point, const float threshold);


/* applies an isotropic transformation on the image */
/**
  \fn void clean_to_weak_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates the weakening of the pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
void clean_to_weak_iso(Mat &image, const Point2i pressure_center);

/**
  \fn void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates a bigger pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
void weak_to_clean_iso(Mat &image, const Point2i pressure_center);

/**
  \fn void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  \brief Simulates a bigger pressure given a fingerprint.
  \param &image Image that will be treated
  \param pressure_center the point of maximum pressure during the acquisition
  \return Nothing : the image is directly modified.
  \author William D.
*/
Point2i fingerprint_boudaries(Mat &image);

Point2i parameters_computation(Mat &image);

/*
    @brief: tests if a given point is in the ellipse or not
    @
 */
bool test_ellipse(Point2f parameters, Point2i pressure_center, Point2i coordinates);

Mat ellipse(Point2i parameters, Point2i pressure_center, Point2i dimensions);

/* apply an anisotropic transformation on the image */
void apply_iso(Mat &image, Point2i pressure_center);

#endif //MAIN_1_H
