#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>

using namespace cv;

int produit_coefbycoef(Mat A, Mat B){
  /*
  Produit coefficient par coefficient, A et B doivent
  être de même dimension
  */
  int res = 0;
  for (int i = 0; i < A.cols; i++){
    for (int j = 0; j < A.rows; j++){
      Scalar tmp = A.at<uchar>(j,i);
      Scalar tmp2 = B.at<uchar>(j,i);
      res += tmp[0]*tmp2[0];
    }
  }
  return res;
}

Mat Convol_TopRight(Mat X, Mat H){
/*
Donne X**H, centré sur le coefficient en haut à droite de la matrice H
Données entières !!
*/
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  Mat Res(RowX, ColX, CV_8UC1);
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_8UC1);
  Rect roi = Rect(ColH-1,0,ColX,RowX);
  X.copyTo(BigX(roi));
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      Rect tmp = Rect(i1,j1,ColH,RowH);
      //std::cout << BigX(tmp) << std::endl << H << std::endl;
      //std::cout << produit_coefbycoef(BigX(tmp),H) << std::endl;
      Res.at<uchar>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}

Mat Convol_Centered(Mat X, Mat H){
/*
Donne X**H, centré sur le coeffic#include <time.h>ient au mileu de la matrice H
Pour H : matrice carrée impaire obligatoirement
*/
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  Mat Res(RowX, ColX, CV_8UC1);
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_8UC1);
  Rect roi = Rect((ColH-1)/2,(RowH-1)/2,ColX,RowX);
  X.copyTo(BigX(roi));
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      Rect tmp = Rect(i1,j1,ColH,RowH);
      //std::cout << BigX(tmp) << std::endl << H << std::endl;
      //std::cout << produit_coefbycoef(BigX(tmp),H) << std::endl;
      Res.at<uchar>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}

// int main(int argc, char** argv){
//   Mat D = Mat::ones(3,3,CV_8UC1);
//   Mat E = (Mat_<int>(3,3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
//   Mat F = Mat::ones(9,9,CV_8UC1);
//   // srand(time(NULL));
//   // for (int i1 = 0; i1 < 9; i1++){
//   //   for (int j1 = 0; j1 < 9; j1++){
//   //     int nombre_aleatoire = rand();
//   //     F.at<uchar>(j1, i1) = nombre_aleatoire;
//   //   }
//   // }
//   // Mat A = Convol_TopRight(F,D);
//   // Mat B = Convol_Centered(F,D);
//   // std::cout << A << std::endl;
//   // std:: cout << B << std::endl;
//   // std:: cout << (A-B) + (B-A) << std::endl;
//   if ( argc != 2 )
//   {
//       printf("usage: DisplayImage.out <Image_Path>\n");
//       return -1;
//   }
//   Mat image;
//   image = imread(argv[1], 0);
//   if (!image.data)
//   {
//       printf("No image data \n");
//       return -1;
//   }
//   imshow("Display Image", image);
//   waitKey(0);
//   Mat image2 = Convol_TopRight(image,image);
//   imshow("Image Top Right", image2);
//   waitKey(0);
//
//   return 0;
// }
