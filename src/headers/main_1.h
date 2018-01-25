/*
GLOBAL DESCRIPTION: header file associated to main_1.cpp
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
  @file main_1.h
  @brief Header for the functions of the Main course 1
  @author Théo L. & William D.
  @ date 2018, January the 15th
*/

/**
################################################################################
                              basic operations
################################################################################
  */

/**
  @fn: float distance_computation(const Point2i pressure_center, Point2i point,
      bool anisotropic)
  @brief: computes the distance between a point and the pressure center, adapted
      to anistropic computations
  @param: pressure_center: coordinates of the pressure pressure_center
  @param: point: coordinates of a point
  @return: a float containing the distance
  @author: Théo L.
*/
float distance_computation(const Point2i pressure_center, Point2i point);

/**
  @fn: float coefficient_computation(bool clean_to_weak, const Point2i
      pressure_center, Point2i point)
  @brief: computes the coefficient c(x,y) such that g(x,y) = c(x,y)f(x,y)
  @param: clean_to_weak: boolean that indicates which coefficient whould be
   computed, depending on the transformation we are doing
  @param: pressure_center: the pressure_center of the fingerprint.
  @param: point: the point (x,y) at which we compute the coefficient c(x,y)
  @return: the floating point number c(x,y)
  @author: William D.
*/
float coefficient_computation(bool clean_to_weak, const Point2i pressure_center,
    Point2i point);

/**
  @fn: void change_intensity (Mat &image, Point2i point, float coef)
  @brief: changes the intendity of the image at the point (x,y)
  @param: &image: image that will be modified
  @param: point: the point (x,y) at which we change the intensity
  @param: coef: floating point number that multiplies the intensity
  @return: nothing : the data is directly modified by the function.
  @author: William D.
*/
void change_intensity (Mat &image, Point2i point, float coef);


/**
################################################################################
                            isotropic filtering
################################################################################
  */

/**
  @fn: bool white_thresholding(Mat &image, Point2i pt, const float threshold)
  @brief: applies a thresholding to the intensity of the image at a given point.
  @param: &image: image that will be modified
  @param: pt: the point (x,y) at which we apply the thresholding
  @param: threshold: floating point number <1.0 such that if the intensity at
      the point (x,y) is greater than the threshold, it is set to 1.0.
  @return: a boolean that indicates wether or not the threshold has been applied
  @author: William D.
*/
bool white_thresholding(Mat &image, Point2i point, const float threshold);

/**
  @fn: void clean_to_weak_iso(Mat &image, const Point2i pressure_center)
  @brief: simulates the weakening of the pressure given a fingerprint.
  @param: &image: image that will be treated
  @param: pressure_center: the point of maximum pressure during the acquisition
  @return: nothing : the image is directly modified.
  @author: William D.
*/
void clean_to_weak_iso(Mat &image, const Point2i pressure_center);

/**
  @fn: void weak_to_clean_iso(Mat &image, const Point2i pressure_center)
  @brief: simulates a bigger pressure given a fingerprint.
  @param: &image: image that will be treated
  @param: pressure_center: the point of maximum pressure during the acquisition
  @return: nothing : the image is directly modified.
  @author: William D.
*/
void weak_to_clean_iso(Mat &image, const Point2i pressure_center);


/**
################################################################################
                            anisotropic filtering
################################################################################
  */

/**
  @fn: int fingerprint_boundaries_x(Mat &image)
  @brief: finds the first point in terms of x that define the fingerprint
  @param: &image: the image on which will be applied the ellipse after
  @return: the coordinate x
  @author: Théo L.
*/
int fingerprint_boundaries_x(Mat &image);

/**
    @fn: int fingerprint_boundaries_y(Mat &image)
    @brief: finds the first point in terms of y that define the fingerprint
    @param: &image: the image on which will be applied the ellipse after
    @return: the coordinate y
    @author: Théo L.
*/
int fingerprint_boundaries_y(Mat &image);

/**
    @fn: Point2i fingerprint_boundaries(Mat &image)
    @brief: returns the result of the two previous function as point (y, x)
    @param: &image: the image on which will be applied the ellipse after
    @return: a point (y, x)
    @author: Théo L.
*/
Point2i fingerprint_boundaries(Mat &image);

/**
    @fn: Point2i pressure_center_computation(Mat &image)
    @brief: computes the coordinates of an estimate pressure center (search for
        a maximum of intensity after having apply a gaussian blur)
    @param: &image: the image on which to look for a pressure center
    @return: a point with the coordinates (y, x)
    @author: William D.
*/
Point2i pressure_center_computation(Mat &image);

/**
    @fn: Point2i parameters_computation(Mat &image, Point2i pressure_center)
    @brief: computes the semi-major and semi-minor axes of the future ellipse
    @param: &image: the image on which will be applied the ellipse after
    @param: pressure_center: the coordinates of the pressure pressure_center
    @return: a point that contains semi-major and semi-minor axes length
    @author: Théo L.
 */
Point2i parameters_computation(Mat &image, Point2i pressure_center);

 /**
    @fn: bool test_ellipse(Point2f const parameters, Point2i const
        pressure_center, Point2i coordinates)
    @brief: tests if a given point is in the ellipse or not
    @param: parameters: semi-major and semi-minor axes
    @param: pressure_center: the coordinates of the pressure pressure_center
    @param: coordinates: the point that is tested
    @return: a boolean function of the tests
    @author: Théo L.
  */
bool test_ellipse(Point2f const parameters, Point2i const pressure_center,
    Point2i coordinates);

/**
    @fn: Mat ellipse(Point2i const parameters, Point2i const pressure_center,
        Point2i dimensions)
    @brief: tests for each point if it is in the ellipse or not, and store the
        result
    @param: parameters: semi-major and semi-minor axes
    @param: pressure_center: the coordinates of the pressure pressure_center
    @param: dimensions: dimensions of the image
    @return: a Mat object which values are 0 or 1 (0 : true, 1 : false)
    @author: Théo L.
 */
Mat ellipse(Point2i const parameters, Point2i const pressure_center,
    Point2i dimensions);

/**
    @fn: void per_layer_filtering(Mat &image, Mat &protected_zone)
    @brief: apply the coefficient transform outside the ellipse
    @param: &image: the image on which the filter will be applied
    @param: pressure_center: the coordinates of the pressure pressure_center
    @return: nothing: the image is directly modified
    @author: Théo L.
 */
void per_layer_filtering(Mat &image, Mat &protected_zone);

/**
    @fn: int number_of_iterations(Mat &image, Point2i pressure_center)
    @brief: computes the approximate number of iterations that will be recquired
        to apply correctly the anisotropic filtering process
    @param: &image: the image on which the filter will be applied
    @param: pressure_center: the coordinates of the pressure pressure_center
    @return: an int containing the number of iterations
    @author: Théo L.
 */
int number_of_iterations(Mat &image, Point2i pressure_center);

/**
    @fn: void anisotropic_filtering(Mat &image, Point2i const pressure_center)
    @brief: compute at each step the new ellipse and apply the filter outside
    @param: &image: the image on which the filter will be applied
    @param: pressure_center: the coordinates of the pressure pressure_center
    @return: nothing: the image is directly modified
    @author: Théo L.
 */
void anisotropic_filtering(Mat &image, Point2i const pressure_center);


#endif //MAIN_1_H
