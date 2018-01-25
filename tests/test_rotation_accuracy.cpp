#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "starter2.h"
#include <cmath>
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

float mean_error(Mat image1, Mat image2){
  Mat diff;
  absdiff(image1, image2, diff);

  Scalar res = mean(diff);
  return res[0]/255;
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

    //TESTING THE ACCURACY OF THE ROTATION OF THE IMAGE
    Mat rotation_to_dest_corr ;
    Mat rotation_from_source_corr;
    cout << "Rotation accuracy of image..." <<endl;
    convert_to_float(image, image);
    int angle = 45;
    Mat rotation_img_to_dest = rotate_img_to_dest(image, angle);
    rotation_img_to_dest = interpolation_nearest_neighboor(rotation_img_to_dest);
    Mat rotation_from_source_bicubic = rotate_img_from_source_bicubic(image, angle);
    Mat rotation_from_source = rotate_img_from_source(image, angle);
    Mat rotation_from_source_bilinear = rotate_img_from_source_bilinear(image, angle);
    Mat true_rotation = rotate(image, angle);
    convert_to_int(rotation_img_to_dest, rotation_img_to_dest);
    convert_to_int(rotation_from_source, rotation_from_source);
    convert_to_int(rotation_from_source_bicubic, rotation_from_source_bicubic);
    convert_to_int(rotation_from_source_bilinear, rotation_from_source_bilinear);
    convert_to_int(true_rotation, true_rotation);
    float accuracy_source = mean_error(rotation_from_source, true_rotation);
    float accuracy_bilinear = mean_error(rotation_from_source_bilinear, true_rotation);
    float accuracy_bicubic = mean_error(rotation_from_source_bicubic, true_rotation);
    float accuracy_to_dest = mean_error(rotation_img_to_dest, true_rotation);

    cout << "accuracy_to_dest :" << accuracy_to_dest << endl;
    cout << "accuracy_source :" << accuracy_source << endl;
    cout << "accuracy_bilinear :" << accuracy_bilinear << endl;
    cout << "accuracy_bicubic :" << accuracy_bicubic << endl;




    cout << " Done." << endl;
}