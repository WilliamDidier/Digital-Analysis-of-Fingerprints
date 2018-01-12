#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter_1.h"
#include "blur.h"

using namespace cv;
using std::cout;
using std::endl;


int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: Digital_anlysis <Image_Path> [Test]\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    /*
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    */
    //cvtColor(image, grey_image, COLOR_BGR2GRAY);
    Mat grey_image = convert_to_float(image);
    Mat image_blurred;
    grey_image.copyTo(image_blurred);
    //std::cout << image_blurred << std::endl;
    test_blur(image_blurred);
    //std::cout << image_blurred << std::endl;
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image_blurred);
    waitKey(0);
    grey_image = convert_to_int(image_blurred);
    imwrite("blur.png", grey_image);
    /*
    draw_uniform_rectangle(570,570,7,100,0.0, grey_image);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);

    Mat image_sym = symetry_diag(image);
    imshow("Display Image", image_sym);
    waitKey(0);
    imwrite("sym.png", image_sym);

    return 0;
}
