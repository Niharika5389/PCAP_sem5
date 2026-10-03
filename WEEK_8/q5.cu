#include <stdio.h>
#include <string.h>
#define MAX 1000

__global__ void replaceVowels(int *s, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i < n) {
        if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'||
           s[i]=='A'||s[i]=='E'||s[i]=='I'||s[i]=='O'||s[i]=='U')
            atomicExch(&s[i], '*');
    }
}

int main() {
    char s[MAX];
    int a[MAX];
    int *d;
    int n;

    printf("Enter string: ");
    fgets(s,MAX,stdin);

    n = strlen(s);

    for(int i=0;i<n;i++)
        a[i] = s[i];

    cudaMalloc(&d,n*sizeof(int));

    cudaMemcpy(d,a,n*sizeof(int),cudaMemcpyHostToDevice);

    replaceVowels<<<(n+255)/256,256>>>(d,n);

    cudaMemcpy(a,d,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%c",(char)a[i]);

    cudaFree(d);

    return 0;
}

