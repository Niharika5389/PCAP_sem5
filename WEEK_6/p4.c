#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int local, received;
    int a[100], result[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter %d elements:\n", size);

        for (int i = 0; i < size; i++)
            scanf("%d", &a[i]);
    }

    MPI_Scatter(a, 1, MPI_INT, &local, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int phase = 0; phase < size; phase++)
    {
        if (phase % 2 == 0)
        {
            if (rank % 2 == 0 && rank + 1 < size)
            {
                MPI_Sendrecv(&local, 1, MPI_INT, rank + 1, 0,
                             &received, 1, MPI_INT, rank + 1, 0,
                             MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (local > received)
                    local = received;
            }
            else if (rank % 2 == 1)
            {
                MPI_Sendrecv(&local, 1, MPI_INT, rank - 1, 0,
                             &received, 1, MPI_INT, rank - 1, 0,
                             MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (local < received)
                    local = received;
            }
        }
        else
        {
            if (rank % 2 == 1 && rank + 1 < size)
            {
                MPI_Sendrecv(&local, 1, MPI_INT, rank + 1, 0,
                             &received, 1, MPI_INT, rank + 1, 0,
                             MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (local > received)
                    local = received;
            }
            else if (rank % 2 == 0 && rank > 0)
            {
                MPI_Sendrecv(&local, 1, MPI_INT, rank - 1, 0,
                             &received, 1, MPI_INT, rank - 1, 0,
                             MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (local < received)
                    local = received;
            }
        }
    }

    MPI_Gather(&local, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Sorted array:\n");

        for (int i = 0; i < size; i++)
            printf("%d ", result[i]);

        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

