#include <stdio.h>
#include <omp.h>

int reverse(int n)
{
    int rev = 0;

    while (n > 0)
    {
        rev = rev * 10 + (n % 10);
        n = n / 10;
    }

    return rev;
}

int main()
{
    int A[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int n = sizeof(A) / sizeof(A[0]);
    int i;

    #pragma omp parallel for
    for (i = 0; i < n; i++)
    {
        A[i] = reverse(A[i]);
    }

    printf("Array after reversing digits:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");

    return 0;
}

