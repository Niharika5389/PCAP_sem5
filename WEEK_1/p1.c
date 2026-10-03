#include<stdio.h>
#include<omp.h>
int main(){
	#pragma omp parallel
	{
		int id;
		id = omp_get_num_threads();
		printf("Total number of threads: %d\n",id);
	}
	return 0;
}
