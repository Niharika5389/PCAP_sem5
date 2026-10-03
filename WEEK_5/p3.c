#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, len, part, local_count = 0;
    char *str = NULL;
    char *local = NULL;
    int *counts = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        scanf("%s", str = malloc(1000));
        len = strlen(str);
        counts = malloc(size * sizeof(int));
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    part = len / size;

    local = malloc((part + 1) * sizeof(char));

    MPI_Scatter(str, part, MPI_CHAR,
                local, part, MPI_CHAR, 0, MPI_COMM_WORLD);

    for(int i = 0; i < part; i++)
    {
        if(local[i] != 'a' && local[i] != 'e' &&
           local[i] != 'i' && local[i] != 'o' &&
           local[i] != 'u' && local[i] != 'A' &&
           local[i] != 'E' && local[i] != 'I' &&
           local[i] != 'O' && local[i] != 'U')
            local_count++;
    }

    MPI_Gather(&local_count, 1, MPI_INT,
               counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        int total = 0;

        for(int i = 0; i < size; i++)
        {
            printf("%d ", counts[i]);
            total += counts[i];
        }

        printf("\n%d\n", total);

        free(str);
        free(counts);
    }

    free(local);

    MPI_Finalize();
    return 0;
}

