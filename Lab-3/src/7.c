#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void binary_search (int [], int, int, int);

int main (){

	int arr[] = {3, 1, 5, 2, 5, 2, 6, 4, 7, 9, 5, 3, 5}, n = sizeof(arr)/sizeof(int);
	int key = 5;
	binary_search(arr, 0, n, key);

	return 0;

}

void binary_search (int arr[], int start, int end, int key){

	int mid = (end + start)/2;

	if(start > end){
		return;
	}
	if(start == end){
		if(arr[mid] == key){
			printf("Key found at address: %d\n", mid);
		}
		return;
	}
	if(start+1 == end){
		binary_search(arr, start, start, key);
		binary_search(arr, end, end, key);
	}
	if(arr[mid] == key){
		printf("Key found at address: %d\n", mid);
	}
	
	pid_t pid = fork();
	if(pid == 0){
		binary_search(arr, start, mid-1, key);
	}
	else{
		binary_search(arr, mid+1, end, key);
	}

}