#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>

#define MaxSize 1024

void Messenger(char* name1, char* name2);

int main(int argc, char* argv[]){
	char *name1 = "aaa.fifo";
	char *name2 = "a.fifo";
	mknod(name1, S_IFIFO | 0666, 0);
        mknod(name2, S_IFIFO | 0666, 0);
	if(atoi(argv[1]) == 0){
		Messenger(name1, name2);
	}
	if(atoi(argv[1]) == 1){
		Messenger(name2, name1);
	}
	return 0;
}

void Messenger(char* name1, char* name2){
	int fd[2];
	pid_t pid = fork();
                if (pid == 0){
                        char input[MaxSize] = {};
                        char output[MaxSize] = {};
                        if ((fd[0] = open(name1, O_WRONLY)) < 0){
                                printf("Cannot open FIFO for Writing");
                                exit(-1);
                        }
                        while(1){
                                fgets(input, MaxSize, stdin);
                                write(fd[0], input, MaxSize);   
                        }
                } else {
                        char input[MaxSize] = {};
                        char output[MaxSize] = {};
                        if((fd[1] = open(name2, O_RDONLY)) < 0){
                                printf("Cannot open FIFO for Reading");
                                exit(-1);
                        }
                        while(1){
                                read(fd[1], output, MaxSize);
                                printf("%s", output);
                        }
                }
        }

