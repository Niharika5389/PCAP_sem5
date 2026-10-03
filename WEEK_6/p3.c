#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int a[4][4];
    int row[4];
    int result[4][4];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4)
    {
        if (rank == 0)
            printf("Run with 4 processes\n");

        MPI_Finalize();
        return 1;
    }

    if (rank == 0)
    {
        printf("Enter 4 X 4 matrix:\n");

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &a[i][j]);
    }

    MPI_Scatter(a, 4, MPI_INT, row, 4, MPI_INT,
                0, MPI_COMM_WORLD);

    MPI_Scan(row, result[rank], 4, MPI_INT,
             MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0)
    {
        MPI_Gather(MPI_IN_PLACE, 0, MPI_INT,
                   result, 4, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Gather(result[rank], 4, MPI_INT,
                   result, 4, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        printf("O/p matrix:\n");

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d ", result[i][j]);

            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}

