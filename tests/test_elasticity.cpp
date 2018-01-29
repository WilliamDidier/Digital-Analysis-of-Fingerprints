#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "starter2.h"
#include "main2.h"
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
    image = imread(argv[1], 0);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    //TESTING THE ELASTICITY IN THE IMAGE

    cout << "Elasticity of image...";
    convert_to_float(image, image);
    mat zone = get_zone(100,100,25,25, image);
    imshow("zone", zone);
    waitKey(0);
    cout << "done." << std::endl;
}