#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "starter_1.h"
#include "blur.h"

using namespace cv;
using std::cout;
using std::endl;


/*int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: Digital_anlysis <Image_Path> [Test]\n");
        return -1;
    }
    Mat image;
    image = imread(argv[1], 0);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    image = convert_to_float(image);
    test_blur(image);
    imwrite("../test_filter.png", convert_to_int(image));
}*/
