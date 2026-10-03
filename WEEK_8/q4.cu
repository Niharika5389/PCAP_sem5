#include <stdio.h>
#include <string.h>
#define MAX 1000

__global__ void countWord(char *s, char *w, int *count, int n, int m) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i <= n-m) {
        int j;

        for(j=0;j<m;j++)
            if(s[i+j]!=w[j])
                break;

        if(j==m && (i==0 || s[i-1]==' ') &&
           (i+m==n || s[i+m]==' ' || s[i+m]=='\n'))
            atomicAdd(count,1);
    }
}

int main() {
    char s[MAX], w[MAX];
    char *ds,*dw;
    int *count, h=0;

    printf("enter string: ");
    fgets(s,MAX,stdin);

    printf("enter word: ");
    scanf("%s",w);

    int n=strlen(s);
    int m=strlen(w);

    cudaMalloc(&ds,n);
    cudaMalloc(&dw,m);
    cudaMalloc(&count,sizeof(int));

    cudaMemcpy(ds,s,n,cudaMemcpyHostToDevice);
    cudaMemcpy(dw,w,m,cudaMemcpyHostToDevice);
    cudaMemcpy(count,&h,sizeof(int),cudaMemcpyHostToDevice);

    countWord<<<(n+255)/256,256>>>(ds,dw,count,n,m);

    cudaMemcpy(&h,count,sizeof(int),cudaMemcpyDeviceToHost);

    printf("Count = %d\n",h);

    cudaFree(ds);
    cudaFree(dw);
    cudaFree(count);

    return 0;
}

