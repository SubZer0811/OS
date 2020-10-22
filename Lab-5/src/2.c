#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
	int fd1[2], fd2[2];
	pid_t pid;

	if(pipe(fd1) == -1){
		printf("Unable to create pipe\n");
	}
	if(pipe(fd2) == -1){
		printf("Unable to create pipe\n");
	}

	pid = fork();

	if(pid < 0){
		printf("fork failed\n");
	}
	else{
		if(pid == 0){ 	// Child block
			close(fd1[1]);

			char str1[100], * str2 = "Child!";
			read(fd1[0], str1, 100);

			close(fd1[0]);

			close(fd2[0]);
			
			write(fd2[1], strcat(str1, str2), strlen(str1)+strlen(str2));

			close(fd2[1]);

		}
		else{ 			// Parent block
			close(fd1[0]);

			char* str = "Parent!";
			write(fd1[1], str, strlen(str));
			close(fd1[1]);

			wait(NULL);
			
			close(fd2[1]);
			
			char cat_str[100];
			read(fd2[0], cat_str, 100);
			printf("Concatenated String: %s\n", cat_str);

			close(fd2[0]);
		}
	}
	return 0;
}