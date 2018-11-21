#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
#include<sys/sem.h>
#include<unistd.h>
#define N_MAX 2

int main(){
	int semid;
	struct sembuf sem;
	int msqid;
	char pathname[] = "file.c";
	key_t key;
	int i, len;
	struct mymsgbuf{
		long mtype;
		int a;
		int b;
		pid_t pid;
	} mybuf;
	struct msgbuf{
		long mtype;
		int result;
	} buf;
	int N;
	(key = ftok(pathname, 0));
	msqid = msgget(key, 0666 | IPC_CREAT);
	semid = semget(key, 1, 0666 | IPC_CREAT);
	scanf("%d", &mybuf.a);
	scanf("%d", &mybuf.b);
	mybuf.pid = getpid();
	mybuf.mtype = 1;
	msgsnd(msqid, &mybuf,sizeof(struct mymsgbuf) - sizeof(long), 0);
	msgrcv(msqid, &buf, sizeof(struct msgbuf) - sizeof(long), getpid(), 0);
	printf("result = %d", buf.result);
	return 0;
}
