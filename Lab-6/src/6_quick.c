#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct arguments{
	int b, e, k; 
};

void* runner(void*);
void swap(int*, int*);
void quicksort(int [], int, int, int);
int partition (int [], int, int);

int n, arr[20], k;

int main(int argc,char *argv[]){

	if(argc < 3){
		printf("Invalid input\n");
		exit(0);
	}

	n=atoi(argv[1]);
	if(argc != n+2){
		printf("Invalid input\n");
		exit(0);
	}
	
	for(int i=0; i<n; i++){
		arr[i] = atoi(argv[i+2]);
	} 

	k = n;
	quicksort(arr, 0, n-1, k);

	printf("Sorted array:\n");

	for(int i=0; i<k; i++)
		printf("%d ", arr[i]); 

	printf("\n");
	return 0;
}

void* runner(void* param){

	struct arguments* p=(struct arguments*)param;
	quicksort(arr, p->b, p->e, p->k);
	return NULL;
}

void swap(int* a, int* b){ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
}

int partition (int arr[], int low, int high){
	int pivot = arr[high];    
	int i = (low - 1);   
  
	for (int j = low; j <= high- 1; j++){
	   	if (arr[j] < pivot){ 
			i++;     
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i+1], &arr[high]); 
	return i+1; 
} 
  
void quicksort(int arr[], int low, int high,int k){ 

	if (high>low){
		int q = partition(arr, low, high);  

		struct arguments p, r;

		p.b = low;
		p.e = q-1;
		p.k = k;

		r.b = q+1;
		r.e = high;
		r.k = k;

		pthread_t tid[2];
		
		pthread_create(&tid[0], NULL, runner, &p);
		pthread_create(&tid[1], NULL, runner, &r);

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);
	} 
} 