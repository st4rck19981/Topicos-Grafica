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
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <opencv2/opencv.hpp>
#include "Funciones.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat FiltrosyConvoluciones();
Mat imageZOOM(Mat image);
Mat imageEspejo(Mat image);
void Rotar(Mat imagen, Mat& salida);
Mat TransAFIN(Mat image);
Mat Perspectiva(Mat image);
Mat deformacion(Mat image);
Mat acristalado(Mat image);
Mat ecualizacion(Mat image);
void mostrar(Mat image);

int main() {
    int op = 100;
    int resultado;
    Mat image,salida;
    image = imread("image.jpg");
    imwrite("image.png", image);
    
    //Imprimiendo la imagen de salida

    while (op != 0) {
        system("cls");
        cout << " *** Una Interfaz Sencilla para modificar Imagenes ***" << endl;
        cout << "NOTA:" << endl;
        cout << "Se cargara el archivo image.jpg como la imagen original." << endl;
        cout << "La imagen resultado se guardara con el nombre salida.png" << endl;
        cout << "Las imagenes se trabajaran en formato .png" << endl;
        cout << "Al mostrar una imagen, presiona ENTER para continuar y digita la opcion" << endl;
        cout << "\nOpciones" << endl;
        cout << "10 - Filtros y Convoluciones." << endl;
        cout << "11 - ZOOM 2X." << endl;
        cout << "12 - Espejo." << endl;
        cout << "13 - Escala y Rotacion." << endl;
        cout << "14 - Transformacion AFIN." << endl;
        cout << "21 - Cambiar Perspectiva." << endl;
        cout << "22 - Transformacion Aleatoria con un radio de deformacion." << endl;
        cout << "23 - Transformacion Acristalado." << endl;
        cout << "24 - Ecualizacion de Histograma." << endl;

        cout << "\n1 - Imagen Original" << endl;
        cout << "2 - Imagen Resultado" << endl;
        cout << "3 - Guardar Imagen Resultado" << endl;
        cout << "4 - Reemplazar la imagen original por la salida" << endl;
        cout << "0 - Salir" << endl;
        cout << "\nElija Opcion: ";     cin >> op;

        switch (op) {
        case 0:
            system("cls");
            if (salida.data != NULL) {
                cout << "Imagen de salida guardada correctamente" << endl;
                imwrite("salida.png", salida);
            }
            else
                cout << "No se hizo ningun cambio a la imagen." << endl;
            system("pause");
            break;
        case 1:
            mostrar(image);
            break;
        case 2:
            mostrar(salida);
            break;
        case 3:
            system("cls");
            resultado=imwrite("salida.png", salida);
            if (resultado == 1)
                cout << "Imagen guardada correctamente. " << endl;
            else
                cout << "No se pudo guardar la imagen" << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            resultado=imwrite("image.png", salida);
            if (resultado == 1) {
                cout << "Se reemplazo la imagen original correctamente. " << endl;
                image = imread("image.png");
            }
            else
                cout << "No se pudo reemplazar la imagen" << endl;
            system("pause");
            break;
        case 10:
            salida = FiltrosyConvoluciones();
            mostrar(salida);
            break;
        case 11:
            salida = imageZOOM(image);
            mostrar(salida);
            break;
        case 12:
            salida = imageEspejo(image);
            mostrar(salida);
            break;
        case 13:
            Rotar(image,salida);
            mostrar(salida);
            break;
        case 14:
            salida = TransAFIN(image);
            mostrar(salida);
            break;
        case 21:
            salida = Perspectiva(image);
            mostrar(salida);
            break;
        case 22:
            salida = deformacion(image);
            mostrar(salida);
            break;
        case 23:
            salida = acristalado(image);
            mostrar(salida);
            break;
        case 24:
            salida = ecualizacion(image);
            mostrar(salida);
            break;
        }


        system("cls");


    }

	return 0;
}

void mostrar(Mat image) {
    if (image.data != NULL) {
        namedWindow("Ventana", WINDOW_NORMAL);
        imshow("Imagen", image);
        waitKey(0);
        destroyAllWindows();
    }
    else {
        cout << "No existe la imagen." << endl;
        system("pause");
    }
}

Mat imageZOOM(Mat image) {
    system("cls");
    int x, y;
    cout << "ZOOM en X:";    cin >> x;
    cout << "ZOOM en Y:";    cin >> y;
    Mat salida;
    resize(image, salida, Size(), x, y);
    return salida;
}

void Rotar(Mat imagen, Mat& salida) {
    double angulo,escala;
    system("cls");
    cout << "Escriba angulo de rotacion: ";    cin >> angulo;
    cout << "Escriba nueva escala de imagen o 1.0: ";    cin >> escala;
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

Mat imageEspejo(Mat image) {
    system("cls");
    Mat salida;
    flip(image, salida, -1);
    return salida;
}

Mat TransAFIN(Mat image) {
    Mat salida;
    Mat pt1(1, 3, CV_32FC2);
    pt1.at<Vec2f>(0, 0) = Vec2f(0, 0);
    pt1.at<Vec2f>(0, 1) = Vec2f(100, 0);
    pt1.at<Vec2f>(0, 2) = Vec2f(100, 100);
    Mat pt2(1, 3, CV_32FC2);
    pt2.at<Vec2f>(0, 0) = Vec2f(10, 20);
    pt2.at<Vec2f>(0, 1) = Vec2f(80, 40);
    pt2.at<Vec2f>(0, 2) = Vec2f(20, 70);
    Mat c = getAffineTransform(pt1, pt2);
    warpAffine(image, salida, c, image.size());
    return salida;
}

Mat Perspectiva(Mat image) {
    Mat salida;
    double w = image.size().width, h = image.size().height;
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
    Mat c = getPerspectiveTransform(pt1, pt2);
    warpPerspective(image, salida, c, image.size());
    return salida;
}

Mat deformacion(Mat image) {
    Mat salida;
    system("cls");
    int m;
    cout << "Numero entero para radio de deformacion: ";    cin >> m;
    Mat mapa1(image.size(), CV_32FC1);
    Mat mapa2(image.size(), CV_32FC1);
    for (int y = 0; y < image.size().height; y++) {
        for (int x = 0; x < image.size().width; x++) {
            mapa1.at<float>(y, x) = x + rand() % (2 * m + 1) - m;
            mapa2.at<float>(y, x) = y + rand() % (2 * m + 1) - m;
        }
    }
    remap(image, salida, mapa1, mapa2, INTER_NEAREST);
    return salida;
}

Mat acristalado(Mat image) {
    Mat salida;
    system("cls");
    int m;
    cout << "Numero entero para radio de deformacion: ";    cin >> m;
    Mat mapa1(image.size(), CV_32FC1);
    Mat mapa2(image.size(), CV_32FC1);
    for (int y = 0; y < image.size().height; y++) {
        for (int x = 0; x < image.size().width; x++) {
            mapa1.at<float>(y, x) = x + rand() % (2 * m + 1) - m;
            mapa2.at<float>(y, x) = y + rand() % (2 * m + 1) - m;
        }
    }
    for (int y = 0; y < image.size().height; y++) {
        for (int x = 0; x < image.size().width; x++) {
            mapa1.at<float>(y, x) = x - x % m + y % m;
            mapa2.at<float>(y, x) = y - y % m + x % m;
        }
    }
    remap(image, salida, mapa1, mapa2, INTER_NEAREST);
    return salida;
}

Mat ecualizacion(Mat image) {
    Mat gris, hist;
    cvtColor(image, gris, COLOR_RGB2GRAY);
    int canales[1] = { 0 }, bins[1] = { 256 };
    float rango[2] = { 0,256 };
    const  float* rangos[] = { rango };
    calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
    hist *= 255.0 / norm(hist, NORM_L1);
    Mat lut(1, 256, CV_8UC1);
    float acum = 0.0;
    for (int i = 0; i < 256; i++) {
        lut.at<uchar>(0, i) = acum;
        acum += hist.at<float>(i);
    }
    Mat res;
    LUT(image, lut, res);
    return res;
}

Mat FiltrosyConvoluciones() {
    Mat image = imread("image.png", 0);
    int Mask_Width = 3;
    Size s = image.size();
    int Row = s.width;
    int Col = s.height;

    //Mascaras
    char h_Mask[] = { -1,0,1,-2,0,2,-1,0,1 }; // kernel para la deteccion de bordes.
    char h_Mask1[] = { 1,1,1,1,1,1,1,1,1 };  //Para hacerlo borroso, solo que en el kernel, hay q dividir la suma entre 9 o sale muy brilloso
    char h_Mask2[] = { -1,-2,-1,0,0,0,1,2,1 }; //si se quiere usar este filtro en el eje y.

    //Reservando memoria en host
    unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);
    unsigned char* imgOut = (unsigned char*)malloc(sizeof(unsigned char) * Row * Col);

    img = image.data;

    int op;
    system("cls");
    cout << "Tenemos 3 filtros diferentes." << endl;
    cout << "1 - Detectar Bordes en X." << endl;
    cout << "2 - Hacer borroso la imagen." << endl;
    cout << "3 - Detectar Bordes en Y." << endl;
    cout << "NOTA: Solo trabaja con imagenes a blanco y negro." << endl;
    cout << "Elije una opcion: ";    cin >> op;

    if (op == 1) {
        callKernel2D(img, imgOut, h_Mask, Mask_Width, Row, Col, false);
    }
    if (op == 2) {
        callKernel2D(img, imgOut, h_Mask1, Mask_Width, Row, Col, true);
    }
    if (op == 3) {
        callKernel2D(img, imgOut, h_Mask2, Mask_Width, Row, Col, false);
    }

    Mat gray_image;
    gray_image.create(Col, Row, CV_8UC1);
    gray_image.data = imgOut;

    return gray_image;
}