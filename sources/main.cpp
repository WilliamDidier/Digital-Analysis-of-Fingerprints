#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
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
    Mat grey_image;
    cvtColor(image, grey_image, COLOR_BGR2Luv);
    Rect r(10,10,100,100);
    Mat small_image = grey_image(r);
    small_image = Scalar(0);
    imwrite("Henni_NB.png", grey_image);
    return 0;
}
