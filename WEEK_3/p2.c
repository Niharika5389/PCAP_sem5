#include <stdio.h>
#include <omp.h>

#define SIZE 20

int main()
{
    int arr[SIZE];
    int sum = 0;
    int even_count = 0;
    int num_threads = 0;

    #pragma omp parallel
    {
        #pragma omp master
        {
            for (int i = 0; i < SIZE; i++)
            {
                arr[i] = i + 1;
            }

            num_threads = omp_get_num_threads();

            printf("Master thread initialized the array.\n");
            printf("Total number of threads = %d\n", num_threads);
        }

        #pragma omp barrier

        #pragma omp for reduction(+:sum)
        for (int i = 0; i < SIZE; i++)
        {
            sum += arr[i];

            if (arr[i] % 2 == 0)
            {
                #pragma omp atomic
                even_count++;
            }
        }

        int partial_sum = 0;

        #pragma omp for
        for (int i = 0; i < SIZE; i++)
        {
            partial_sum += arr[i];
        }

        #pragma omp critical
        {
            printf("Thread %d processed a partial sum = %d\n",
                   omp_get_thread_num(), partial_sum);
        }

        #pragma omp barrier

        #pragma omp master
        {
            printf("\nFinal sum = %d\n", sum);
            printf("Total even numbers = %d\n", even_count);
        }
    }

    return 0;
}

