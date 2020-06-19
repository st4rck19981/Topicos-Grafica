/*
PASOS PARA CREAR TU PROYECTO C++ / OPENCV / CUDA
1. Crear nuevo proyecto vacio de CUDA
2. Abra solo un archivo llamado "kernel.cu"
3. Agregas el main.cpp
Sigues los pasos de este link:
https://www.youtube.com/watch?v=EbPsLwhtu54
*/
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Funciones.h"

#define Mask_size 3
#define TILE_SIZE 32
#define BLOCK_SIZE 32

using namespace std;
using namespace cv;

int main() {
    int Mask_Width = Mask_size;

    Mat image;
    image = imread("image.jpg", 0);
    Size s = image.size();
    int Row = s.width;
    int Col = s.height;

    //Mascaras
    char h_Mask[] = { -1,0,1,-2,0,2,-1,0,1 }; // kernel para la deteccion de bordes.
    //char h_Mask[] = { 1,1,1,1,1,1,1,1,1 };  //Para hacerlo borroso, solo que en el kernel, hay q dividir la suma entre 9 o sale muy brilloso
    char h_Mask1[] = { -1,-2,-1,0,0,0,1,2,1 }; //si se quiere usar este filtro en el eje y.


    if (!image.data)
    {//Prueba de carga de la imagen apropiadamente
        cout << "Problems loading the image" << endl;
        return -1;
    }

    //Reservando memoria en host
    unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);
    unsigned char* imgOut = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);

    img = image.data;

    callKernel2D(img, imgOut, h_Mask, Mask_Width, Row, Col);

    //Imprimiendo la imagen de salida
    Mat gray_image;
    gray_image.create(Col, Row, CV_8UC1);
    gray_image.data = imgOut;

    namedWindow("image", WINDOW_NORMAL);
    imshow("Original", image);
    imshow("Convolucion", gray_image);
    waitKey(0);

    imwrite("salida.png", gray_image);

	return 0;
}