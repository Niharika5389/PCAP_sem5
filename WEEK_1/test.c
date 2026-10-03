#include<stdio.h>
#include<omp.h>
int main(){
	#pragma omp parallel
	{
		int id;
		omp_set_num_threads(4);
		id = omp_get_thread_num();
		tot = omp_get_num_threads();
		printf("Thread id: %d\n, Total threads: %d\n",id,tot);
	}
	return 0;
}
