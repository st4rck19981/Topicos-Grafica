#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void Rotar(Mat imagen, Mat& salida, double angulo, double escala = 1.0) {
    double w = imagen.size().width, h = imagen.size().height;
    double sa = sin(angulo * M_PI / 180), ca = cos(angulo * M_PI / 180);
    double cx = -w / 2.0 * ca - h / 2.0 * sa, cy = w / 2.0 * sa - h / 2.0 * ca;
    sa = fabs(sa);    ca = fabs(ca);
    Size tam((w * ca + h * sa) * escala, (h * ca + w * sa) * escala);
    Mat M = getRotationMatrix2D(Point2f(0, 0), angulo, escala);
    M.at<double>(0, 2) = tam.width / 2 + cx * escala;
    M.at<double>(1, 2) = tam.height / 2 + cy * escala;
    warpAffine(imagen, salida, M, tam);
}

int main()
{
    Mat image = imread("image.jpg");

    //EJERCICIO 1 ZOOM2X
    Mat image1;
    resize(image, image1, Size(), 2, 2);
    namedWindow("image", WINDOW_NORMAL);
    imshow("Original", image);
    imshow("Ejercicio 1: Zoom 2x", image1);

    //EJERCICIO 2 ESPEJO VERTICAL Y HORIZONTAL
    Mat image2;
    flip(image, image2, -1);
    imshow("Ejercicio 2: Espejo Vertical y Horizontal", image2);

    //EJERCICIO 3 ROTAR Y ESCALAR UNA IMAGEN
    Mat image3;
    Rotar(image, image3, 90.0, 1.0);
    imshow("Ejercicio 3: Rotar y Escalar una imagen indicando angulo y escala", image3);
    
    //EJERCICIO 4 INCLINAR LA IMAGEN Y DESPLAZAR
    /*  
    Mat image4;
    //ui->doubleSpinBox_3->value()  falta definir que es UI, y aniadir las librerias
    double inc = tan(1.1*M_PI / 180.0);
    Mat c = (Mat_<double>(2, 3) << 1, inc, -inc * image.size().height / 2.0, 0, 1, 0);     mala sintaxis
    warpAffine(image, image4, c, image.size());
    imshow("Ejercicio 4: Inclinar y Desplazar una imagen en X", image4);
    */

    //EJERCICIO 5 APLICAR TRANSFORMACION AFIN A UNA IMAGEN
    Mat image5;
    Mat pt1(1, 3, CV_32FC2);
    pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
    pt1.at<Vec2f>(0, 1) = Vec2f(100, 0);
    pt1.at<Vec2f>(0, 2) = Vec2f(100, 100);
    Mat pt2(1, 3, CV_32FC2);
    pt2.at<Vec2f>(0, 0) = Vec2f(10, 20);
    pt2.at<Vec2f>(0, 1) = Vec2f(80, 40);
    pt2.at<Vec2f>(0, 2) = Vec2f(20, 70);
    Mat c = getAffineTransform(pt1, pt2);
    warpAffine(image, image5,c,image.size());
    imshow("Ejercicio 5: Transformacion AFIN con 3 puntos origen y 3 puntos destino", image5);
    waitKey(0);

    return 0;
}
