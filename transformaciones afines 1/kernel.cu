
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "Funciones.h"
using namespace std;


#define Mask_size 3
#define TILE_SIZE 32
#define BLOCK_SIZE 32

__global__ void gpu_matrix_mult(int* a, int* b, int* c, int m, int n, int k)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int sum = 0;
    if (col < k && row < m)
    {
        for (int i = 0; i < n; i++)
        {
            sum += a[row * n + i] * b[i * k + col];
        }
        c[row * k + col] = sum;
    }
}

void llamadakernel(int matriz[2][3], int matrix2[3][1], int matrixresult[2][1])
{
    int* dev_a;
    int* dev_b;
    int* dev_c;
    int size_a = 2 * 3 * sizeof(int);
    int size_b = 3 * 1 * sizeof(int);
    int size_c = 2 * 1 * sizeof(int);

    cudaMalloc((void**)&dev_a, size_a);
    cudaMalloc((void**)&dev_b, size_b);
    cudaMalloc((void**)&dev_c, size_c);

    cudaMemcpy(dev_a, matriz, size_a, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, matrix2, size_b, cudaMemcpyHostToDevice);

    int numbloques = 1;
    int tambloque = 2;

    gpu_matrix_mult << <numbloques, tambloque >> > (dev_a, dev_b, dev_c, 2, 3, 1);

    cudaDeviceSynchronize();
    cudaMemcpy(matrixresult, dev_c, sizeof(int) * size_c, cudaMemcpyDeviceToHost);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);


}
