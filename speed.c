#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NMAX 1000

int** Makematrix(int** mat){
	mat = (int**)calloc(NMAX * NMAX, sizeof(int));
	int i = 0;
	int j = 0;
	for(i; i < NMAX; i++){
		mat[i] = (int*)calloc(NMAX * NMAX, sizeof(int));
	} 
	for (i = 0; i < NMAX; i++){
		for(j = 0; j < NMAX; j++){
			mat[i][j] = rand() % 10;
		}
	}
	return mat;	
}
struct Matrix{
	int** first;
	int** second;
	int** result;
	int counter;
	int del;
};

void PrintMatrix(int** mat){
	int i = 0;
	int j = 0;
	for(i = 0; i < NMAX; i++){
		for(j = 0; j < NMAX; j++){
			printf("%d  ", mat[i][j]);
		}
		printf("\n");
	}
	
}

void* MatrixMult(void* dummy){
	struct Matrix mat = *((struct Matrix*)dummy);
	int j = 0;
	int i;
	int k = 0;
	for(i = 0; i < mat.counter; i++){
		for(j = 0; j < NMAX; j++){
			mat.result[i + mat.del][j] = 0;
			for(k = 0; k < NMAX; k++){
				mat.result[i + mat.del][j] += (mat.first[i + mat.del][k] * mat.second[k][j]);  
			}
		}
	}
	return NULL;
}

int main(){
	int N = 0;
	printf("ENTER N = ");
	scanf("%d", &N);
	srand(time(0));
	int** matrix1;
	int** matrix2;
	int** matrix_result;
	int i = 0;
	matrix_result = (int**)calloc(NMAX * NMAX, sizeof(int));
	for(i = 0; i < NMAX; i++){
		matrix_result[i] = (int*)calloc(NMAX * NMAX, sizeof(int)); 
	} 
	struct Matrix Mat;
	Mat.first = Makematrix(matrix1);
	Mat.second = Makematrix(matrix2);
	Mat.result = matrix_result;
	PrintMatrix(Mat.first);
	printf("\n\n\n");
	PrintMatrix(Mat.second);
	Mat.del = 0;
	Mat.counter = 0;
	Mat.counter = NMAX / N;
	for (i = 0; i < N; i++){
		pthread_t thid;
		int result;
		result = pthread_create(&thid,(pthread_attr_t *)NULL, MatrixMult, &Mat);
		if( result != 0){
			printf("ERROR with Create threads");
			exit(-1);
		}
	pthread_join(thid, (void **) NULL);
	Mat.del += NMAX / N;		
	}
	printf("\n\n\n");
	PrintMatrix(Mat.result);
	for(i = 0; i < NMAX; i++){
		free(Mat.first[i]);
		free(Mat.second[i]);
		free(Mat.result[i]);
	}
	free(Mat.first);
	free(Mat.second);
	free(Mat.result);
	return 0;
}
