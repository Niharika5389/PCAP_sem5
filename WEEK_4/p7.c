#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int *arr;
    int value;
    int buffer[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        int a[100];

        printf("Enter %d elements:\n", size);

        for (int i = 0; i < size; i++)
            scanf("%d", &a[i]);


        MPI_Buffer_attach(buffer, sizeof(buffer));

        for (int i = 1; i < size; i++)
        {
            MPI_Bsend(&a[i], 1, MPI_INT, i, 0,
                      MPI_COMM_WORLD);
        }


        value = a[0];

        if (rank % 2 == 0)
            printf("Process 0: Square = %d\n", value * value);

        MPI_Buffer_detach(buffer, &(int){0});
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank % 2 == 0)
            printf("Process %d: Square = %d\n",
                   rank, value * value);
        else
            printf("Process %d: Cube = %d\n",
                   rank, value * value * value);
    }

    MPI_Finalize();
    return 0;
}

