//https://fisica.cab.cnea.gov.ar/gpgpu/images/charlas/partec%20-%20programacinbasicoii.pdf

#include <cuda_runtime.h>
#include <iostream>
using namespace std;

__global__ void SumaColMatrizKernel(int M, float* Md, float* Nd) {
	__shared__ float Nds[512];
	float Pvalue = 0;
	int aux = blockIdx.y * M + threadIdx.x * (M / blockDim.x);
	int aux2 = aux + (M / blockDim.x);
	for (int k = aux; k < aux2; ++k) {
		Pvalue = Pvalue + Md[k];
	}
	Nds[threadIdx.x] = Pvalue;
	__syncthreads();

	if (threadIdx.x == 0) {
		for (int i = 1; i < blockDim.x; ++i) {
			Nds[0] = Nds[0] + Nds[i];
		}
		Nd[blockIdx.y] = Nds[0];
	}
}


int main() {
	int f = 1024, c = 512;

	int size = f * c * sizeof(float);
	int size2 = c * sizeof(float);

	float* Mh = (float*)malloc(size);
	float* Nh = (float*)malloc(size2);

	for (int i = 0; i < f * c; i++)    Mh[i] = 1.0;

	float* Md, * Nd;
	cudaMalloc(&Md, size);
	cudaMalloc(&Nd, size2);

	cudaMemcpy(Md, Mh, size, cudaMemcpyHostToDevice);
	cudaMemset(Nd, 0, size2);

	int M = f;
	int N = c;

	int chunk = 32;
	dim3 tamGrid(1, N);
	dim3 tamBlock(M / chunk, 1, 1);

	SumaColMatrizKernel << <tamGrid, tamBlock >> > (M, Md, Nd);
	cudaMemcpy(Nh, Nd, size2, cudaMemcpyDeviceToHost);

	cudaFree(Md);
	cudaFree(Nd);

	cout << "\nResultados: " << endl;
	for (int i = 0; i < c; i++) {
		cout << Nh[i] << " ";
	}

	return 0;
}