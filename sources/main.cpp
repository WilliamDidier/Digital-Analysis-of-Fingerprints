#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"

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
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    image = convert_to_float(image);
    //cvtColor(image, image, COLOR_BGR2GRAY);
    imshow("Display Image", image);
    waitKey(0);



    Rect r (10,570,7,100);
    draw_uniform_rectangle(image, r, 1.0);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);

    Mat image_sym = symetry_diag(image);
    imshow("Display Image", image_sym);
    waitKey(0);
    imwrite("sym.png", image_sym);

    return 0;
}
