#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

int main(int argc, char* argv[]){
	int pid = getpid();
	int one, two, shm_id;

	one = atoi(argv[1]);
	two = atoi(argv[2]);

	printf("Checker process [%d]: Starting.\n", pid);
	read(argv[3][0], &shm_id, sizeof(int));
	printf("Checker process [%d]: read 4 bytes containing shm ID %d.\n", pid, shm_id);
	
	int val;
	if(two % one){
		val = 0;
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", pid, two, one);
	}
	else{	
		val = 1;
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", pid, two, one);
	}
	
	char* shm_p = shmat(shm_id, NULL, 0);
	*shm_p = val;
	printf("Checker process [%d]: wrote result (%d) to shared memory.\n", pid, val);
	shmdt(shm_p);
}
