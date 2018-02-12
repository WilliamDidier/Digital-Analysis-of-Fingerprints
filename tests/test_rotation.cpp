#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "Rotation.h"
using namespace cv;
using std::cout;
using std::endl;



Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2, src.rows/2);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows), INTER_LINEAR, BORDER_CONSTANT,Scalar(255));
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
    float angle = 20;
    Rotation rot(WEIGHTED, angle);
    Mat rotation_to_dest = rotate_img_to_dest(image, angle);
    rotation_to_dest = interpolation_nearest_neighboor(rotation_to_dest);
    Mat rotation_weighted = rot.apply(image);
    rot.set_method(BICUBIC);
    Mat rotation_from_source_bicubic = rot.apply(image);
    rot.set_method(CLASSIC);
    Mat rotation_from_source = rot.apply(image);
    rot.set_method(BILINEAR);
    Mat rotation_from_source_bilinear = rot.apply(image);
    Mat true_rotation = rotate(image, angle);
    convert_to_int(rotation_to_dest, rotation_to_dest);
    convert_to_int(rotation_from_source, rotation_from_source);
    convert_to_int(rotation_from_source_bicubic, rotation_from_source_bicubic);
    convert_to_int(rotation_from_source_bilinear, rotation_from_source_bilinear);
    convert_to_int(true_rotation, true_rotation);
    convert_to_int(rotation_weighted, rotation_weighted);
    convert_to_int(image, image);
    imwrite("tests/rotation_to_dest.png", rotation_to_dest);
    imwrite("tests/rotation_from_source_bilinear.png", rotation_from_source_bilinear );
    imwrite("tests/rotation_from_source.png", rotation_from_source);
    imwrite("tests/rotation_from_source_bicubic.png", rotation_from_source_bicubic);
    imwrite("tests/true_rotation.png", true_rotation);
    imwrite("tests/rotation_weighted.png", rotation_weighted);

    cout << " Done." << endl;
}
