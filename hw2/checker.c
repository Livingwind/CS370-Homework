#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int pid = getpid();
	int one, two;
	one = atoi(argv[0]);
	two = atoi(argv[1]);
	printf("Checker process [%d]: Starting.\n", pid);
	if(two % one){
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", pid, two, one);
		printf("Checker process [%d]: Returning 0.\n", pid);
		return 0;
	}
	else{	
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", pid, two, one);
		printf("Checker process [%d]: Returning 1.\n", pid);
		return 1;
	}
}
