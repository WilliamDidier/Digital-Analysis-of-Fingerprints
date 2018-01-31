#ifndef ELLIPTICAL_MODELLING_H
#define ELLIPTICAL_MODELLING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

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
   @fn bool test_ellipse(Point2f const parameters, Point2i const
       pressure_center, Point2i coordinates)
   @brief Tests if a given point is in the parametrized ellipse or not
   @param parameters semi-major and semi-minor axes length
   @param pressure_center coordinates of the pressure center
   @param pt the point that is tested
   @return A boolean representing the belonging of the point to the ellipse
   @author Théo L.
 */
bool test_ellipse(Point2f const parameters, Point2i const pressure_center,
    Point2i coordinates);

/**
    @fn Mat ellipse(Point2i const parameters, Point2i const pressure_center,
        Point2i dimensions)
    @brief Creats a binary matrix representing the parametrized ellipse
    @param parameters semi-major and semi-minor axes
    @param pressure_center coordinates of the pressure center
    @param dimensions dimensions of the image
    @return A binary Mat object representing an ellipse
    @author Théo L.
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

/**
    @fn: Point2i ellipse_erosion_parameters(Mat &image, Point2i pressure_center)
    @brief: compute the parameters of the ellipse that will select the eroded
        zone
    @param: &image: the image on which the filter will be applied
    @param: pressure_center: the coordinates of the pressure pressure_center
    @return: a point containing the axes of the ellipse
    @author: Théo L.
 */
Point2i ellipse_erosion_parameters(Mat &image, Point2i pressure_center);

/**
    @fn: void dilation(int, void*, Mat &src, Mat &dst)
    @brief: apply a morphological dilation to an image
    @param: &src: the image on which the filter will be applied
    @param: &dst: the location where the image will be stored
    @return: nothing: the image is stored at "&src"
    @author: Théo L.
*/
void dilation(int, void*, Mat &src, Mat &dst);

/**
    @fn: void selected_dilation_Protection(Mat &src, Mat &original, Point2i
        pressure_center)
    @brief: select a zone that will be protected from dilation operation, and
        paste it on the dilated image
    @param: &image: &src: the image on which the protection will be applied
    @param: &original: the original image
    @return: nothing: the image is directly modified
    @author: Théo L.
 */
void selected_dilation_Protection(Mat &src, Mat &original, Point2i pressure_center);


#endif //ELLIPTICAL_MODELLING_H
