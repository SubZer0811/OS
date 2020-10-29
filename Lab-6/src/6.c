#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<pthread.h>

struct arguments
{
	int s, e;
};


void* merge_sort(void*);
void merge(int s, int mid, int e);
void copy_arguments (const struct arguments*, struct arguments*);

int array[] = {9, 8, 7, 4, 1, 3, 2, 5}, n = sizeof(array)/sizeof(int);

int main (){


	struct arguments* args = (struct arguments*)malloc(sizeof(struct arguments));

	printf("Input Array: ");
	for(int i=0; i<n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");

	args->s = 0; args->e = n-1;
	merge_sort(args);

	printf("Output Array: ");
	for(int i=0; i<n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	
	return 0;
}

void merge(int s, int mid, int e){

	int temp[e-s+1];
	int i = 0;
	int l = s;
	int r = mid+1;
	while( l<=mid && r<=e ){

		if(array[l] < array[r]){
			temp[i] = array[l];
			l++; i++;
		}
		else if(array[l] > array[r]){
			temp[i] = array[r];
			r++; i++;
		}
		else if(array[l] == array[r]){
			temp[i] = array[r];
			i++; r++;
			temp[i] = array[l];
			i++; l++;
		}
	}

	while(l <= mid){
		temp[i] = array[l];
		i++; l++;
	}

	while(r <= e){
		temp[i] = array[r];
		i++; r++;
	}

	for(int j=0; j<i; j++){
		array[s+j] = temp[j];
	}

}

void* merge_sort(void* arg){

	struct arguments* args = (struct arguments*)arg;

	if(args->s < args->e){

		int mid = (args->s + args->e)/2;
	
		pthread_t right_tid, left_tid;

		struct arguments* left_args = (struct arguments*)malloc(sizeof(struct arguments));
		struct arguments* right_args = (struct arguments*)malloc(sizeof(struct arguments));

		copy_arguments(args, left_args);
		left_args->e = mid;

		copy_arguments(args, right_args);
		right_args->s = mid+1;

		pthread_create(&left_tid, NULL, merge_sort, left_args);
		pthread_create(&right_tid, NULL, merge_sort, right_args);

		pthread_join(left_tid, NULL);
		pthread_join(right_tid, NULL);
		
		merge(args->s, mid, args->e);

	}
}

void copy_arguments (const struct arguments* src, struct arguments* dest){
	dest->s = src->s;
	dest->e = src->e;
}
