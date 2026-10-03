#include <stdio.h>
#include <cuda_runtime.h>

__global__ void add(float *a, float *b, float *c) {
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

__global__ void dot(float *a, float *b, float *r) {
    int i = threadIdx.x;
    r[i] = a[i] * b[i];
}

int main() {
    int N = 10;
    float a[10], b[10], c[10], r[10];
    float *da, *db, *dc, *dr;

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    cudaMalloc(&da, N*sizeof(float));
    cudaMalloc(&db, N*sizeof(float));
    cudaMalloc(&dc, N*sizeof(float));
    cudaMalloc(&dr, N*sizeof(float));

    cudaMemcpy(da,a,N*sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(db,b,N*sizeof(float),cudaMemcpyHostToDevice);

    add<<<1,N>>>(da,db,dc);
    dot<<<1,N>>>(da,db,dr);

    cudaMemcpy(c,dc,N*sizeof(float),cudaMemcpyDeviceToHost);
    cudaMemcpy(r,dr,N*sizeof(float),cudaMemcpyDeviceToHost);
	
    printf("a   b    Add       Dot    \n");
    for(int i=0;i<N;i++){
    	a[i] = i;
        b[i] = i * 2;
        printf("%.2f  %.2f  %.2f  %.2f \n",a[i],b[i],c[i],r[i]);
     }

    cudaFree(da); cudaFree(db); cudaFree(dc); cudaFree(dr);
    return 0;
}

