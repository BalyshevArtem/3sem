#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Max_size 100

void Split(char* string,char* delimiters,char*** tokens,int* tokensCount){
	
	int len = strlen(string);
	(*tokensCount) = 0;
	(*tokens)[*tokensCount] = strtok(string, delimiters);
	while((*tokens)[*tokensCount] != NULL){
		(*tokensCount)++;
		(*tokens)[*tokensCount] = strtok(NULL, delimiters);
	}
}

int main(){
	int i = 0;
	char string[Max_size] = {};
	int tokensCount = 0;
	char delimiters[2] = {'\t','\n'};
	fgets(string,Max_size,stdin);
	char **tokens;
	tokens = (char**)malloc(Max_size * sizeof(char*));
	for(i = 0; i < Max_size; i++){
		tokens[i] = (char*)malloc(Max_size * sizeof(char));
	}
	Split(string,delimiters,&tokens,&tokensCount);
	for (i = 0; i < tokensCount; i++){
        	printf("%s\n", tokens[i]);
        }
	free(tokens);
	return 0;
}

