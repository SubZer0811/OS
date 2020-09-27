#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main (){

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 
  
	// shmget returns an identifier in shmid 
	int shmid = shmget(key,5*sizeof(int),0666|IPC_CREAT); 
  
	// shmat to attach to shared memory 
	int *arr = shmat(shmid, 0, 0);

	arr[0] = 0; arr[1] = 1; arr[2] = 2; arr[3] = 3; arr[4] = 4;

	pid_t pid = fork();

	if(pid == 0){
		arr[0] = 10; arr[1] = 11; arr[2] = 12; arr[3] = 13; arr[4] = 14;
	}
	else{
		for(int i=0; i<5; i++){
			printf("%d ", arr[i]);
		}
		sleep(2);
		for(int i=0; i<5; i++){
			printf("%d ", arr[i]);
		}
		shmdt(arr);
		shmctl(shmid,IPC_RMID,NULL); 
	}
	

	return 0;
}