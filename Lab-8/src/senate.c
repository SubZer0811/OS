#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define MAX_RIDERS 10

pthread_mutex_t mutex;	
sem_t riders_waiting; //multiplex
sem_t bus_arrival;   //bus
sem_t bus_depart;    //all_aboard
int waiting = 0;

void * rider(){

	while(1){		
		
		sem_wait(&riders_waiting);
		pthread_mutex_lock(&mutex);		
		waiting = waiting + 1;
		printf("[RIDERS]: riders waiting = %d \n", waiting);
		sleep(1);
		pthread_mutex_unlock(&mutex); 		
		sem_wait(&bus_arrival);						
		sem_post(&riders_waiting);
			
		printf("RIDER: bus is here. \n riders waiting: %d \n", waiting--);					
		sleep(1);
		if(waiting == 0){
			sem_post(&bus_depart);
		}else{
			sem_post(&bus_arrival);
		}	
	}
}

void * bus(){	
	while(1){
		sem_wait(&riders_waiting);
		printf("Bus arrived \t waiting: %d\n", waiting);
		pthread_mutex_lock(&mutex);			
		if(waiting > 0){
			sem_post(&bus_arrival);
			sem_wait(&bus_depart);
		}
		printf("[->] BUS: departing! \n[!]riders waiting: %d \n", waiting);
		pthread_mutex_unlock(&mutex);				
		sleep(1);
	}
}


void main(int argc,  char * argv[]){
	
	pthread_t  riders [MAX_RIDERS];
	pthread_t b1;
	
	pthread_mutex_init(&mutex, NULL);
	sem_init(&riders_waiting, 0, 50);
	sem_init(&bus_arrival, 0, 0);
	sem_init(&bus_depart, 0, 0);
	
	int t_id;
	pthread_create(&b1, NULL, bus, NULL);
	for(t_id=0; t_id< MAX_RIDERS ;t_id++){
		pthread_create(&riders[t_id], NULL, rider, NULL);
	}

	for(t_id=0; t_id< MAX_RIDERS ;t_id++){
		pthread_join(riders[t_id], NULL);
	}
	
	pthread_join(b1, NULL);
}