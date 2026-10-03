#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

long long fact(int n)
{
    long long f = 1;
    for(int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int main(int argc, char *argv[])
{
    int rank, size, n, value;
    int *a = NULL;
    long long f, sum = 0;
    long long *results = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        n = size;
        a = malloc(n * sizeof(int));
        results = malloc(n * sizeof(long long));

        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);
    }

    MPI_Scatter(a, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    f = fact(value);

    MPI_Gather(&f, 1, MPI_LONG_LONG, results, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i = 0; i < size; i++)
            sum += results[i];

        printf("%lld\n", sum);

        free(a);
        free(results);
    }

    MPI_Finalize();
    return 0;
}

