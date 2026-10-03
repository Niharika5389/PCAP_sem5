#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int A[N][N], x[N], y[N];
    int i, j;
    double start, end;

    for(i = 0; i < N; i++) {
        x[i] = 1;
        for(j = 0; j < N; j++) {
            A[i][j] = 1;
        }
    }

    start = omp_get_wtime();

    #pragma omp parallel for private(j)
    for(i = 0; i < N; i++) {
        y[i] = 0;

        for(j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    end = omp_get_wtime();

    printf("\nExecution Time for matrix size %d = %f seconds\n",N, end - start);

    return 0;
}

