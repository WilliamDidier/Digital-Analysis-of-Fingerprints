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
    //TESTING THE CONVOLUTION WITH FFT
    cout << "convol thanks to fft...";
    convert_to_float(image, image);
    Mat kernel = Gaussian_kernel(5,2,2);
    Mat naive = convolution_fft(image, kernel);
    convert_to_int(naive, naive);
    imwrite("tests/test_convol_fft.png", naive);
    waitKey(0);
    cout << " Done." << endl;
}
