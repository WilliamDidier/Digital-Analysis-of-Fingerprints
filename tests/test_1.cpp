#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "../sources/starter_1.h"
#include "../sources/main_1.h"
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

    /*
    //TESTING THE FLOAT AND COLOR CONVERSION
    cout << "Converting to gray...";
    cvtColor(image, image, COLOR_BGR2GRAY);
    imwrite("./Grey_Image.png", image);
    image = convert_to_float(image);
    cout << " Done." << endl;


    //TETSING THE SYMETRIES
    Mat image_sym;
    cout << "testing diagonal symetry...";
    image_sym = symetry_diag(image);
    imwrite("./Diagonal_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;

    cout << "testing y-axis symetry...";
    image_sym = symetry_y(image);
    imwrite("./Y-axis_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;


    // TESTING THE RECTANGLE DRAWING
    cout << "Inserting rectangles" << endl;
    Rect r1(image.cols/2,image.rows/2,image.cols/4,image.rows/4);
    Rect r2(image.cols/8,image.rows/8,image.cols/3,image.rows/6);
    draw_uniform_rectangle(image, r1, 0.0);
    draw_uniform_rectangle(image, r2, 255.0);
    imwrite("./Rectangles.png", convert_to_int(image));
    cout << "Done." << endl;
    */

    // TESTING THE ELLIPTICAL FUNCTION
    image = convert_to_float(image);
    Mat ellipse_test;
    ellipse_test.create(image.cols, image.rows, CV_32F);
    Point2i param(90, 60);
    Point2i press(image.rows/2, image.cols/2);
    ellipse_test = ellipse(param, press, Point2i(image.rows, image.cols));
    imwrite("./test_filter.png", convert_to_int(ellipse_test));

    /* TESTING POINTS AIGAIN */
    image = imread("../fingerprints/black.png", 0);
    Point2i test_pt(image.cols/2, image.rows/2);
    cout << test_pt << endl;
    image.at<uchar>(test_pt) = 255;
    imwrite("../black_test.png",image);

    /*TESTING THE WEAKENING */
    image = imread("../fingerprints/clean_finger.png", 0);
    cout << "Weakening clean_finger..." << endl;
    Point2i pressure_center(image.cols/2, image.rows/2);
    image = convert_to_float(image);
    clean_to_weak_iso(image, pressure_center);
    imwrite("../Weakened_finger.png", convert_to_int(image));
    cout << " Done." << endl;

    /*TESTING THE REINFORCEMENT*/
    image = imread("../fingerprints/weak_finger.png", 0);
    cout << "Reinforcing weak_finger" << endl;
    pressure_center = Point2i(image.cols/2, image.rows/2);
    image = convert_to_float(image);
    weak_to_clean_iso(image, pressure_center);
    imwrite("../Reinforced_finger.png", convert_to_int(image));
    cout << " Done." << endl;

    /*TESTING THE XLIM YLIM COMPUTATION */
    image = imread("../fingerprints/clean_finger.png",0);
    image = convert_to_float(image);
    cout << parameters_computation(image) << endl;

}
