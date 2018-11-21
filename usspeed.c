#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NMAX 1000
int** Makematrix(int** mat){
	mat = (int**)calloc(NMAX * NMAX + 1, sizeof(int*));
	int i = 0;
	int j = 0;
	for(i; i < NMAX; i++){
		mat[i] = (int*)calloc(NMAX * NMAX + 1, sizeof(int));
	} 
	for (i = 0; i < NMAX; i++){
		for(j = 0; j < NMAX; j++){
			mat[i][j] = rand() % 100;
		}
	}
	return mat;	
}

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

int** MultMatrix(int** mat1, int** mat2){
	int i = 0;
	int j = 0;
	int k = 0;
	int** mat_result;
	mat_result = Makematrix(mat_result);
	for(i = 0; i < NMAX; i++){
		for(j = 0; j < NMAX; j++){
			mat_result[i][j] = 0;
			for(k = 0; k < NMAX; k++){
				mat_result[i][j] += (mat1[i][k] * mat2[k][j]);
			}
		}
	}
	return mat_result;	
}

int main(){
	int N = 0;
	srand(time(0));
	int** matrix1;
	int** matrix2;
	int** matrix_result;
	int i = 0;
	matrix_result = (int**)calloc(NMAX * NMAX + 1, sizeof(int*));
	for(i = 0; i < NMAX; i++){
		matrix_result[i] = (int*)calloc(NMAX * NMAX + 1, sizeof(int)); 
	} 
	PrintMatrix(Makematrix(matrix1));
	printf("\n\n\n");
	PrintMatrix(Makematrix(matrix2));
	printf("\n\n\n");
	PrintMatrix(MultMatrix(Makematrix(matrix1), Makematrix(matrix2)));
	return 0;
}

