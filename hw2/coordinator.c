#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int status;
	for(int i = 2; i < argc; i++){
		if(!(pid = fork()))
			execlp(".//checker", argv[1], argv[i], NULL);
		else{
			printf("Coordinator: forked process with ID %d.\n", pid);
			printf("Coordinator: waiting for process [%d].\n", pid);
			waitpid(pid, &status, 0);
			printf("Coordinator: child process %d returned %d.\n", pid, WEXITSTATUS(status));
		}
	}

	printf("Coordinator: exiting\n");	
	return 0;
}
