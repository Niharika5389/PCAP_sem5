#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SEQUENTIAL_CUTOFF 1000

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_sequential(int arr[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_sequential(arr, left, mid);
    merge_sort_sequential(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void merge_sort_parallel(int arr[], int left, int right, int depth)
{
    if (left >= right)
        return;

    if (right - left + 1 <= SEQUENTIAL_CUTOFF)
    {
        merge_sort_sequential(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    #pragma omp task shared(arr) if(depth < 4)
    {
        merge_sort_parallel(arr, left, mid, depth + 1);
    }

    #pragma omp task shared(arr) if(depth < 4)
    {
        merge_sort_parallel(arr, mid + 1, right, depth + 1);
    }

    #pragma omp taskwait

    merge(arr, left, mid, right);
}

void parallel_sort(int arr[], int n)
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            merge_sort_parallel(arr, 0, n - 1, 0);
        }
    }
}

void generate_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand();
}

int verify_sorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
            return 0;
    }

    return 1;
}

int main()
{
    int sizes[] = {
        10000,
        50000,
        100000,
        500000,
        1000000
    };

    int thread_counts[] = {1, 2, 4, 8};

    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_thread_counts =
        sizeof(thread_counts) / sizeof(thread_counts[0]);

    printf("Parallel Merge Sort Performance\n");

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        int *original = malloc(n * sizeof(int));
        int *seq_array = malloc(n * sizeof(int));
        int *par_array = malloc(n * sizeof(int));

        if (original == NULL ||
            seq_array == NULL ||
            par_array == NULL)
        {
            printf("Memory allocation failed for N = %d\n", n);
            return 1;
        }

        srand(42);
        generate_array(original, n);

        /*
         * Sequential execution
         */
        for (int i = 0; i < n; i++)
            seq_array[i] = original[i];

        double start = omp_get_wtime();

        merge_sort_sequential(seq_array, 0, n - 1);

        double end = omp_get_wtime();

        double sequential_time = end - start;

        printf("\nN = %d\n", n);
        printf("Sequential time = %.6f seconds\n",
               sequential_time);

        if (!verify_sorted(seq_array, n))
            printf("Sequential sorting ERROR!\n");

        printf("\nThreads\tParallel Time\tSpeedup\tEfficiency\n");

        /*
         * Parallel execution for different thread counts
         */
        for (int t = 0; t < num_thread_counts; t++)
        {
            int threads = thread_counts[t];

            for (int i = 0; i < n; i++)
                par_array[i] = original[i];

            omp_set_num_threads(threads);

            start = omp_get_wtime();

            parallel_sort(par_array, n);

            end = omp_get_wtime();

            double parallel_time = end - start;

            double speedup =
                sequential_time / parallel_time;

            double efficiency =
                speedup / threads;

            printf("%d\t%.6f\t%.4f\t%.4f\n",
                   threads,
                   parallel_time,
                   speedup,
                   efficiency);

            if (!verify_sorted(par_array, n))
                printf("Parallel sorting ERROR!\n");
        }

        free(original);
        free(seq_array);
        free(par_array);
    }

    return 0;
}

