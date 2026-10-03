#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int a[4][4];
    int row[4];
    int result[4][4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Enter 4 X 4 matrix:\n");

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &a[i][j]);
    }

    MPI_Scatter(a, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int j = 0; j < 4; j++)
            result[0][j] = row[j];
    }
    else
    {
        int prev[4];

        MPI_Recv(prev, 4, MPI_INT, rank - 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int j = 0; j < 4; j++)
            result[rank][j] = prev[j] + row[j];

        MPI_Send(result[rank], 4, MPI_INT, rank + 1, 0,
                 MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        MPI_Send(result[0], 4, MPI_INT, 1, 0, MPI_COMM_WORLD);

        for (int i = 1; i < 4; i++)
            MPI_Recv(result[i], 4, MPI_INT, i, 1,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

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

