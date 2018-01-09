#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int draw_uniform_rectangle (uint x, uint y, uint sx, uint sy, uint color, Mat image){

  Rect r(x,y,sx,sy);
  Mat crop_image;
  crop_image = image(r);
  crop_image = Scalar(color);
  return 0;
}

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
    cvtColor(image, grey_image, COLOR_BGR2GRAY);
    draw_uniform_rectangle(10,10,100,100,255, grey_image);
    draw_uniform_rectangle(150,150,50,10,0, grey_image);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", grey_image);
    waitKey(0);
    return 0;
}
