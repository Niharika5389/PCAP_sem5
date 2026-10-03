#include <stdio.h>
#include <omp.h>

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    #pragma omp parallel
    {
        int x = omp_get_thread_num();
        long long result = 1;

        for (int i = 0; i < x; i++) {
            result *= n;
        }

        printf("Thread %d: %d^%d = %lld\n", n, n, x, result);
    }

    return 0;
}

