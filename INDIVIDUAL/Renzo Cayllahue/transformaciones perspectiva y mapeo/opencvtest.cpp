
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*
//ejercicio 1: transformar imagen perspectiva
int main()
{
	Mat img = imread("a.jpg", IMREAD_COLOR);
	double w = img.size().width, h = img.size().height;
	Mat pt1(1, 4, CV_32FC2); // Cuatro puntos en el origen
	pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
	pt1.at<Vec2f>(0, 1) = Vec2f(w, 0);
	pt1.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt1.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat pt2(1, 4, CV_32FC2); // Cuatro puntos en el destino
	pt2.at<Vec2f>(0, 0) = Vec2f(w * 0.3, 0);
	pt2.at<Vec2f>(0, 1) = Vec2f(w * 0.7, 0);
	pt2.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt2.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat c = getPerspectiveTransform(pt1, pt2);
	Mat resultado;
	warpPerspective(img, resultado, c, img.size());
	imshow("Display Window", resultado);
	waitKey(0);
	return 0;
}
*/

//ejercicio2: trasnformacion aleatoria de una imagen con un m


/*
#define m 20
int main()
{
	Mat img = imread("a.jpg", IMREAD_COLOR);
	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y = 0; y < img.size().height; y++)
		for (int x = 0; x < img.size().width; x++) {
			mapa1.at<float>(y, x) = x + rand() % (2 * m + 1) - m; // Mapa 1
			mapa2.at<float>(y, x) = y + rand() % (2 * m + 1) - m; // Mapa2
		}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("Display Window", resultado);
	waitKey(0);
	return 0;
}
*/

//Ejercicio 3: acristalado
#define m 50
int main()
{
	Mat img = imread("a.jpg", IMREAD_COLOR);
	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y = 0; y < img.size().height; y++)
		for (int x = 0; x < img.size().width; x++) {
			mapa1.at<float>(y, x) = x - x % m + y % m;
			mapa2.at<float>(y, x) = y - y % m + x % m;
		}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("Display Window", resultado);
	waitKey(0);
	return 0;
}