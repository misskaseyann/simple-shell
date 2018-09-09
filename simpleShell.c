#include <stdio.h>

/* program start */
int main() {
	while(true){
		pid_t pid;
		char command = 'ls'
		char params = ''

		scanf("%s", &input);
		if (input == 'quit'){
			break;
		}
	//read_command(&command, &params) //unsure of reading the command part

		pid = fork();
		if (pid < 0){
			//error_routine()
			printf("halp\n");
			printf("fix it\n");
		}

		else if (pid){
			waitpid(-1, &status, 0)
		}

		else{
			execve(command, params, 0)
		}

	}
}
