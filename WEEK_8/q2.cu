#include <stdio.h>
#define MAX 100

__global__ void oddEven(int *a, int n, int phase) {
    int i = 2 * (blockIdx.x * blockDim.x + threadIdx.x) + phase;
    if (i < n-1 && a[i] > a[i+1]) {
        int t=a[i];
        a[i]=a[i+1];
        a[i+1]=t;
    }
}

int main() {
    int a[MAX], n, *d;
    printf("size: ");
    scanf("%d",&n);
    printf("elements: ");
    for(int i=0;i<n;i++) scanf("%d",&a[i]);

    cudaMalloc(&d,n*sizeof(int));
    cudaMemcpy(d,a,n*sizeof(int),cudaMemcpyHostToDevice);

    for(int i=0;i<n;i++) {
        oddEven<<<(n+255)/256,256>>>(d,n,i%2);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(a,d,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++) printf("%d ",a[i]);
    cudaFree(d);
}

