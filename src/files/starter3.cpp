#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include "starter3.h"

using namespace cv;

float produit_coefbycoef(Mat A, Mat B){
  /**
    @fn float produit_coefbycoef(Mat A, Mat B)
    @brief make the sum of product term by term of two matrix
    @param Input : 2 matrix with the same size
    @return a float
    @author Théo M. & Romain
  */
  float res = 0;
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < A.cols; j++){
      //one get the coordinates i and j of each matrix
      float tmp = A.at<float>(i,j);
      float tmp2 = B.at<float>(i,j);
      res += tmp*tmp2;
    }
  }
  return res;
}

Mat Convol_DownRight(Mat X, Mat H){
  /**
    @fn Mat Convol_DownRight(Mat X, Mat H)
    @brief give X**H, centered on the downright coefficient of the matrix H
    @param Input : 2 matrix
    @return the matrix of convolution
    @author Théo M. & Romain
  */
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  //  one create a float matrix which has the same dimension than X
  Mat Res(RowX, ColX, CV_32FC1);
  // One complete the matrix X with colH-1 zeros on the left and at the bottom ( to remove the bordure issues)
  // To do that, one create a matrix of dimension greater than X
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  // one select the region of dimension X
  Rect roi = Rect(ColH-1,0,ColX,RowX);
  // One copy X on the region
  X.copyTo(BigX(roi));
  // For each pixel of X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      //... one sélect a small image of dimension H having for beginning the current pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // ... and finally one complet the result matrix by the sum of product term by term of two matrix
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}

Mat Convol_Centered(Mat X, Mat H){
  /**
    @fn Mat Convol_Centered(Mat X, Mat H)
    @brief give X**H, centered on the centered coefficient of the matrix H
    @param Input : 2 matrix, H must be a square matrix with an odd dimension
    @return the matrix of convolution
    @author Théo M. & Romain
  */
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  //  one create a float matrix which has the same dimension than X
  Mat Res(RowX, ColX, CV_32FC1);
  // One complete the matrix X with colH-1 zeros around X ( to remove the bordure issues)
  // To do that, one create a matrix of dimension greater than X
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  // one select the region of dimension X
  Rect roi = Rect((ColH-1)/2,(RowH-1)/2,ColX,RowX);
  // One copy X on the region
  X.copyTo(BigX(roi));
  // For each pixel of X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      //... one sélect a small image of dimension H having for beginning the current pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // ... and finally one complet the result matrix by the sum of product term by term of two matrix
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}



Mat transfo_fourier( Mat image){
  /**
    @fn Mat transfo_fourier( Mat image)
    @brief give a complex Matrix which is the result of the fourier transform of initial matrix
    @param Input : one matrix
    @return the fourier transform of the matrix
    @author Théo M. & Romain
  */
  Mat optimal;
  //extend the matrix with the optimal size
  int  nbRows =   getOptimalDFTSize( image.rows );
  int  nbCols =   getOptimalDFTSize( image.cols );
  //add zeros on the boundaries
  copyMakeBorder(image, optimal, 0, nbRows - image.rows, 0, nbCols - image.cols, BORDER_CONSTANT, Scalar::all(0));
  Mat tab[] = {Mat_<float>(optimal), Mat::zeros(optimal.size(), CV_32F)};
  Mat img_complexe;
  // convert the real matrix to a complex matrix
  merge(tab, 2, img_complexe);
  dft(img_complexe, img_complexe);
  return img_complexe;
}

Mat img_magnitude(Mat img_complexe){
  /**
    @fn Mat img_magnitude(Mat img_complexe)
    @brief give a complex Matrix which is the result of the fourier transform of initial matrix
    @param Input : one matrix
    @return the fourier transform of the matrix
    @author Théo M. & Romain
  */
  /*
  Entrée : une matrice à coefficient complexe ( résultant d'une DFT le plus souvent)
  Sortie : on renvoie la matrice correspondant à l'image du spectre de la
  matrice en entrée
  */
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
  //on transforme la matrice avec des float entre 0 et 1
  normalize(res, res, 0, 1, NORM_MINMAX);
  return res;Mat O = Mat::ones(2, 2, CV_32F);
}

Mat inv_transfo_fourier(Mat image, int nbCols, int nbRows){
  /*
  on applique la transformée inverse
  */
  Mat res;
  // On applique l'idft avec pour résultat une matrice réelle
  idft(image, res, DFT_REAL_OUTPUT|DFT_SCALE);
  Mat finalImage;
  //on transforme la matrice avec des float entre 0 et 1
  normalize(res, finalImage, 0, 1, NORM_MINMAX);
  return finalImage(Rect(0, 0, nbCols, nbRows));
}

Mat convolution_fft(Mat x, Mat h){
  /*
  on applique la convolution de matrice en passant par la FFT
  */
  Mat X = transfo_fourier(x);
  //on complète h avec des  0 pour atteindre la taille de x
  copyMakeBorder(h, h, 0, x.rows - h.rows, 0, x.cols - h.cols, BORDER_CONSTANT, Scalar::all(0));
  Mat H = transfo_fourier(h);

  Mat Y;
  // on fait la multiplication coef par coef de H et X
  mulSpectrums(X,H,Y,0,false);
  Mat res = inv_transfo_fourier(Y, x.cols, x.rows);
  return res;
}
