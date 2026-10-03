#include <stdio.h>
#define MAX 100

__global__ void convolution(int *N, int *M, int *P, int width, int mw) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < width) {
        int sum = 0;
        for (int j = 0; j < mw; j++) {
            int k = i + j - mw / 2;
            if (k >= 0 && k < width)
                sum += N[k] * M[j];
        }
        P[i] = sum;
    }
}

int main() {
    int N[MAX], M[MAX], P[MAX], width, mw;
    int *dN, *dM, *dP;
	printf("Array width and mask width\n");
    scanf("%d%d", &width, &mw);
    printf("Array elements:");
    for (int i = 0; i < width; i++) scanf("%d", &N[i]);
    printf("Mask elements:");
    for (int i = 0; i < mw; i++) scanf("%d", &M[i]);

    cudaMalloc(&dN, width*sizeof(int));
    cudaMalloc(&dM, mw*sizeof(int));
    cudaMalloc(&dP, width*sizeof(int));

    cudaMemcpy(dN,N,width*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(dM,M,mw*sizeof(int),cudaMemcpyHostToDevice);

    convolution<<<(width+255)/256,256>>>(dN,dM,dP,width,mw);

    cudaMemcpy(P,dP,width*sizeof(int),cudaMemcpyDeviceToHost);

    for (int i = 0; i < width; i++) printf("%d ",P[i]);

    cudaFree(dN); cudaFree(dM); cudaFree(dP);
}

