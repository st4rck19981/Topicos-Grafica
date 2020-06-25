#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
    Mat image = imread("image.jpg");

    //EJERCICIO 1 TRANSFORMACION PERSPECTIVA DE UNA IMAGEN
    Mat image1;
    double w = image.size().width, h = image.size().height;
    Mat pt1(1, 4, CV_32FC2);
    pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
    pt1.at<Vec2f>(0, 1) = Vec2f(w, 0);
    pt1.at<Vec2f>(0, 2) = Vec2f(w, h);
    pt1.at<Vec2f>(0, 3) = Vec2f(0, h);
    Mat pt2(1, 4, CV_32FC2);
    pt2.at<Vec2f>(0, 0) = Vec2f(w * 0.3, 0);
    pt2.at<Vec2f>(0, 1) = Vec2f(w * 0.7, 0);
    pt2.at<Vec2f>(0, 2) = Vec2f(w , h);
    pt2.at<Vec2f>(0, 3) = Vec2f(0, h);
    Mat c = getPerspectiveTransform(pt1, pt2);
    warpPerspective(image, image1, c, image.size());

    namedWindow("image", WINDOW_NORMAL);
    imshow("Original", image);
    imshow("Ejercicio 1: Transformacion Perspectiva de una imagen", image1);

    //EJERCICIO 2 TRANSFORMACION ALEATORIA DE UNA IMAGEN CON UN RADIO DE DEFORMACION
    Mat image2;
    int m = 5;
    Mat mapa1(image.size(), CV_32FC1);
    Mat mapa2(image.size(), CV_32FC1);
    for (int y = 0; y < image.size().height; y++) {
        for (int x = 0; x < image.size().width; x++) {
            mapa1.at<float>(y, x) = x +rand()%(2 * m + 1) - m;
            mapa2.at<float>(y, x) = y +rand()%(2 * m + 1) - m;
        }
    }
    remap(image, image2, mapa1, mapa2, INTER_NEAREST);
    imshow("Ejercicio 2: Transformacion Aleatoria con radio 5", image2);

    //EJERCICIO 3 TRANSFORMACION DE ACRISTALADO
    Mat image3;
    for (int y = 0; y < image.size().height; y++) {
        for (int x = 0; x < image.size().width; x++) {
            mapa1.at<float>(y, x) = x - x % m + y % m;
            mapa2.at<float>(y, x) = y - y % m + x % m;
        }
    }
    remap(image, image3, mapa1, mapa2, INTER_NEAREST);
    imshow("Ejercicio 3: Transformacion de acristalado con radio 5", image3);
    waitKey(0);

    return 0;
}
