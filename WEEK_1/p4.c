#include<stdio.h>
#include<omp.h>

#define N 5
int main(){
	int a1[N]= {1,2,4,6,8};
	int a2[N] = {2,7,3,0,5};
	int a3[N];
	int i;
	
	#pragma omp parallel for
	for(i=0;i<N;i++){
		int id = omp_get_thread_num();
		a3[i]= a1[i]+a2[i];
		printf("Array element %d initialized by thread %d\n",i,id);
	}
	
	{
		printf("Result\n");
		for(int i=0;i<5;i++){
			printf("%d\t",a3[i]);
		}
	}
	return 0;
}
