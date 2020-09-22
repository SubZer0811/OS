# include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
int main ()
{
	pid_t pid; // this is to use the pid data type - relevant headers above
	pid = fork();
	if (pid == 0){
		
		char * args[]={"ls","-aF","/",0};
		char * env[]={0};
		execve("/bin/ls",args,env);
	}
	else{
		wait (NULL); // parent waits for the child to complete execn.
		printf("Parent Process gets the control \n");
		printf("Parent Has waited for Child to Complete\n");
	}
	return 0;
}