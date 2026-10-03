#include<stdio.h>
#include<omp.h>

#define ROWS 5
#define COLS 5
int main(){
	int arr[ROWS][COLS];
	int i,j;
	
	#pragma omp parallel for private(j)
	
	for(i=0;i<ROWS;i++){
		int id = omp_get_thread_num();
		for(j=0;j<COLS;j++){
			arr[i][j] = i*COLS+j+1;
		}
		printf("Row %d initialized by thread %d\n",i,id);
	}
	
	{
		for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			printf("%4d",arr[i][j]);
		}
		printf("\n");
	}
	}
	return 0;
}
