# include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
int main ()
{
	pid_t pid; // this is to use the pid data type - relevant headers above
	pid = fork();
	if (pid == 0){
		char *const argv[] = {"/bin/ls", NULL};
		execvp(argv[0], argv);
	}
	else{
		wait (NULL); // parent waits for the child to complete execn.
		printf("Parent Process gets the control \n");
		printf("Parent Has waited for Child to Complete\n");
	}
	return 0;
}