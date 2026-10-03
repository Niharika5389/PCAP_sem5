#include <stdio.h>
#include <omp.h>

#define M 4
#define N 4


int toBinary(int n) {
    int binary = 0, place = 1;

    while (n > 0) {
        binary += (n % 2) * place;
        n /= 2;
        place *= 10;
    }

    return binary;
}

int onesComplement(int n) {
    int bits = 0, temp = n;

    while (temp > 0) {
        bits++;
        temp /= 2;
    }

    int mask = (1 << bits) - 1;
    return (~n) & mask;
}



int main() {
    int a[M][N], c[M][N], d[M][N];
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j + 1;
        }
    }

    printf("Matrix A:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    #pragma omp parallel for private(j)
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (i==0 || i==M-1 || j==0 || j==N-1){
                c[i][j] = a[i][j];
                d[i][j] = a[i][j];
                }
            else{
            	d[i][j] = onesComplement(a[i][j]);
            	c[i][j] = toBinary(d[i][j]);
            	}
        }

    }

    printf("\nResult Matrix C:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

	 printf("\nResult Matrix D:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    return 0;
}

