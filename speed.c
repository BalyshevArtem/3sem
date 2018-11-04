//Для N = 3 ускорение составило ~8,7 
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/*
У вас, как я понял, квадратные матрицы со стороной (N * N + 1) и вы их перемножаете с помощью N нитей.
Чтобы честно измерить ускорение нужно:
1) взять пару матриц большого размера, например, 1000 * 1000
2) Число нитей K варьировать от 1 до числа процессоров на вашем компьютере, т.е. до 4 или 8, при этом 
размеры матриц не меняются.
3) на всякий случай удостовериться, что при фиксированных входных матрицах результирующее произведение от числа нитей K не зависит.
*/

int** Makematrix(int** mat, int n){
	mat = (int**)calloc(n * n + 1, sizeof(int));
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
struct Matrix{
	int** first;
	int** second;
	int** result;
	int counter;
	int constN;
};

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

void* MatrixMult(void* dummy){
	struct Matrix mat = *((struct Matrix*)dummy);
	int i = 0;
	int j = 0;
	int k = 0;
	for(j = 0; j < mat.constN; j++){
		mat.result[mat.counter][j] = 0;
		for(k = 0; k < mat.constN; k++){
			mat.result[mat.counter][j] += (mat.first[mat.counter][k] * mat.second[k][j]);  
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
	matrix_result = (int**)calloc(N * N + 1, sizeof(int));
	for(i = 0; i < N; i++){
		matrix_result[i] = (int*)calloc(N * N + 1, sizeof(int)); 
	} 
	struct Matrix Mat;
	Mat.first = Makematrix(matrix1, N);
	Mat.second = Makematrix(matrix2, N);
	Mat.result = matrix_result;
	PrintMatrix(Mat.first, N);
	printf("\n\n\n");
	PrintMatrix(Mat.second, N);
	Mat.constN = N;
	for (i = 0; i < N; i++){
		pthread_t thid;
		int result;
		Mat.counter = i;
		result = pthread_create(&thid,(pthread_attr_t *)NULL, MatrixMult, &Mat);
		if( result != 0){
			printf("ERROR with Create threads");
			exit(-1);
		}
	pthread_join(thid, (void **) NULL);		
	}
	printf("\n\n\n");
	PrintMatrix(Mat.result, N);
	for(i = 0; i < N; i++){
		free(Mat.first[i]);
		free(Mat.second[i]);
		free(Mat.result[i]);
	}
	free(Mat.first);
	free(Mat.second);
	free(Mat.result);
	return 0;
}
