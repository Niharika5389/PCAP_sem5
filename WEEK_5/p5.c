#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void selectionSort(int *a, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;

        for(int j = i + 1; j < n; j++)
            if(a[j] < a[min])
                min = j;

        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

void merge(int *a, int *b, int *c, int n)
{
    int i = 0, j = 0, k = 0;

    while(i < n && j < n)
    {
        if(a[i] < b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }

    while(i < n)
        c[k++] = a[i++];

    while(j < n)
        c[k++] = b[j++];
}

int main(int argc, char *argv[])
{
    int rank, size, n;
    int *a = NULL;
    int *local = NULL;
    int *result = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        scanf("%d", &n);

        a = malloc(n * sizeof(int));

        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int part = n / size;

    local = malloc(part * sizeof(int));

    MPI_Scatter(a, part, MPI_INT,
                local, part, MPI_INT, 0, MPI_COMM_WORLD);

    selectionSort(local, part);

    MPI_Gather(local, part, MPI_INT,
               a, part, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        result = malloc(n * sizeof(int));

        for(int step = 1; step < size; step *= 2)
        {
            for(int i = 0; i < n; i += 2 * step * part)
            {
                int left = i;
                int mid = i + step * part;
                int right = i + 2 * step * part;

                if(mid >= n)
                    continue;

                if(right > n)
                    right = n;

                int x = left;
                int y = mid;
                int k = 0;

                while(x < mid && y < right)
                {
                    if(a[x] < a[y])
                        result[k++] = a[x++];
                    else
                        result[k++] = a[y++];
                }

                while(x < mid)
                    result[k++] = a[x++];

                while(y < right)
                    result[k++] = a[y++];

                for(int j = 0; j < k; j++)
                    a[i + j] = result[j];
            }
        }

        for(int i = 0; i < n; i++)
            printf("%d ", a[i]);

        free(result);
        free(a);
    }

    free(local);

    MPI_Finalize();
    return 0;
}

