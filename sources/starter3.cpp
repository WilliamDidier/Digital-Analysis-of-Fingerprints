#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <vector>

#include <cmath>

float pi = 3.14159265359;


using namespace cv;

Mat convert_to_floatXXX(Mat image){
  Mat dst;
  image.convertTo(dst, CV_32F, 1.0/255.0);
  return(dst);
}



float produit_coefbycoef(Mat A, Mat B){
  /*
  Produit coefficient par coefficient, A et B doivent
  être de même dimension
  */
  float res = 0;
  for (int i = 0; i < A.cols; i++){
    for (int j = 0; j < A.rows; j++){
      float tmp = A.at<float>(j,i);
      float tmp2 = B.at<float>(j,i);
      res += tmp*tmp2;
    }
  }
  return res;
}

Mat Convol_TopRight(Mat X, Mat H){
/*
Donne X**H, centré sur le coefficient en haut à droite de la matrice H
Données entières !!
*/
// std::cout << X << std::endl;
// std::cout << H << std::endl;
  uint ColX = X.cols;
  uint RowX = X.rows;
  uint ColH = H.cols;
  uint RowH = H.rows;
  Mat Res(RowX, ColX, CV_32FC1);
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  Rect roi = Rect(ColH-1,0,ColX,RowX);
  X.copyTo(BigX(roi));
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      Rect tmp = Rect(i1,j1,ColH,RowH);
      // std::cout << H << std::endl;
      // std::cout << produit_coefbycoef(BigX(tmp),H) << std::endl;
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
  Mat Res(RowX, ColX, CV_32FC1);
  Mat BigX = Mat::zeros(RowX+RowH-1, ColX+ColH-1, CV_32FC1);
  Rect roi = Rect((ColH-1)/2,(RowH-1)/2,ColX,RowX);
  X.copyTo(BigX(roi));
  for (int i1 = 0; i1 < ColX; i1++){
    for (int j1 = 0; j1 < RowX; j1++){
      Rect tmp = Rect(i1,j1,ColH,RowH);
      //std::cout << BigX(tmp) << std::endl;
      //std::cout << produit_coefbycoef(BigX(tmp),H) << std::endl;
      Res.at<float>(j1, i1) = produit_coefbycoef(BigX(tmp),H);
    }
  }
  //std::cout << Res << std::endl;
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

Mat convolution_fft(Mat x, Mat h){

  Mat trans_mat = (Mat_<double>(2,3) << 1, 0, -1, 0, 1, -1);
  warpAffine(x,x,trans_mat,x.size());
  Mat X = transfo_fourier(x);

  copyMakeBorder(h, h, 0, x.rows - h.rows, 0, x.cols - h.cols, BORDER_CONSTANT, Scalar::all(0));
  Mat H = transfo_fourier(h);

  Mat Y;
  mulSpectrums(X,H,Y,0,false);

  // Mat S(Y.rows, Y.cols, CV_32FC2, Scalar(0,0));
  // for (int sx = 0; sx < X.rows; sx++){
  //   for (int sy = 0; sy < X.cols; sy++){
  //     float tmp1 = float(sx)/X.rows;
  //     float tmp2 = float(sy)/X.cols;
  //     S.at<Scalar>(sy,sx) = Scalar(cos(2*pi*(tmp1+tmp2)), sin(2*pi*(tmp1+tmp2)));
  //   }
  // }
  // std::cout << S << std::endl;
  // mulSpectrums(Y,S,Y,0,false);

  Mat res = inv_transfo_fourier(Y, x.cols, x.rows);
  // std::cout << produit<< std::endl;

  return res;

}




/*int main(int argc, char** argv){

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

  image = convert_to_floatXXX(image);
  imshow("image", image);
  waitKey(0);
  Mat kernel(3,3,CV_32FC1, Scalar(1./9.));
  //std::cout << image << std::endl;
  Mat naive = Convol_Centered(image, kernel);
  // std::cout << naive << std::endl;
  imshow("naive", naive);
  waitKey(0);
  Mat with_transorm = convolution_fft(image, kernel);
  imshow("with_transorm", with_transorm);
  // std::cout << with_transorm(Rect(0,0,10,10)) << std::endl;
  waitKey(0);
}*/
