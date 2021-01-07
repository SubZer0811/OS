#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#include<unistd.h>
#define N 5

void *producer(void *args);
void *consumer(void *args);

int buf[N];
int in = 0,out = 0,counter = 0;
int flag[] = {0,0};
int turn = 0;

void lock(int self){

    // Set flag[self] = 1 saying you want to acquire lock
    flag[self] = 1;
 
    // But, first give the other thread the chance to
    // acquire lock
    turn = 1-self;
 
    // Wait until the other thread looses the desire
    // to acquire lock or it is your turn to get the lock.
    while (flag[1-self]==1 && turn==1-self);
}
 
// Executed after leaving critical section
void unlock(int self){

    // You do not desire to acquire lock in future.
    // This will allow the other thread to acquire
    // the lock.
    flag[self] = 0;
}

int main(){	

	pthread_t tid[2];
	
	pthread_create(&tid[0], NULL, producer, NULL);
	pthread_create(&tid[1], NULL, consumer, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	return 0;
}

void *producer(void *args){

	int data = 3,i = 0;
	while(i<15){
		
		while(counter == N) ;
		lock(0);
		buf[in] = data++;
		printf("producing at index %d: %d\n", in, buf[in]);
		in = (in+1)%N;
		i++;
		counter++;
		unlock(0);
	}
	pthread_exit(0);
}

void *consumer(void *args){

	int data,i = 0;

	while(i<15){
		while(counter == 0);
		lock(1);
		data = buf[out];
		printf("consuming at index %d: %d\n", out, buf[out]);
		out = (out+1)%N;
		i++;
		counter--;
		unlock(1);
		//sleep(1);
	}
	pthread_exit(0);
}