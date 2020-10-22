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

	pid = fork();
	if(pid < 0){
		printf("fork failed\n");
	}
	else{
		if(pid == 0){ 	// Child block
			close(fd1[1]);

			char str1[100];
			read(fd1[0], str1, 100);

            for(int len=1; len<=strlen(str1); len+=1){
                for(int ptr=0; ptr+len-1<strlen(str1); ptr+=1){
                    for(int i=ptr; i<ptr+len; i++){
                        printf("%c", str1[i]);
                    }
                    printf("\n");
                }
            }

			close(fd1[0]);
		}
		else{ 			// Parent block
			close(fd1[0]);

			write(fd1[1], argv[1], strlen(argv[1]));
			close(fd1[1]);

			wait(NULL);
		}
	}
	return 0;
}