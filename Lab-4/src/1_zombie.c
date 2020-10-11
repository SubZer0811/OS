#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

    pid_t pid = fork();

    if(pid == 0){
        exit(0);
    }
    else{
        sleep(10);
    }

    return 0;
}