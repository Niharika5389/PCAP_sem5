#include <stdio.h>
#include <omp.h>

#define N 1000000

int A[N], B[N];
int add[N], sub[N], mul[N];

int main() {

    double start, end;
    double parallel_time, serial_time;
    int i;

    for(i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    start = omp_get_wtime();

    for(i = 0; i < N; i++)
        add[i] = A[i] + B[i];

    for(i = 0; i < N; i++)
        sub[i] = A[i] - B[i];

    for(i = 0; i < N; i++)
        mul[i] = A[i] * B[i];

    end = omp_get_wtime();

    serial_time = end - start;

    printf("Serial Execution Time = %f seconds\n", serial_time);


    start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Addition executed by thread %d\n",
                   omp_get_thread_num());

            for(i = 0; i < N; i++)
                add[i] = A[i] + B[i];
        }


        #pragma omp section
        {
            printf("Subtraction executed by thread %d\n",
                   omp_get_thread_num());

            for(i = 0; i < N; i++)
                sub[i] = A[i] - B[i];
        }


        #pragma omp section
        {
            printf("Multiplication executed by thread %d\n",
                   omp_get_thread_num());

            for(i = 0; i < N; i++)
                mul[i] = A[i] * B[i];
        }
    }

    end = omp_get_wtime();

    parallel_time = end - start;

    printf("\nParallel Execution Time = %f seconds\n", parallel_time);


    printf("Speedup = %f\n", serial_time / parallel_time);

    printf("Efficiency = %f\n",
           (serial_time / parallel_time) / 3.0);

    return 0;
}
