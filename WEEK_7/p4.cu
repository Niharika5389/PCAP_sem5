#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>

__global__ void sine(float *a, float *b, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
        b[i] = sinf(a[i]);
}

int main() {
    int N = 10;
    float a[10], b[10];
    float *da,*db;

    for(int i=0;i<N;i++)
        a[i] = i * 0.5f;

    cudaMalloc(&da,N*sizeof(float));
    cudaMalloc(&db,N*sizeof(float));

    cudaMemcpy(da,a,N*sizeof(float),cudaMemcpyHostToDevice);

    sine<<<(N+255)/256,256>>>(da,db,N);

    cudaMemcpy(b,db,N*sizeof(float),cudaMemcpyDeviceToHost);

    for(int i=0;i<N;i++)
        printf("%f -> %f\n",a[i],b[i]);

    cudaFree(da);
    cudaFree(db);
    return 0;
}

