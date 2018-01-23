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
    Mat rotation_to_dest_corr ;
    Mat rotation_from_source_corr;
    cout << "Rotation of image...";
    image = convert_to_float(image);
    int angle = 30;
    Mat rotation_to_dest = rotate_img_to_dest(image, angle);
    rotation_to_dest_corr = interpolation_nearest_neighboor(rotation_to_dest);
    Mat rotation_from_source = rotate_img_from_source(image, angle);
    rotation_from_source_corr = interpolation_bicubic(rotation_from_source);

    // Mat rotation_from_source_cubic = rotate_img_from_source_cubic(image, angle);
    // imwrite("tests/rotation_to_dest.png", convert_to_int(rotation_to_dest));
    // imwrite("tests/rotation_to_dest_corr.png", convert_to_int(rotation_to_dest_corr));
    imwrite("tests/rotation_from_source.png", convert_to_int(rotation_from_source));
    // imwrite("tests/rotation_from_source_cubic.png", convert_to_int(rotation_from_source_cubic));

    // imshow("rotation2", rotation);
    // waitKey(0);

    cout << " Done." << endl;
}
