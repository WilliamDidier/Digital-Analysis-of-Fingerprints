#include <opencv2/opencv.hpp>

#include "starter_4.h"
#include "starter_1.h"

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
    Mat bin_image ;
    bin_image.create(image.rows, image.cols, CV_32F);

    image = imread(argv[1], 0);
    Mat image_bis = imread(argv[1], 0);

    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    cout << "This test program will save all its work to the main directory" << endl;
    cout << "Image succesfully imported" << endl;
    convert_to_float(image, image);

    /* TESTING THE BINARIZATION OF THE IMAGE */
    binarization(image, bin_image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", bin_image );
    waitKey(0);
    convert_to_int(bin_image, image);
    imwrite("../output/test_bin.png", image);
    cout << "Binarization done." << endl;

    /* TESTING THE LEVELS COMPUTATION */
    convert_to_float(image_bis, image_bis);
    cout << "woullaye" << endl;
    vector<int> levels = levels_computation(image_bis);
    cout << "c le bendo" << endl;
    print_vector(levels);
    cout << "Levels computation done." << endl;

    cout << endl << "All tests have passed successfully, well done !" << endl;
}
