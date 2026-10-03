#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void distance(float *a, float *b, float *c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
        c[i] = (a[i]-b[i])*(a[i]-b[i]);
}

int main() {
    int N = 1000;
    float *a,*b,*c,*d;
    float sum=0;

    a=malloc(N*sizeof(float));
    b=malloc(N*sizeof(float));
    c=malloc(N*sizeof(float));

    for(int i=0;i<N;i++) {
        a[i]=(float)rand()/RAND_MAX;
        b[i]=(float)rand()/RAND_MAX;
    }

    cudaMalloc(&d,N*sizeof(float));
    float *da,*db;
    cudaMalloc(&da,N*sizeof(float));
    cudaMalloc(&db,N*sizeof(float));

    cudaMemcpy(da,a,N*sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(db,b,N*sizeof(float),cudaMemcpyHostToDevice);

    distance<<<(N+255)/256,256>>>(da,db,d);
    cudaMemcpy(c,d,N*sizeof(float),cudaMemcpyDeviceToHost);

    for(int i=0;i<N;i++) sum+=c[i];

    printf("Euclidean Distance = %f\n",sqrt(sum));

    cudaFree(da); cudaFree(db); cudaFree(d);
    free(a); free(b); free(c);
    return 0;
}

