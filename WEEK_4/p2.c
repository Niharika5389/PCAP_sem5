#include <stdio.h>
#include <mpi.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[] = "HELLO";

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank < 5)
    {
        str[rank] = tolower(str[rank]);

        printf("Process %d: %c\n", rank, str[rank]);
    }

    MPI_Finalize();
    return 0;
}

