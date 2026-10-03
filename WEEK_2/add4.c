#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    int i;

    if (n < 2)
        return 0;

    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int start, end, i;

    printf("Enter the interval: ");
    scanf("%d %d", &start, &end);

    printf("Prime numbers between %d and %d are:\n", start, end);

    #pragma omp parallel for
    for (i = start; i <= end; i++)
    {
        if (isPrime(i))
        {
            #pragma omp critical
            {
                printf("%d ", i);
            }
        }
    }

    printf("\n");

    return 0;
}

