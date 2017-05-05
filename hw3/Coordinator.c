#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, char* argv[]){
	if(argc != 6)
		exit(-1);

	int status;
	pid_t pid[4];
	int pipeIO[2];
	int shm_id[4];

	for(int i = 0; i < 4; i++){
		pipe(pipeIO);
		if(!(pid[i] = fork())){
			close(pipeIO[1]);	
			execlp(".//Checker", ".//Checker", argv[1], argv[i+2], pipeIO, NULL);
			exit(-1);
		}
		else{
			close(pipeIO[0]);
			printf("Coordinator: forked process with ID %d\n", pid[i]);
			shm_id[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
			write(pipeIO[1], &shm_id[i], sizeof(int));
			printf("Coordinator: wrote shm ID %d to pipe (4 bytes)\n", shm_id[i]);
		}	
	}

	int val;
	char* shm_p;
	for(int i = 0; i < 4; i++){
		printf("Coordinator: waiting on child process ID %d...\n", pid[i]);
		waitpid(pid[i], &status, 0);
		shm_p = shmat(shm_id[i], NULL, 0);
		val = *shm_p;
		printf("Coordinator: result %d read from shared memory: %d %s divisible by %d.\n"
			 ,*shm_p, atoi(argv[i+2]), (val)?"is":"is not", atoi(argv[1]));
		shmdt(shm_p);
		shmctl(shm_id[i], IPC_RMID, NULL);
	} 
	printf("Coordinator: exiting\n");	
	return 0;
}
