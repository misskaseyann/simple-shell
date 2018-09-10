#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

/* Simple command interpreter or shell. */
int main() {

	/* Print intro! */
	printf("\n  /\\___/\\\n ( o   o )\n (  =^=  ) \n (        )\n (         )\n (          )))))))))))\n\n");
	printf("~* Welcome to tinyshell by kehlsey & kasey!\n");
	printf("~* To quit please type 'quit'. \n\n");

	while(1){

		printf("tinyshell ~ ");
		pid_t pid;
		int status;
		struct rusage usage;

		char input[100];
		char *params[15];
		char *done = "quit";

		fgets(input, 100, stdin);

		/* Handle new lines and spaces. */
		while (input[0] == '\n' || input[0] == ' ')
			fgets(input, 100, stdin);

		/* Add null terminator. */
		int len;
		len = strlen(input);
		if (len > 0 && input[len-1] == '\n')
    		input[len-1] = '\0';

		/* Store commands. */
		char *split_string = strtok (input, " ");
		int i = 0;
		while (split_string != NULL) {
			params[i] = split_string;
			split_string = strtok (NULL, " ");
			i++;
		};
		params[i] = NULL;

		/* Prints arguments for debugging. */
		// i = 0;
		// while (params[i] != NULL) {
		// 	printf("%s\n",params[i]);
		// 	i++;
		// }

		/* Exit command to quit shell. */
		if (*params[0] == *done) {
			printf("~* bye! :)\n");
			exit(0);
		};

		pid = fork();

		/* Catch failure and exit program. */
		if (pid < 0){
			printf("Error: fork failed.\n");
			exit(1);
		}

		/* Parent waits for child. */
		else if (pid) {
			//printf("waiting. . . \n"); //for testing
			waitpid(-1, &status, 0);
			getrusage(RUSAGE_CHILDREN, &usage);
			printf("User CPU time: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
			printf("Context switches: %ld\n", usage.ru_nivcsw);
		}

		/* This is the child, execute command. */
		else {
			//printf("about to execute. . . \n"); //for testing
			execvp(params[0], params);
			printf("tinyshell ~ Unknown command!\n");
			exit(0);
		}

	}
}
