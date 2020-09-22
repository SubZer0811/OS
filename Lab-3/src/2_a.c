#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main (int argc, char* argv[]){

	int n = atoi(argv[1]);
    
    pid_t pid=0;
    pid = fork();

	if(pid != 0){
        printf("Even series: ");
        for(int i=0; i<n; i+=2)
            printf("%d ", i);
        printf("\n");
    }else{
        printf("Odd series: ");
        for(int i=1; i<n; i+=2)
            printf("%d ", i);
        printf("\n");
    }


	return 0;
}