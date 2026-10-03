#include <stdio.h>
#define MAX 100

__global__ void rankSort(int *a, int *b, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n) {
        int rank=0;
        for(int j=0;j<n;j++)
            if(a[j]<a[i] || (a[j]==a[i] && j<i))
                rank++;
        b[rank]=a[i];
    }
}

int main() {
    int a[MAX], b[MAX], n, *da, *db;
    printf("size: ");
    scanf("%d",&n);
    printf("elements: ");
    for(int i=0;i<n;i++) scanf("%d",&a[i]);

    cudaMalloc(&da,n*sizeof(int));
    cudaMalloc(&db,n*sizeof(int));

    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);

    rankSort<<<(n+255)/256,256>>>(da,db,n);

    cudaMemcpy(b,db,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++) printf("%d ",b[i]);

    cudaFree(da); cudaFree(db);
}

