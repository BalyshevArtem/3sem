#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int** Makematrix(int** mat, int n){
	mat = (int**)calloc(n * n + 1, sizeof(int*));
	int i = 0;
	int j = 0;
	for(i; i < n; i++){
		mat[i] = (int*)calloc(n * n + 1, sizeof(int));
	} 
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			mat[i][j] = rand() % 100;
		}
	}
	return mat;	
}

void PrintMatrix(int** mat, int n){
	int i = 0;
	int j = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d  ", mat[i][j]);
		}
		printf("\n");
	}
	
}

int** MultMatrix(int** mat1, int** mat2, int N){
	int i = 0;
	int j = 0;
	int k = 0;
	int** mat_result;
	mat_result = Makematrix(mat_result, N);
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			mat_result[i][j] = 0;
			for(k = 0; k < N; k++){
				mat_result[i][j] += (mat1[i][k] * mat2[k][j]);
			}
		}
	}
	return mat_result;	
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
	matrix_result = (int**)calloc(N * N + 1, sizeof(int*));
	for(i = 0; i < N; i++){
		matrix_result[i] = (int*)calloc(N * N + 1, sizeof(int)); 
	} 
	PrintMatrix(Makematrix(matrix1, N), N);
	printf("\n\n\n");
	PrintMatrix(Makematrix(matrix2, N), N);
	printf("\n\n\n");
	PrintMatrix(MultMatrix(Makematrix(matrix1, N), Makematrix(matrix2, N), N), N);
	return 0;
}

