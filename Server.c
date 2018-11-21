#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
#define N_MAX 3


int main(){
	int* N;
	int shmid;
	int new = 1;
	int semid;
	struct sembuf sem;
        int msqid;
        char pathname[] = "file.c";
        key_t key;
        int i, len;
	struct msgbuf{
		long mtype;
		int result;
	} buf;
        struct mymsgbuf{
                long mtype;
                int a;
		int b;
		pid_t pid;
        } mybuf;
        (key = ftok(pathname, 0));
        msqid = msgget(key, 0666 | IPC_CREAT);
	pid_t pid;
	sem.sem_op = N_MAX;
	sem.sem_flg = 0;
	sem.sem_num = 0;
	semop(semid, &sem, 1);
	while(1){
		sem.sem_op = -1;
               	sem.sem_flg = 0;
               	sem.sem_num = 0;	
               	semop(semid, &sem, 1);
		msgrcv(msqid, &mybuf, sizeof(struct mymsgbuf) - sizeof(long), 1, 0);
		pid = fork();
		if(pid == 0){
			sleep(10);
			buf.result = mybuf.a * mybuf.b;
			buf.mtype = mybuf.pid;
			msgsnd(msqid, &buf, sizeof(struct msgbuf) - sizeof(long), 0);
			sem.sem_op = 1;
			sem.sem_flg = 0;
			sem.sem_num = 0;
			semop(semid, &sem, 1);
			exit(-1); 
		}
	}
        return 0;
}

