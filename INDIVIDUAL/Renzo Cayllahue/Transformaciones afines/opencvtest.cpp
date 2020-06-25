
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>
#define M_PI 3.141592653589793238463

using namespace cv;
using namespace std;


void zoom(Mat imagen)
{
	resize(imagen, imagen, Size(), 2, 2);
	imshow("ZOOM 2X", imagen);
}

void espejo(Mat imagen, int code)
{
	flip(imagen, imagen, code);
	imshow("Ejercicio 2: espejo vertical horizontal", imagen);
}

void Rotar(Mat imagen, Mat& salida, double angulo, double escala = 1)
{
	double w = imagen.size().width, h = imagen.size().height;
	double sa = sin(angulo * M_PI / 180), ca = cos(angulo * M_PI / 180);
	double cx = -w / 2 * ca - h / 2 * sa, cy = w / 2 * sa - h / 2 * ca;
	sa = fabs(sa); ca = fabs(ca);
	Size tam((w * ca + h * sa) * escala, (h * ca + w * sa) * escala);
	Mat M = getRotationMatrix2D(Point2f(0, 0), angulo, escala);
	M.at<double>(0, 2) = tam.width / 2 + cx * escala;
	M.at<double>(1, 2) = tam.height / 2 + cy * escala;
	warpAffine(imagen, salida, M, tam);
	imshow("Ejercicio 3: rotar", salida);
}

void inclinacion(Mat img, int value)
{
	double inc = tan(value * M_PI / 180.0);
	Mat c = (Mat_<double>(2, 3) << 1, inc, -inc * img.size().height / 2.0, 0, 1, 0);
	warpAffine(img, img, c, img.size());
	imshow("Ejercicio 4: inclinación", img);
}

void afines(Mat img)
{
	Mat pt1(1, 3, CV_32FC2); // Puntos en el origen
	pt1.at<Vec2f>(0, 0) = Vec2f(0, 0); // Rellenar los tres puntos
	pt1.at<Vec2f>(0, 1) = Vec2f(100, 0);
	pt1.at<Vec2f>(0, 2) = Vec2f(100, 100);
	Mat pt2(1, 3, CV_32FC2); // Puntos en el destino
	pt2.at<Vec2f>(0, 0) = Vec2f(10, 20); // Rellenar los tres puntos
	pt2.at<Vec2f>(0, 1) = Vec2f(80, 40);
	pt2.at<Vec2f>(0, 2) = Vec2f(20, 70);
	Mat c = getAffineTransform(pt1, pt2);
	warpAffine(img, img, c, img.size());
	imshow("Ejercicio 5: tranformacion afín", img);
}


int main()
{
	Mat image = imread("1.jpg", 1);
	Mat image1 = imread("1.jpg", 1);
	Mat image2 = imread("1.jpg", 1);
	Mat image3 = imread("1.jpg", 1);
	Mat image4 = imread("1.jpg", 1);
	imshow("imagen original", image);
	Rotar(image, image, 75, 1);
	zoom(image1);
	//espejo(image2, 1);
	espejo(image2, 0);
	inclinacion(image3, 50);
	afines(image4);

	waitKey(0);
	return 0;
}

