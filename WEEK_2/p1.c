#include <stdio.h>
#include <omp.h>

#define M 2
#define N 2

int main() {
    int a[M][N], b[M][N], c[M][N], d[M][N];
    double start, end;
    int i, j;


    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i;
            b[i][j] = 2 * i;
        }
    }

    start = omp_get_wtime();

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    end = omp_get_wtime();
    printf("Serial Execution Time = %f seconds\n\n", end - start);


    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            d[i][j] = a[i][j] + b[i][j];
        }
        printf("Thread %d computed row %d\n", omp_get_thread_num(), i);
    }

    end = omp_get_wtime();
    printf("\nParallel Execution Time = %f seconds\n\n", end - start);

    printf("Result Matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    return 0;
}

