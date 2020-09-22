#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

	pid_t pid = fork();
	int n = 10;

	if(pid == 0){
		int flag = 0, num = 3;
		printf("Prime Number Series: 1 2 ");

		while (n > 2){
			flag = 0;
			for(int i=2; i<=num/2+1; i++){
				if(num%i == 0){
					flag = 1;
					break;
				}
			}
			
			if(flag == 0){
				printf("%d ", num);
				n -= 1;
			}
			num += 1;
		}
		printf("\n");
	}
	else{
		printf("Fibonacci Series: 0 1 ");
		int fib_a = 0, fib_b = 1;
		for(int i=2; i<n; i++){
			printf("%d ", fib_a+fib_b);
			fib_b = fib_a + fib_b;
			fib_a = fib_b - fib_a;
		}
		printf("\n");
	}

	return 0;
}