#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<assert.h>

// FIXIT: называйте константа, объявленные с помощью define в таком стиле: MAX_SIZE

#define Max_size 100
#define Max_Time 5

void Split(char* string,char* delimiters,char*** tokens,int* tokensCount){

	int len = strlen(string);
	*tokensCount = 0;
	(*tokens)[*tokensCount] = strtok(string, delimiters);
	while((*tokens)[*tokensCount] != NULL){
		(*tokensCount)++;
		(*tokens)[*tokensCount] = strtok(NULL, delimiters);
	}
}

int main(){
	int i;
	char string[Max_size] = {};
	int tokensCount = 0;
	char *estr;
	int status;
	char str[Max_size] = {};
	char delimiters[2] = {'\t','\n'};
	FILE *mf;
	mf = fopen("primer.txt", "r");
	
	// лучше написать do { ... } while (estr);
	// FIXIT: fgets (str,Max_size,mf) -> fgets(str, Max_size, mf)
	while (1){
      		estr = fgets (str,Max_size,mf);
		strcat(string, str);
		if (estr == NULL){
			break;
		}
	}
	
	char **tokens;
	tokens = (char**)calloc(Max_size, sizeof(char*));
	for(i = 0; i < Max_size; i++){
		tokens[i] = (char*)calloc(Max_size, sizeof(char));
	}
	
	Split(string, delimiters, &tokens, &tokensCount);
	
	for (i = 0; i < tokensCount; i++){
	
		// FIXIT: вы дублируете код Split. лучше позвать эту ф-и с нужными параметрами
		char* argv_[Max_size] = {0};
		int j = 0;
		// FIXIT: argv_ -> argv, т.к. в этом подчеркивании глубокого смысла нет
		argv_[0] = strtok(tokens[i], " ");
		while(argv_[j] != NULL){
			j++;
			argv_[j] = strtok(NULL, " ");
		}
		
		pid_t  pid;
		pid = fork();
		if (pid == 0){
			pid = fork();
			if (pid == 0){
				sleep(atoi(argv_[0]));
				// FIXIT: вместо сдвига на 1 элемент ведь можно просто вызвать execvp(argv[1], argv + 1);
				int k;
				for(k = 0; k < Max_size - 1; k++){
					argv_[k] = argv_[k + 1]; 
				}
				execvp(argv_[0], argv_);
				// вот здесь лучше написать exit(0) на всякий случай. если команду запустить не получится, то и исходный родительский и этот дочерний процесс продолжат запускать новые поцессы, чего явно не хочется
			} else {
				// Величина atoi(argv_[0]) продублирована дважды. Луше до fork объявить переменную timeout ... и дублирования кода избегаете, и делаете код "самодокументированным" 
				sleep(atoi(argv_[0]) + Max_Time);
				if(waitpid(pid, &status, WNOHANG))
					exit(0);
				else
				{
					kill(pid, SIGKILL);
					exit(0);
				}
			}
		}
	}

        free(tokens);
        return 0;
	
}
