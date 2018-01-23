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
    convert_to_float(image,image);
    // Mat kernel = Normalized_kernel(7,7);
    Mat kernel1 = Gaussian_kernel(9,2,0.2);
    Mat kernel2 = Gaussian_kernel(9,0.2,2);
    Mat kernel3 = Gaussian_kernel(9,2,2);
    Mat naive1 = convolution_fft(image, kernel1);
    convert_to_int(naive1, naive1);
    imwrite("tests/test_convol_fft11.png", naive1);
    cout << " Done." << endl;
    Mat naive2 = convolution_fft(image, kernel2);
    convert_to_int(naive2, naive2);
    imwrite("tests/test_convol_fft22.png", naive2);
    cout << " Done." << endl;
    Mat naive3 = convolution_fft(image, kernel3);
    convert_to_int(naive3, naive3);
    imwrite("tests/test_convol_fft33.png", naive3);
    cout << " Done." << endl;
}
