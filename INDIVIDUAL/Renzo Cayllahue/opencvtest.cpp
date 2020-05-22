
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat img = imread("arequipa.jpg", 1);
		imshow("Entrada", img);
	Mat gris, hist;
	cvtColor(img, gris, COLOR_RGB2GRAY);     //CAMBIA EN LA VERSION 3 DE OPENCV
	int canales[1] = { 0 }, bins[1] = { 256 };
	float rango[2] = { 0, 256 };
	const float* rangos[] = { rango };
	calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
	hist *= 255.0 / norm(hist, NORM_L1);
	Mat lut(1, 256, CV_8UC1);
	float acum = 0.0;
	for (int i = 0; i < 256; i++) {
		lut.at<uchar>(0, i) = acum;
		acum += hist.at<float>(i);
	}
	Mat res;
	LUT(img, lut, res);
	imshow("Ecualizada", res);
	waitKey(0);
}


//HISTOGRAMA CANALES RG
/*
int main()
{
	Mat img = imread("arequipa.jpg", 1);
	Mat hist;
	imshow("imagen inicial: ", img);
	int canales[2] = { 2, 1 }; // El 2 es el canal R, y el 1 es el canal G
	int bins[2] = { 64, 64 };
	float rango[2] = { 0, 256 };
	const float* rangos[] = { rango, rango };
	calcHist(&img, 1, canales, noArray(), hist, 2, bins, rangos);
	// Operaciones para pintar el histograma
	Mat pinta(64, 64, CV_8UC1);
	double minval, maxval;
	minMaxLoc(hist, &minval, &maxval); // Para escalar el color entre blanco y negro
	for (int r = 0; r < 64; r++)
		for (int g = 0; g < 64; g++)
			pinta.at<uchar>(r, g) = 255 - 255 * hist.at<float>(r, g) / maxval;
	namedWindow("Histograma R-G", 0);
	imshow("Histograma R-G", pinta);
	waitKey(0);
}

*/

//histograma unidimensional
/*
int main() {
	Mat img = imread("arequipa.jpg", 1);
	Mat gris;
	Mat hist;
	cvtColor(img, gris, COLOR_RGB2GRAY); // Conversión a gris
	imshow("Imagen inicial: ", img);
	imshow("Imagen escaa de grises: ", gris);
	int canales[1] = { 0 };
	int bins[1] = { 256 };
	float rango[2] = { 0, 256 };
	const float* rangos[] = { rango };
	int const hist_height = 256;
	Mat3b hist_image = Mat3b::zeros(hist_height, 256);
	cv::calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
	double max_val = 0;
	minMaxLoc(hist, 0, &max_val);
	for (int i = 0; i < 256; i++) {
		printf("Celda %d: %g \n", i, hist.at<float>(i));
		float const binVal = hist.at<float>(i);
		int   const height = cvRound(binVal * hist_height / max_val);
		cv::line
		(hist_image
			, cv::Point(i, hist_height - height), cv::Point(i, hist_height)
			, cv::Scalar::all(255)
		);
	}
	imshow("histograma", hist_image);
	waitKey(0);
}

*/


//trasnformacion gamma
/*
int main()
{
	Mat img;
	img = imread("arequipa.jpg");
	imshow("imagenoriginal: ", img);
	Mat im32F;
	img.convertTo(im32F, CV_32F, 1.0 / 255.0);
	pow(im32F, 5, im32F);
	im32F.convertTo(img, CV_8U, 255);
	imshow("imagen final: ", img);
	waitKey(0);
}	
*/

// transicion de 2 imagenes 
/*
int main()
{
	Mat A, B, res;

	A = imread("arequipa.jpg",1);
	B = imread("puno.jpg",1);
	if (A.empty()) { cout << "Error cargando imagen A" << endl; return EXIT_FAILURE; }
	if (B.empty()) { cout << "Error cargando imagen B" << endl; return EXIT_FAILURE; }
	for (int i = 0; i < 100; i++) {
		addWeighted(A, i / 100.0, B, 1 - i / 100.0, 0, res);
		imshow("Transicion", res);
		waitKey(10);
	}	
	
} 
*/