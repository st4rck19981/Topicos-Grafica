# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc.hpp>
# include <iostream>
using namespace cv;
using namespace std;

int  main (){
	Mat img = imread ("image.jpg",1);
	imshow("Original",img);
	Mat gris, hist;
	cvtColor(img, gris, COLOR_RGB2GRAY);
	int canales[1]={0}, bins[1]={256};
	float rango[2]={0,256};
	const  float *rangos[]={rango};
	calcHist(&gris,1,canales,noArray(),hist,1,bins,rangos);
	hist*=255.0/norma(hist, NORM_L1);
	Mat lut(1,256,CV_8UC1);
	float acum=0.0;
	for(int i=0;i<256;i++) {
		lut.at<uchar>(0,i)=acum;
		acum+=hist.at<float>(i);
	}
	Mat res;
	LUT(img, lut, res);
	imshow ("Ecualizacion",res);
	waitKey(0);
}