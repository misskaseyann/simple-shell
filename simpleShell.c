#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/* program start */
int main() {
	while(1){;
		
		pid_t pid;
		int status;
		char input[100]; 
		char *word_1, *word_2;
		char *done = "quit";

		fgets(input, 100, stdin);
		word_1 = strtok (input, " ");
		word_2 = strtok (NULL, " "); 

		if (*word_1 == *done){
			exit(1);
		}


		pid = fork();

		if (pid < 0){
			printf("it broke\n");
			exit(1);
		}

		else if (pid){
			printf("waiting. . . \n"); //for testing
			wait(&status);
		}

		else{
			printf("about to execute. . . \n"); //for testing

			char *cmd[3]; //trying stuff
			cmd[0] = word_1;
			cmd[1] = word_2;
			cmd[2] = NULL;

			if (execvp(cmd[1], cmd) < 0) { 
				perror("exec failed");
				exit(1);
			}
		}

	}
}
