#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int is_prime(int n)
{
    if (n < 2)
        return 0;

    if (n == 2)
        return 1;

    if (n % 2 == 0)
        return 0;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

void run_schedule(int N, int schedule_type, const char *name)
{
    int *thread_id = malloc((N + 1) * sizeof(int));
    int *prime = malloc((N + 1) * sizeof(int));
    int prime_count = 0;

    for (int i = 0; i <= N; i++)
    {
        thread_id[i] = -1;
        prime[i] = 0;
    }

    omp_set_schedule(schedule_type, 0);

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(runtime) reduction(+:prime_count)
    for (int i = 1; i <= N; i++)
    {
        thread_id[i] = omp_get_thread_num();

        if (is_prime(i))
        {
            prime[i] = 1;
            prime_count++;
        }
    }

    double end = omp_get_wtime();

    printf("Scheduling policy: %s\n", name);

    printf("Number -> Thread -> Prime?\n");

    for (int i = 1; i <= N; i++)
    {
        printf("%5d -> Thread %d -> %s\n",
               i,
               thread_id[i],
               prime[i] ? "Yes" : "No");
    }

    printf("\nTotal prime numbers = %d\n", prime_count);
    printf("Execution time = %.6f seconds\n", end - start);

    free(thread_id);
    free(prime);
}

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    printf("\nMaximum OpenMP threads = %d\n", omp_get_max_threads());

    run_schedule(N, omp_sched_static, "STATIC");

    run_schedule(N, omp_sched_dynamic, "DYNAMIC");

    run_schedule(N, omp_sched_guided, "GUIDED");

    return 0;
}

