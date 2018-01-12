#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "../sources/starter_1.h"

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


    /* TESTING THE FLOAT AND COLOR CONVERSION */
    cout << "Converting to gray...";
    cvtColor(image, image, COLOR_BGR2GRAY);
    imwrite("Grey_Image.png", image);
    image = convert_to_float(image);
    cout << " Done." << endl;


    /*TETSING THE SYMETRIES*/
    Mat image_sym;
    cout << "testing diagonal symetry...";
    image_sym = symetry_diag(image);
    imwrite("Diagonal_symetry.png", image_sym);
    cout << " Done." << endl;

    cout << "testing y-axis symetry...";
    image_sym = symetry_y(image);
    waitKey(0);
    imwrite("Y-axis_symetry.png", image_sym);
    cout << " Done." << endl;


    /* TESTING THE RECTANGLE DRAWING*/
    cout << "Inserting rectangles" << endl;
    cout << image.rows << " "<< image.cols << endl;
    Rect r1(image.cols/2,image.rows/2,image.cols/4,image.rows/4);
    Rect r2(image.cols/8,image.rows/8,image.cols/3,image.rows/6);
    //waitKey(0);
    draw_uniform_rectangle(image, r1, 0.0);
    draw_uniform_rectangle(image, r2, 255.0);
    imwrite("Rectangles.png", image);
    cout << " Done." << endl;

    return 0;
}
