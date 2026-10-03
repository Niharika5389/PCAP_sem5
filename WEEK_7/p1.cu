#include <stdio.h>
#include <cuda_runtime.h>

int main() {
    int n;
    cudaGetDeviceCount(&n);
    printf("CUDA Devices: %d\n", n);

    for (int i = 0; i < n; i++) {
        cudaDeviceProp p;
        cudaGetDeviceProperties(&p, i);

        printf("\nDevice %d: %s\n", i, p.name);
        printf("SMs: %d\n", p.multiProcessorCount);
        printf("Max Threads/Block: %d\n", p.maxThreadsPerBlock);
        printf("Max Threads Dim: %d %d %d\n",
               p.maxThreadsDim[0], p.maxThreadsDim[1], p.maxThreadsDim[2]);
        printf("Max Grid Dim: %d %d %d\n",
               p.maxGridSize[0], p.maxGridSize[1], p.maxGridSize[2]);
        printf("Clock Frequency: %d kHz\n", p.clockRate);
    }
    return 0;
}

