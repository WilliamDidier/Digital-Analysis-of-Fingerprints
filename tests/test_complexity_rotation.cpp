#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include "starter2.h"
#include "main2.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace cv;
using std::cout;
using std::endl;

void create_file(std::ofstream &monFlux, clock_t temps1, clock_t temps2, clock_t temps3, clock_t temps4, int m, int n){
  monFlux << n << " " << m << " " <<  -(double) temps1/CLOCKS_PER_SEC + (double) temps2/CLOCKS_PER_SEC;
  monFlux << " " << -(double) temps3/CLOCKS_PER_SEC + (double) temps4/CLOCKS_PER_SEC << endl;
}

int main(int argc, char** argv)
{
  clock_t temps1;
  clock_t temps2;
  clock_t temps3;
  clock_t temps4;
  string const nomFichier1("compare_source_bicubic.txt");

  std::ofstream monFlux1(nomFichier1.c_str());


  for (int n = 2; n<3000; n+=100){
      float angle = 25;
      temps1 = clock();
       Mat image = Mat::ones(256+n,256+n, CV_32F);
      // Mat image;
      // image = imread(argv[1], 0);
      convert_to_float(image, image);
      Mat img_to_dest = rotate_img_from_source(image, angle);

      temps2=clock();
      temps3= clock();
      Mat img_from_source = rotate_img_from_source_bicubic(image, angle);

      temps4=clock();
      create_file(monFlux1, temps1, temps2, temps3, temps4, n, n);

     cout << n << endl;
      }
}
