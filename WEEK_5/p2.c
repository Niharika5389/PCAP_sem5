#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, M;
    int *a = NULL;
    int *local = NULL;
    double local_avg, total_avg;
    double *avgs = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        scanf("%d", &M);
        a = malloc(size * M * sizeof(int));

        for(int i = 0; i < size * M; i++)
            scanf("%d", &a[i]);

        avgs = malloc(size * sizeof(double));
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local = malloc(M * sizeof(int));

    MPI_Scatter(a, M, MPI_INT, local, M, MPI_INT, 0, MPI_COMM_WORLD);

    double sum = 0;

    for(int i = 0; i < M; i++)
        sum += local[i];

    local_avg = sum / M;

    MPI_Gather(&local_avg, 1, MPI_DOUBLE,
               avgs, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        total_avg = 0;

        for(int i = 0; i < size; i++)
            total_avg += avgs[i];

        total_avg /= size;

        printf("%.2f\n", total_avg);

        free(a);
        free(avgs);
    }

    free(local);

    MPI_Finalize();
    return 0;
}

