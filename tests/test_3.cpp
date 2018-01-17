#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
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

    image = convert_to_float(image);
    imshow("image", image);
    waitKey(0);
    Mat kernel(3,3,CV_32FC1, Scalar(1./9.));
    //std::cout << image << std::endl;
    Mat naive = Convol_Shifted(image, kernel);
    // std::cout << naive << std::endl;
    imshow("naive", naive);
    waitKey(0);
    Mat with_transorm = convolution_fft(image, kernel);
    imshow("with_transorm", with_transorm);
    // std::cout << with_transorm(Rect(0,0,10,10)) << std::endl;
    waitKey(0);

}
