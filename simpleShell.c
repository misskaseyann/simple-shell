#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/* Simple command interpreter or shell. */
int main() {

	printf("Shell started. To quit please type 'quit'.\n");

	while(1){

		printf("gwsh: ");
		pid_t pid;
		int status;

		char input[100];
		char *params[15];
		char *command;
		char *done = "quit";

		fgets(input, 100, stdin);
		char *split_string = strtok (input, " ");

		/* Get the first initial command. */
		command = split_string;
		split_string = strtok (NULL, " ");

		/* Get all arguments. */
		int i = 0;
		while (split_string != NULL) {
			params[i++] = split_string;
			split_string = strtok (NULL, " ");
		};
		params[i] = NULL;

		/* Prints arguments for debugging. */
		i = 0;
		while (params[i] != NULL) {
			printf("%s\n",params[i]);
			i++;
		}

		/* Exit command to quit shell. */
		if (*command == *done){
			exit(0);
		}

		pid = fork();

		if (pid < 0){
			printf("Error: fork failed.\n");
			exit(1);
		}

		else if (pid){
			printf("waiting. . . \n"); //for testing
			wait(&status);
		}

		else{
			printf("about to execute. . . \n"); //for testing

			char *cmd[3]; //trying stuff
			cmd[0] = command;
			//cmd[1] = params;
			cmd[2] = NULL;

			if (execvp(cmd[1], cmd) < 0) { 
				perror("exec failed");
				exit(1);
			}
		}

	}
}
