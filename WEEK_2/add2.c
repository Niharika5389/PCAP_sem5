#include <stdio.h>
#include <omp.h>

int main()
{
    int n, i;

    printf("Enter the size of arrays: ");
    scanf("%d", &n);

    int A[n], B[n], C[n];

    printf("Enter elements of array A:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter elements of array B:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &B[i]); 


    #pragma omp parallel for
    for (i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
    }

    printf("Resultant array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", C[i]);

    printf("\n");

    return 0;
}

