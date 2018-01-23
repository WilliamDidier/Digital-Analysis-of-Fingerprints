#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "starter2.h"
using namespace cv;
using std::cout;
using std::endl;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}

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
    //TESTING THE ROTATION OF THE IMAGE
    cout << "Rotation of image...";
    image = convert_to_float(image);
    int angle = 30;
    Mat rotation = rotate_img(image, angle);
    // rotation = interpolation_bicubic(rotation);

    imwrite("tests/test_rotation.png", convert_to_int(rotation));
    imwrite("tests/image.png", convert_to_int(image));
    imshow("image", image);
    waitKey(0);
    imshow("rotation", rotation);
    waitKey(0);
    // imshow("rotation2", rotation);
    // waitKey(0);

    cout << " Done." << endl;
}
