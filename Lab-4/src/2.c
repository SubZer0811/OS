#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void merge_sort(int arr[], int s, int e);
void merge(int arr[], int s, int mid, int e);

int main (){

	key_t key = ftok("merge_sort", 8);
	int shmid = shmget(key,sizeof(int)*20,0666|IPC_CREAT);
	int *arr = shmat(shmid, 0, 0);

	int array[] = {3, 1, 5, 2, 3, 6, 8, 5, 9, 0}, n = sizeof(array)/sizeof(int);

	printf("Input Array: ");
	for(int i=0; i<n; i++){
		printf("%d ", array[i]);
		arr[i] = array[i];
	}
	printf("\n");

	merge_sort(arr, 0, n-1);

	printf("Output Array: ");
	for(int i=0; i<n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	shmdt(arr);
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}

void merge(int arr[], int s, int mid, int e){

	int temp[e-s+1];
	int i = 0;
	int l = s;
	int r = mid+1;
	while( l<=mid && r<=e ){

		if(arr[l] < arr[r]){
			temp[i] = arr[l];
			l++; i++;
		}
		else if(arr[l] > arr[r]){
			temp[i] = arr[r];
			r++; i++;
		}
		else if(arr[l] == arr[r]){
			temp[i] = arr[r];
			i++; r++;
			temp[i] = arr[l];
			i++; l++;
		}
	}

	while(l <= mid){
		temp[i] = arr[l];
		i++; l++;
	}

	while(r <= e){
		temp[i] = arr[r];
		i++; r++;
	}

	for(int j=0; j<i; j++){
		arr[s+j] = temp[j];
	}
}

void merge_sort(int arr[], int s, int e){

	if(s < e){

		int mid = (s + e)/2;
	
		pid_t right_pid, left_pid;
		left_pid = fork();

		if(left_pid == 0){
			merge_sort(arr, s, mid);
			exit(0);
		}
		else{
			right_pid = fork();
			if(right_pid == 0){
				merge_sort(arr, mid+1, e);
				exit(0);
			}
		}

		int status;

		waitpid(left_pid, &status, 0);
		waitpid(right_pid, &status, 0);
		
		merge(arr, s, mid, e);

	}
}