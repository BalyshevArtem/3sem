#include"stdio.h"
#include"string.h"
#include"malloc.h"
#include"math.h"
#include"stdlib.h"
void GenerateString(int n, char* string){
        char *prev;
        char *new;
        int i;
        prev = (char*)malloc(((1<<n) - 1) * sizeof(char));
        new = (char*)malloc(((1<<n) - 1) * sizeof(char));
        prev[0] = '\0';
        new[1] = '\0';
        for(i = 0; i < n; i++){
                new[0] = 'a' + i;
                strcat(string, new);
                strcat(string, prev);
                strcpy(prev, string);
                printf("%s\n", string);
        }
        free(prev);
        free(new);
}

int main(){
        int n;
        scanf("%d", &n);
        char *ptr;
        ptr = (char*)malloc(((1<<n) - 1) * sizeof(char));
        GenerateString(n, ptr);
        free(ptr);
        return 0;
}

