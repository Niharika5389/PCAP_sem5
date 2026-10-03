#include <stdio.h>
#include <omp.h>

#define M 2
#define N 2

int main() {
    int a[M][N], c[M][N];
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

        int max = a[i][0];
        int min = a[i][0];
        for (j = 1; j < N; j++) {
            if (a[i][j] > max)
                max = a[i][j];
            if (a[i][j] < min)
                min = a[i][j];
        }

        for (j = 0; j < N; j++) {
            if (i == j)
                c[i][j] = 0;
            else if (i > j)
                c[i][j] = max;
            else
                c[i][j] = min;
        }

        printf("Thread %d computed row %d\n", omp_get_thread_num(), i);
    }

    printf("\nResult Matrix C:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}

