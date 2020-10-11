#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

	int count = 0;

	while(1){
		pid_t pid = fork();
		if(pid == 0){
			sleep(10);
			exit(0);
		}
		count += 1;
		if(pid < 0){
			printf("Could not create more processes\n");
			break;
		}	
	}

	printf("Total number of processes created: %d\n", count);
	wait(NULL);

	return 0;
}