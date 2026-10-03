#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, i, fact = 1, sum, total;
    int err;

    err = MPI_Init(&argc, &argv);
    if (err != MPI_SUCCESS)
    {
        printf("MPI_Init failed\n");
        return 1;
    }

    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (err != MPI_SUCCESS)
    {
        printf("MPI_Comm_rank failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    err = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (err != MPI_SUCCESS)
    {
        printf("MPI_Comm_size failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0)
        printf("Number of processes = %d\n", size);

    i = rank + 1;

    for (int j = 1; j <= i; j++)
        fact *= j;

    err = MPI_Scan(&fact, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS)
    {
        printf("MPI_Scan failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == size - 1)
        total = sum;

    MPI_Bcast(&total, 1, MPI_INT, size - 1, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Sum = %d\n", total);

    MPI_Finalize();
    return 0;
}

