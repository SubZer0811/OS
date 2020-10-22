#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

char* strrev (char*);

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

			char str[100] = {0};
			read(fd1[0], str, 100);

			close(fd1[0]);

			close(fd2[0]);
            char temp[100];
            strcat(temp, str);
            char* rev = strrev(temp);

			if(strcmp(str, rev) == 0){
                write(fd2[1], "1", 1);
            }
            else
                write(fd2[1], "0", 1);

			close(fd2[1]);

		}
		else{ 			// Parent block
			close(fd1[0]);

			write(fd1[1], argv[1], strlen(argv[1]));
			close(fd1[1]);

			wait(NULL);
			
			close(fd2[1]);
			
			char result[1];
			read(fd2[0], result, 1);

            if(result[0] == '0'){
                printf("String is not a palindrome\n");
            }
            else{
                printf("String is a palindrome\n");
            }

			close(fd2[0]);
		}
	}
	return 0;
}

char *strrev(char *str)
{
    char *itr1, *itr2;

    for (itr1=str, itr2=str+strlen(str)-1; itr2>itr1; ++itr1, --itr2){
        *itr1 ^= *itr2;
        *itr2 ^= *itr1;
        *itr1 ^= *itr2;
    }
    return str;
}