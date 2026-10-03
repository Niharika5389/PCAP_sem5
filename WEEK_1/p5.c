#include<stdio.h>
#include<omp.h>

#define ROWS 2
#define COLS 2
int main(){
	int a1[ROWS][COLS];
	int a2[ROWS][COLS];
	int i,j;
	printf("Rows: %d Cols: %d",ROWS,COLS);
	printf("Matrix 1:\n");
	for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
			scanf("%d",&a1[i][j]);
		}
	}
	printf("Matrix 2:\n");
	for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
			scanf("%d",&a2[i][j]);
		}
	}
	int a3[ROWS][COLS];
	
	#pragma omp parallel for private(j)
	
	for(i=0;i<ROWS;i++){
		int id = omp_get_thread_num();
		for(j=0;j<COLS;j++){
			a3[i][j] = a1[i][j] + a2[i][j];
		}
		printf("Row %d computed by thread %d\n",i,id);
	}
	
	{
		printf("Result\n");
		for(int i=0;i<ROWS;i++){
			for(int j=0;j<COLS;j++){
				printf("%d\t",a3[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
