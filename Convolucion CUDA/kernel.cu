#include "cuda_runtime.h"
#include "Funciones.h"
#include <iostream>
using namespace std;

#define Mask_size 3
#define TILE_SIZE 32
#define BLOCK_SIZE 32

__device__ unsigned char clamp(int value)//__device__ because it's called by a kernel
{
	if (value < 0)
		value = 0;
	else
		if (value > 255)
			value = 255;
	return  value;
}

__global__ void CUDA(unsigned char* In, char* Mask, unsigned char* Out, int Mask_Width, int Rowimg, int Colimg) {
	unsigned int row = blockIdx.y * blockDim.y + threadIdx.y;
	unsigned int col = blockIdx.x * blockDim.x + threadIdx.x;

	int Pvalue = 0;
	double suma = 0;

	int N_start_point_row = row - (Mask_Width / 2);
	int N_start_point_col = col - (Mask_Width / 2);

	for (int i = 0; i < Mask_Width; i++){
		for (int j = 0; j < Mask_Width; j++){
			if ((N_start_point_col + j >= 0 && N_start_point_col + j < Rowimg)
				&& (N_start_point_row + i >= 0 && N_start_point_row + i < Colimg))			{
				Pvalue += In[(N_start_point_row + i) * Rowimg + (N_start_point_col + j)] * Mask[i * Mask_Width + j];
			}
			else {
				Pvalue = 0;
			}
		}
	}
	suma = Pvalue;
	Out[row * Rowimg + col] = clamp(suma);
}

void callKernel2D(unsigned char* img, unsigned char* imgOut,char* h_Mask,int Mask_Width, int Row, int Col) {
//problemas con mask_size?
	int Size_of_bytes = sizeof(unsigned char) * Row * Col;
	int Mask_size_bytes = sizeof(char) * (Mask_size * Mask_size);
	unsigned char* d_In, * d_Out;
	char* d_Mask;
	float Blocksize = BLOCK_SIZE;

	cudaMalloc((void**)&d_In, Size_of_bytes);
	cudaMalloc((void**)&d_Out, Size_of_bytes);
	cudaMalloc((void**)&d_Mask, Mask_size_bytes);

	cudaMemcpy(d_In, img, Size_of_bytes, cudaMemcpyHostToDevice);
	cudaMemcpy(d_Mask, h_Mask, Mask_size_bytes, cudaMemcpyHostToDevice);

	dim3 dimGrid(ceil(Row / Blocksize), ceil(Col / Blocksize), 1);
	dim3 dimBlock(Blocksize, Blocksize, 1);

	CUDA<< <dimGrid, dimBlock >> > (d_In, d_Mask, d_Out, Mask_Width, Row, Col);

	cudaDeviceSynchronize();
	cudaMemcpy(imgOut, d_Out, Size_of_bytes, cudaMemcpyDeviceToHost);

	cudaFree(d_In);
	cudaFree(d_Out);
	cudaFree(d_Mask);
}