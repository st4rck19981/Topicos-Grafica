
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat leftCircle = Mat(500, 1000, CV_8UC1);

	Mat rightCircle = Mat(500, 1000, CV_8UC1);
	leftCircle.setTo(0);
	rightCircle.setTo(0);

	circle(leftCircle, Point(1000 / 5 * 2, 500 / 2), 250, CV_RGB(255, 255, 255), FILLED);
	circle(rightCircle, Point(1000 / 5 * 3, 500 / 2), 250, CV_RGB(255, 255, 255), FILLED);

	//and, or, xor, not 테스트
	Mat res;
	bitwise_and(leftCircle, rightCircle, res);     imshow("AND", res);
	bitwise_or(leftCircle, rightCircle, res);      imshow("OR", res);
	bitwise_xor(leftCircle, rightCircle, res);     imshow("XOR", res);
	bitwise_not(leftCircle, res);                    imshow("NOT", res);

	imshow("leftCircle", leftCircle);
	imshow("rightCircle", rightCircle);

	waitKey(0);
}