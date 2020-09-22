#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int main (){

	int n=100000;

	int i=0, num=0, sum=0, pow_to=0, j=0;

	for(i=0; i<n; i=i+1){

		sum = 0;
		num = i;
		pow_to = 0;
		for(; num>0; num/=10)
			pow_to+=1;
		num = i;

		pid_t pid = vfork();
		if(pid == 0){
			while (num>0){	
				int digit = num%10;
				sum = sum + pow(digit, pow_to);
				num = num/10;
			}
			exit(0);
		}
		else{
			wait(NULL);
			if(sum == i)
				printf("armstrong : %d\n", i);
		}
	}

	return 0;
}