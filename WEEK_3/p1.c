#include <stdio.h>
#include <omp.h>

int main()
{
    int N = 10;
    int sum = 0;
    int value = 100;

    printf("N = %d\n", N);

    #pragma omp parallel for shared(sum, value)
    for (int i = 1; i <= N; i++)
    {
        #pragma omp atomic
        sum += i;

        value = i;   
    }

    printf("\n--- SHARED ---\n");
    printf("Sum = %d\n", sum);
    printf("Value = %d (depends on which thread writes last)\n", value);


    sum = 0;
    value = 100;

    #pragma omp parallel for private(value) reduction(+:sum)
    for (int i = 1; i <= N; i++)
    {
        value = i;
        sum += i;
    }

    printf("\n--- PRIVATE ---\n");
    printf("Sum = %d\n", sum);
    printf("Value = %d (original value remains unchanged)\n", value);


    sum = 0;
    value = 100;

    #pragma omp parallel for firstprivate(value) reduction(+:sum)
    for (int i = 1; i <= N; i++)
    {
        value = value + i;
        sum += i;
    }

    printf("\n--- FIRSTPRIVATE ---\n");
    printf("Sum = %d\n", sum);
    printf("Value = %d (original value remains unchanged)\n", value);

    sum = 0;
    value = 100;

    #pragma omp parallel for lastprivate(value) reduction(+:sum)
    for (int i = 1; i <= N; i++)
    {
        value = i;
        sum += i;
    }

    printf("\n--- LASTPRIVATE ---\n");
    printf("Sum = %d\n", sum);
    printf("Value = %d (value from logically last iteration)\n", value);

    return 0;
}

