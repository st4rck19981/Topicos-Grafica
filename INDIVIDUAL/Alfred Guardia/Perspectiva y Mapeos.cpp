#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void mapeado(int m)
{
	Mat img = imread("ZERO.jpg", IMREAD_COLOR);
	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y=0; y<img.size().height; y++)
	{
		for (int x=0; x<img.size().width; x++)
		{
			mapa1.at<float>(y,x) = x+rand()%(2*m+1)-m; 
			mapa2.at<float>(y,x) = y+rand()%(2*m+1)-m; 
		}
	}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("MAPEADO", resultado);
	waitKey(0);
}

void acristalado(int n)
{
	Mat img = imread("ZERO.jpg", IMREAD_COLOR);
	Mat mapa1(img.size(), CV_32FC1);
	Mat mapa2(img.size(), CV_32FC1);
	for (int y = 0; y < img.size().height; y++)
	{
		for (int x = 0; x < img.size().width; x++)
		{
			mapa1.at<float>(y, x) = x - x % n + y % n;
			mapa2.at<float>(y, x) = y - y % n + x % n;
		}
	}
	Mat resultado;
	remap(img, resultado, mapa1, mapa2, INTER_NEAREST);
	imshow("ACRISTALADO", resultado);
	waitKey(0);
}

void perspectiva()
{
	Mat img = imread("ZERO.jpg", IMREAD_COLOR);
	double w = img.size().width, h = img.size().height;
	Mat pt1(1, 4, CV_32FC2);
	pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
	pt1.at<Vec2f>(0, 1) = Vec2f(w, 0);
	pt1.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt1.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat pt2(1, 4, CV_32FC2);
	pt2.at<Vec2f>(0, 0) = Vec2f(w * 0.3, 0);
	pt2.at<Vec2f>(0, 1) = Vec2f(w * 0.7, 0);
	pt2.at<Vec2f>(0, 2) = Vec2f(w, h);
	pt2.at<Vec2f>(0, 3) = Vec2f(0, h);
	Mat persp = getPerspectiveTransform(pt1, pt2);
	Mat resultado;
	warpPerspective(img, resultado, persp, img.size());
	imshow("PERSPECTIVA", resultado);
	waitKey(0);
}

int main()
{
	int m=10;			//VALOR PARA MAPEADO
	int n=20;			//VALOR PARA ACRISTALADO
	//mapeado(m);
	//perspectiva();
	//acristalado(n);
	return 0;
}