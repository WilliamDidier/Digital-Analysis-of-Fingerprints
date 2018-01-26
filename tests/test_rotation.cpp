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
    Point2f pt(src.cols/2, src.rows/2);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows), INTER_CUBIC, BORDER_TRANSPARENT,Scalar(0));
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
    convert_to_float(image, image);

    int angle = 120;

    Mat rotation_weighted = rotate_img_from_source_weighted(image, angle);
    // Mat rotation_from_source_bicubic = rotate_img_from_source_bicubic(image, angle);
    // Mat rotation_from_source = rotate_img_from_source(image, angle);
    // Mat rotation_from_source_bilinear = rotate_img_from_source_bilinear(image, angle);
    Mat true_rotation = rotate(image, angle);
    // // convert_to_int(rotation_from_source, rotation_from_source);
    // convert_to_int(rotation_from_source_bicubic, rotation_from_source_bicubic);
    // convert_to_int(rotation_from_source_bilinear, rotation_from_source_bilinear);
    convert_to_int(true_rotation, true_rotation);
    convert_to_int(rotation_weighted, rotation_weighted);
    convert_to_int(image, image);

     // imwrite("tests/rotation_from_source_bilinear.png", rotation_from_source_bilinear );
     // imwrite("tests/rotation_from_source.png", rotation_from_source);
     // imwrite("tests/rotation_from_source_bicubic.png", rotation_from_source_bicubic);
     imwrite("tests/true_rotation.png", true_rotation);
     imwrite("tests/rotation_weighted.png", rotation_weighted);

    cout << " Done." << endl;
}
