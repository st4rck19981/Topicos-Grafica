
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Funciones.h"

#define Mask_size 3
#define TILE_SIZE 32
#define BLOCK_SIZE 32

using namespace std;
using namespace cv;

void matmult(int A[2][3], int B[3][1], int C[2][1], int f, int c)
{
    for (int a = 0; a < c; a++) {
        // Dentro recorremos las filas de la primera (A)
        for (int i = 0; i < f; i++) {
            int suma = 0;
            // Y cada columna de la primera (A)
            for (int j = 0; j < 3; j++) {
                // Multiplicamos y sumamos resultado
                suma += A[i][j] * B[j][a];
            }
            // Lo acomodamos dentro del producto
            C[i][a] = suma;
        }
    }
}



int main()
{
    Mat img;
    img = imread("image.jpg");
    Size s = img.size();
    int Row = s.width;
    int Col = s.height;
    Mat_<Vec2f> prjMap(img.size());
    int matriz[2][3] = { {1,0,0},{0,1,0}};
    int matrix2[3][1] = { {0},{0},{1}};
    int matrixresult[2][1];

    llamadakernel(matriz, matrix2, matrixresult);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 1; j++)
            cout << matrixresult[i][j];



    for (int x = 0; x < img.cols; x++) {
        for (int y = 0; y < img.rows; y++) {
            matrix2[0][0] = x;
            matrix2[1][0] = y;
            matrix2[2][0] = 1;
            matmult(matriz, matrix2, matrixresult, 2, 1);
            float u = matrixresult[0][0];
            float v = matrixresult[1][0];
            prjMap(y, x) = Vec2f(u, v);
        }
    }
    Mat projected;
    remap(img, projected, prjMap, cv::Mat(), INTER_LINEAR);
    namedWindow("final", WINDOW_AUTOSIZE);
    imshow("final", projected);

    //unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);
    //unsigned char* imgOut = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);

    waitKey(0);
    return 0;
}