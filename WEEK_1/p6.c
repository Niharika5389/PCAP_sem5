#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    int arr[N];
    long long serial_sum = 0, parallel_sum = 0;
    double start, end;
    int i;

    for (i = 0; i < N; i++) {
        arr[i] = 1;     
    }

    start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        serial_sum += arr[i];
    }

    end = omp_get_wtime();
    printf("Serial Sum = %lld\n", serial_sum);
    printf("Serial Execution Time = %f seconds\n", end - start);

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:parallel_sum)
    for (i = 0; i < N; i++) {
        parallel_sum += arr[i];
    }

    end = omp_get_wtime();
    printf("Parallel Sum = %lld\n", parallel_sum);
    printf("Parallel Execution Time = %f seconds\n", end - start);

    return 0;
}

