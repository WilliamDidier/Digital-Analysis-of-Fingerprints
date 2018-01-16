#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include "starter3.h"

using namespace cv;

float produit_coefbycoef(Mat A, Mat B){
  /**
  somme du produit par coefficient, A et B doivent
  être de même dimension
  */
  float res = 0;
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < A.cols; j++){
      //on récupère les coordonnées i et j de chaque matrice
      float tmp = A.at<float>(i,j);
      float tmp2 = B.at<float>(i,j);
      res += tmp*tmp2;
    }
  }
  return res;
}

Mat Convol_DownRight(Mat X, Mat H){
/*
Donne X**H, centré sur le coefficient en haut à droite de la matrice H
Données entières !!
*/
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  // on crée une matrice de flottant de la même dimension que X
  Mat Res(RowX, ColX, CV_32FC1);
  // On complète la matrice X avec colH-1 zéros en bas et à gauche ( pour régler les problèmes de bord)
  // Pour cela on crée une matrice de dimaension supérieure à X
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  // on sélectionne la région de la dimension de X
  Rect roi = Rect(ColH-1,0,ColX,RowX);
  // On copie X sur la région
  X.copyTo(BigX(roi));
  // Pour chaque pixel de X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      //... on sélectionne une imagette de dimension H partant du pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // ... et on complète la matrice résultat par la somme du produit coef par coef des deux matrices
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
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
  // on crée une matrice de flottant de la même dimension que X
  Mat Res(RowX, ColX, CV_32FC1);
  // On complète la matrice X avec colH-1 zéros tout autours de X ( pour régler les problèmes de bord)
  // Pour cela on crée une matrice de dimaension supérieure à X
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
    // on sélectionne la région de la dimension de X
  Rect roi = Rect((ColH-1)/2,(RowH-1)/2,ColX,RowX);
    // On copie X sur la région
  X.copyTo(BigX(roi));
    // Pour chaque pixel de X ...
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
        //... on sélectionne une imagette de dimension H partant du pixel...
      Rect tmp = Rect(i1,j1,ColH,RowH);
        // ... et on complète la matrice résultat par la somme du produit coef par coef des deux matrices
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  return Res;
}



Mat transfo_fourier( Mat image){
  /*
  Donne une matrice complexe en sortie qui est la transformée de Fourier de
  la matrice en entrée
  */
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
