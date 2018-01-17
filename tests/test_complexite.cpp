#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "starter_1.h"
#include "main_1.h"
#include "starter3.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace cv;
using std::cout;
using std::endl;


int main(int argc, char** argv)
{   string const nomFichier("temps.txt");
    std::ofstream monFlux(nomFichier.c_str());
    if(monFlux)
    { clock_t temps1;
      clock_t temps2;
      int n = std::stoi(argv[1]);
      int m = std::stoi(argv[2]);
      int elt = 3;
      while(elt <16){
        temps1 = clock();
        Mat image = Mat::ones(n,m, CV_32F);
        image = convert_to_float(image);
        Mat kernel(elt,elt,CV_32FC1, Scalar(1./(elt*elt)));
        Mat naive = Convol_Shifted(image, kernel);
        temps2=clock();
        monFlux << elt  << " " << n << " " << m << " " <<  -(double) temps1/CLOCKS_PER_SEC + (double) temps2/CLOCKS_PER_SEC << endl;

        temps1 = clock();
        Mat image2 = Mat::ones(n,m, CV_32F);
        image2 = convert_to_float(image2);
        Mat kernel2(elt,elt,CV_32FC1, Scalar(1./(elt*elt)));
        Mat naive2 = convolution_fft(image2, kernel2);
        temps2=clock();
        monFlux << elt  << " " << n << " " << m << " " <<  -(double) temps1/CLOCKS_PER_SEC + (double) temps2/CLOCKS_PER_SEC << endl;
        elt += 6;
      }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}
