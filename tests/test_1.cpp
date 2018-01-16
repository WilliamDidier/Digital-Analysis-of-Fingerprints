#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: Test_1 <Image_Path> [Test]\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    cout << "Image succesfully imported" << endl;


    //TESTING THE FLOAT AND COLOR CONVERSION
    cout << "Converting to gray...";
    cvtColor(image, image, COLOR_BGR2GRAY);
    imwrite("../Grey_Image.png", image);
    image = convert_to_float(image);
    cout << " Done." << endl;


    //TETSING THE SYMETRIES
    Mat image_sym;
    cout << "Testing diagonal symetry...";
    image_sym = symetry_diag(image);
    imwrite("../Diagonal_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;

    cout << "Testing y-axis symetry...";
    image_sym = symetry_y(image);
    imwrite("../Y-axis_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;


    // TESTING THE RECTANGLE DRAWING
    cout << "Inserting rectangles...";
    Rect r1(image.cols/2,image.rows/2,image.cols/4,image.rows/4);
    Rect r2(image.cols/8,image.rows/8,image.cols/3,image.rows/6);
    draw_uniform_rectangle(image, r1, 0.0);
    draw_uniform_rectangle(image, r2, 255.0);
    imwrite("../Rectangles.png", convert_to_int(image));
    cout << " Done." << endl;


    /* TESTING THE ELLIPTICAL FUNCTION */
    cout << "Testing the ellipse creation...";
    Mat ellipse_test;
    ellipse_test.create(image.cols, image.rows, CV_32F);
    Point2i param(90, 60);
    Point2i press(image.rows/2, image.cols/2);
    ellipse_test = ellipse(param, press, Point2i(image.rows, image.cols));
    imwrite("../fingerprints/test_limpt.png", convert_to_int(ellipse_test));
    cout << " Done. (image saved at fingerprints/test_limpt.png)" << endl;



    /*TESTING THE WEAKENING */
    image = imread("../fingerprints/clean_finger.png", 0);
    cout << "Weakening clean_finger...";
    Point2i pressure_center(image.cols/2, image.rows/2);
    image = convert_to_float(image);
    clean_to_weak_iso(image, pressure_center);
    imwrite("../Weakened_finger.png", convert_to_int(image));
    cout << " Done." << endl;

    /*TESTING THE REINFORCEMENT*/
    image = imread("../fingerprints/weak_finger.png", 0);
    cout << "Reinforcing weak_finger";
    pressure_center = Point2i(image.rows*3/4, image.cols/2);
    image = convert_to_float(image);
    weak_to_clean_iso(image, pressure_center);
    imwrite("../Reinforced_finger.png", convert_to_int(image));
    cout << " Done." << endl;

    /*TESTING THE XLIM YLIM COMPUTATION */
    cout << "Testing the extreme points computation..." << endl;;
    image = imread("../fingerprints/test_limpt.png",0);
    image = convert_to_float(image);
    //assert(parameters_computation(image) == Point2i(69,233));
    cout << " Done" << endl;

    /* TESTING POINTS AIGAIN */
    cout << "Creating image for highest intensity test...";
    image = imread("../fingerprints/black.png", 0);
    Point2i test_pt(image.cols/2, image.rows/2);
    image.at<uchar>(test_pt) = 255;
    imwrite("../black_test.png",image);
    cout << " Done" << endl;

    /*TESTING THE ROI FINDING*/
    cout << "Testing highest intensity zone research...";
    image = imread("../black_test.png", 0);
    Mat gblur;
    image.copyTo(gblur);
    GaussianBlur(image, gblur, Size(17, 17), 0, 0);
    double minVal = 0;
    double maxVal = 0;
    Point minLoc, maxLoc;
    minMaxLoc(gblur, &minVal, &maxVal, &minLoc, &maxLoc);
    Rect roi;
    roi = Rect(maxLoc.x-25, maxLoc.y-25, 50, 50);
    image=image(roi);
    imwrite("../roi.png",image);
    cout << " Done." << endl;

    /*TESTING ON FINGERPRINT*/
    cout << "Testing with fingerprint...";
    Mat image_color = imread("../fingerprints/clean_finger.png", 1);
    image_color.copyTo(image);
    cvtColor(image_color, image, COLOR_BGR2GRAY);
    GaussianBlur(image, image, Size(11,11), 0, 0);
    minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc);
    circle(image_color, minLoc, 5, Scalar(0,0,255));
    imwrite("img_roi.png", image_color);


    /*TESTING ISOTROPIC FILTERING*/
    /*cout << "Testing isotropic transformation..." << endl;
    image = imread("../fingerprints/test_limpt.png",0);
    apply_iso(image, pressure_center);
    imwrite("../test_iso.png", convert_to_int(image));
    cout << " Done." << endl;*/


}
