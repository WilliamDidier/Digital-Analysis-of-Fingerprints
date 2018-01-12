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



Mat transfo_fourier( Mat image){

  Mat optimal;
  //extendre la matrice à la taille optimale
  int  nbRows =   getOptimalDFTSize( image.rows );
  int  nbCols =   getOptimalDFTSize( image.cols );
  //ajouter des zeros sur les bords
  copyMakeBorder(image, optimal, 0, nbRows - image.rows, 0, nbCols - image.cols, BORDER_CONSTANT, Scalar::all(0));

  Mat tab[] = {Mat_<float>(optimal), Mat::zeros(optimal.size(), CV_32F)};
  Mat img_complexe;
  // convertis la matrice réelle en matrice complexe
  merge(tab, 2, img_complexe);
  dft(img_complexe, img_complexe);
  //on sépare partie imaginaire et partie réelle
  split(img_complexe, tab);
  // on prend la norme du résultat, c'est à dire la magnitude
   magnitude(tab[0], tab[1], tab[0]);
   Mat res = tab[0];
   // on remet l'image à la taille initiale
   res = res(Rect(0, 0, res.cols & -2, res.rows & -2));
   //on replace l'image afin qu'elle soit centrée
    // int cx = magI.cols/2;
    // int cy = magI.rows/2;
    // Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    // Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    // Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    // Mat q3(magI, Rect(cx, cy, cx, cy));
    std::cout << res << std::endl;
    
    normalize(res, res, 0, 1, NORM_MINMAX);
    std::cout << res << std::endl;
    return res;


}
int main(int argc, char** argv){

  if ( argc != 2 )
  {
      printf("usage: DisplayImage.out <Image_Path>\n");
      return -1;
  }
  Mat image;
  image = imread(argv[1], 0);
  if (!image.data)
  {
      printf("No image data \n");
      return -1;
  }
  imshow("Display Image", image);
  waitKey(0);
  Mat image2 = transfo_fourier(image);
  imshow("Image TF", image2);
  waitKey(0);

  return 0;
}
