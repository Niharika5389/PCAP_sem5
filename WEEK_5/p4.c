#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, len, part;
    char *s1 = NULL;
    char *s2 = NULL;
    char *r = NULL;
    char *l1, *l2, *lr;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Number of processes: %d\n", size);
    if (rank == 0)
    {
        s1 = malloc(1000);
        s2 = malloc(1000);

        scanf("%s", s1);
        scanf("%s", s2);

        len = strlen(s1);

        if (strlen(s2) != len)
        {
            printf("Strings must be of same length\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        r = malloc(2 * len + 1);

        
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (len % size != 0)
    {
        if (rank == 0)
            printf("String length must be divisible by number of processes\n");

        MPI_Finalize();
        return 0;
    }

    part = len / size;

    l1 = malloc(part);
    l2 = malloc(part);
    lr = malloc(2 * part);

    MPI_Scatter(s1, part, MPI_CHAR,
                l1, part, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Scatter(s2, part, MPI_CHAR,
                l2, part, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < part; i++)
    {
        lr[2 * i] = l1[i];
        lr[2 * i + 1] = l2[i];
    }

    MPI_Gather(lr, 2 * part, MPI_CHAR,
               r, 2 * part, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        r[2 * len] = '\0';
        printf("Result: %s\n", r);

        free(s1);
        free(s2);
        free(r);
    }

    free(l1);
    free(l2);
    free(lr);

    MPI_Finalize();

    return 0;
}

