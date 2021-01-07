#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void* test_prime(void*);
void* runner (void* args);

int main(int argc, char const *argv[]){

	int range = atoi(argv[1]);

	pthread_t runner_thread;
	pthread_create(&runner_thread, NULL, runner, &range);

	pthread_join(runner_thread, NULL);
	printf("\n");
}

void* runner (void* args){
	int range = *(int *)args;

	pthread_t tid[range];
	int thread_args[range];
	printf("Prime numbers from 1 to %d: 1 2 ", range);
	for(int i=2; i<range; i++){
		thread_args[i] = i;
		pthread_create(&tid[i], NULL, test_prime, &thread_args[i]);
	}

	for(int i=0; i<range; i++){
		pthread_join(tid[i], NULL);
	}
}

void* test_prime(void* args){

	int num = *(int *)args;
	int flag = 0;

	for(int i=2; i<=num/2+1; i++){
		if(num%i == 0){
			flag = 1;
			break;
		}
	}
	
	if(flag == 0){
		printf("%d ", num);
	}
	num += 1;

	return NULL;
}