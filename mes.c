#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>

#define MaxSize 1024

// FIXIT: общее замечание: много дублирующихся (или очень схожих) участков кода.
// В вашем арсенале есть: 1) вынесение участков кода в отдельные ф-и ... различающиеся части передаются параметрами
// 2) тернарный оператор условие ? выражение1 : выражение2
// 3) изменение порядка if'ов

int main(int argc, char* argv[]){
	char *name1 = "aaa.fifo";
	char *name2 = "a.fifo";
	int fd[2]; 
	mknod(name1, S_IFIFO | 0666, 0);
        mknod(name2, S_IFIFO | 0666, 0);
	if(atoi(argv[1]) == 0){
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
	if(atoi(argv[1]) == 1){
            	pid_t pid = fork();
            	if (pid == 0){
			char input[MaxSize] = {};
                	char output[MaxSize] = {};
                        if ((fd[0] = open(name2, O_WRONLY)) < 0){
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
                        if((fd[1] = open(name1, O_RDONLY)) < 0){
                                printf("Cannot open FIFO for Reading");
                                exit(-1);
                        }
                        while(1){	
                                read(fd[1], output, MaxSize);
                        	printf("%s", output);	
                        }
                }

	}
	
	return 0;
}
