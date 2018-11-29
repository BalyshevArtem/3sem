#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#define MAX_SIZE 1000

void find(char* current, int* depth, char* text){
	if((*depth) < 0){
		printf("Not found in the dir = %s\n", current);
		return;
	}
	DIR* dir;
        dir = opendir(current);
	struct stat buf;
        struct dirent *dire;
	char new_dir[MAX_SIZE];
	strcpy(new_dir, current);
	dire = readdir(dir);
	strcpy(new_dir, current);
      	strcat(new_dir, "/");
       	strcat(new_dir, dire->d_name);
	while(dire != NULL){
		strcpy(new_dir, current);
                strcat(new_dir, "/");
                strcat(new_dir, dire->d_name);
		stat(new_dir, &buf);
		if(S_ISREG(buf.st_mode)){
			if(!strcmp(dire->d_name, text)){
				printf("FOUND !\n");
				printf("%s\n", current);
				return;
			}
		}
		if(S_ISDIR(buf.st_mode) && (strcmp(dire->d_name, ".") && strcmp(dire->d_name, ".."))){
			printf("New dir = %s\n", new_dir);
			(*depth)--;
			find(new_dir, depth, text);
			(*depth)++;
		}
	dire = readdir(dir);
	}
	
	
}

int main(int argc, char** argv){
	int depth = atoi(argv[2]);
	char* name;
	DIR* dir;
	char text[MAX_SIZE];
	strcpy(text, argv[3]);
	char current[MAX_SIZE];
	strcpy(current, argv[1]);
	find(current, &depth, text);
	return 0;
}
