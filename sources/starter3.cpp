#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>

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

  return img_complexe;
}

Mat img_magnitude(Mat img_complexe){
  Mat tab[] = {Mat_<float>(img_complexe), Mat::zeros(img_complexe.size(), CV_32F)};
  //on sépare partie imaginaire et partie réell
  split(img_complexe, tab);
  // on prend la norme du résultat, c'est à dire la magnitude
  magnitude(tab[0], tab[1], tab[0]);
  Mat res = tab[0];

  // on met à l'échelle logarythmique
  res += Scalar::all(1);
  log(res, res);
  // on remet l'image à la taille initiale
  res = res(Rect(0, 0, res.cols & -2, res.rows & -2));

  //on transforme la matrice avec des float entre 0 et 1 pour qu'elle soit affichable
  normalize(res, res, 0, 1, NORM_MINMAX);

  return res;Mat O = Mat::ones(2, 2, CV_32F);
}

Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows){
  Mat res;
  idft(image, res, DFT_REAL_OUTPUT|DFT_SCALE);
  cv::Mat finalImage;

  normalize(res, finalImage, 0, 1, NORM_MINMAX);

  return finalImage(Rect(0, 0, nbCols, nbRows));
}

Mat convolution_matrice(Mat image1, Mat image2){
  Mat image_complex1 = transfo_fourier(image1);
  Mat image_complex2 = transfo_fourier(image2);

  Mat produit = image_complex1 * image_complex2;

  Mat res = inv_transfo_fourier(produit);
  // std::cout << produit<< std::endl;

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


  Mat kernel(3,3,CV_32FC1, Scalar(1));
  std::cout << kernel << std::endl;
  Mat naive = Convol_Centered(image, kernel);
  // std::cout << naive << std::endl;
  imshow("naive", naive);
  waitKey(0);
  Mat with_transorm = convolution_matrice(kernel, kernel);
  // std::cout << with_transorm << std::endl;
  // imshow("with_transorm", with_transorm);
  // waitKey(0);
}
