#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int value;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter a number: ");
        scanf("%d", &value);

        value++;
        printf("Process 0: %d\n", value);

        MPI_Send(&value, 1, MPI_INT, 1, 0,
                 MPI_COMM_WORLD);

        MPI_Recv(&value, 1, MPI_INT, size - 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Final value at root = %d\n", value);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        value++;

        printf("Process %d: %d\n", rank, value);

        if (rank == size - 1)
        {
            MPI_Send(&value, 1, MPI_INT, 0, 0,
                     MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0,
                     MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

