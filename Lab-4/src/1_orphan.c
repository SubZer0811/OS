#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

    pid_t pid = fork();

    if(pid == 0){
        sleep(10);
    }
    else{
        exit(0);
    }

    return 0;
}