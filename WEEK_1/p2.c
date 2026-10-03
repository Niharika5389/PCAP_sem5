#include<stdio.h>
#include<omp.h>
int main(){
	omp_set_num_threads(4);
	#pragma omp parallel

	{
		int id,tot;
		id = omp_get_thread_num();
		tot = omp_get_num_threads();
		printf("Thread id: %d, Total threads: %d\n",id,tot);
	}
	return 0;
}
