#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"split.h"
#include<sys/sem.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
#define NAMEFILE "helper.txt"
#define MAX_SIZE 100
#define TABLE_LIMIT 2

void File_Read(FILE *mf, char *string){
        mf = fopen(NAMEFILE, "r");
        char *estr;
        char str[MAX_SIZE] = {};
        do{
                estr = fgets(str, MAX_SIZE, mf);
                if(estr == NULL){
                        break;
                }
                strcat(string, str);
        }while(estr);
        fclose(mf);
}


int Choose(char* dish, char** tokens, int tokensCount){
	int i;
	for(i = 0; i < tokensCount; i += 2){
		if(!strcmp(tokens[i], dish)){
			return atoi(tokens[i + 1]);
		}
	}
	printf("error in choose");
	exit(-1);
}


int main(){
	int msgid;
	int len;
	struct mymsgbuf{
		long mtype;
		char mtext[MAX_SIZE];
	} mybuf;
	int semid1;
	char pathname[] = "a.c";
	key_t key;
	struct sembuf buf;
	if((key = ftok(pathname, 0)) < 0){
		exit(-1);
	}
	if((semid1 = semget(key, 1, 0666 | IPC_CREAT)) < 0){
		exit(-1);
	}
	if((msgid = msgget(key, 0666 | IPC_CREAT) < 0)) printf("error");
	msgid = msgget(key, 0666 |IPC_CREAT);
	char string[MAX_SIZE] = {};
	FILE *f;
	char text[MAX_SIZE];
	File_Read(f, text);
	printf("text :\n%s", text);
	char **tokens;
        tokens = (char**)calloc(MAX_SIZE, sizeof(char*));
        int i;
        for(i = 0; i < MAX_SIZE; i++){
        	tokens[i] = (char*)calloc(MAX_SIZE, sizeof(char));
        	}
	char delimeters[] = {'\n', ':'};
	int tokensCount = 0;
	Split(text, delimeters, &tokens, &tokensCount); 
	FILE *mf;
	int slp = 0;
	
	while(mybuf.mtype != 228){	
		msgrcv(msgid, (struct msgbuf *) &mybuf, sizeof(struct mymsgbuf) - sizeof(long), 1, 0);		
		printf("I recive %s\n", mybuf.mtext);
		slp = Choose(mybuf.mtext, tokens, tokensCount);
		sleep(slp);
		printf("I help with %s in %d sec\n", mybuf.mtext, slp); 
		buf.sem_op = 1;
                buf.sem_flg = 0;
                buf.sem_num = 0;
                semop(semid1, &buf, 1);

	}
	return 0;
	
}
