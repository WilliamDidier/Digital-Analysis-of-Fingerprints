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
    cout << "This test program will save all its work to the output directory" << endl;
    cout << "Image succesfully imported" << endl;


    /*FORMATTING THE IMAGE FOR TREATMENT */
    cout << "Converting to gray...";
    cvtColor(image, image, COLOR_BGR2GRAY);
    cout << " Done." << endl;
    cout << "Converting to floating point intensities...";
    image = convert_to_float(image);
    cout << " Done." << endl;


    //TETSING THE SYMETRIES
    Mat image_sym;
    cout << "Testing diagonal symetry...";
    image_sym = symetry_diag(image);
    imwrite("../output/Diagonal_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;

    cout << "Testing y-axis symetry...";
    image_sym = symetry_y(image);
    imwrite("../output/Y-axis_symetry.png", convert_to_int(image_sym));
    cout << " Done." << endl;


    // TESTING THE RECTANGLE DRAWING
    cout << "Inserting rectangles...";
    Rect r1(image.cols/2,image.rows/2,image.cols/4,image.rows/4);
    Rect r2(image.cols/8,image.rows/8,image.cols/3,image.rows/6);
    draw_uniform_rectangle(image, r1, 0.0);
    draw_uniform_rectangle(image, r2, 255.0);
    imwrite("../output/Rectangles.png", convert_to_int(image));
    cout << " Done." << endl;
}
