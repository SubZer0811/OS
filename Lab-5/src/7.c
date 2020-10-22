#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

struct arguments{
	int arr[20];
	int start;
	int end;
	int key;
};

pthread_t threads[100];
int itr=0;

void* binary_search (void *);

int main (){

	struct arguments *args = (struct arguments *)malloc(sizeof(struct arguments));
	int n;
	printf("Enter size of array: ");
	scanf("%d", &n);

	printf("Enter elements of array: ");
	for(int i=0; i<n; i++)
		scanf("%d", &args->arr[i]);

	printf("Enter key to search for: ");
	scanf("%d", &args->key);

	args->end = n;
	args->start = 0;

	binary_search(args);

	for(int i=0; i<itr; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;

}

void* binary_search (void* a){

	struct arguments* args = (struct arguments*) a;
	int mid = (args->end + args->start)/2;
	int end = args->end, start = args->start;

	if(args->start > args->end){
		return NULL;
	}
	if(args->start == args->end){
		if(args->arr[mid] == args->key){
			printf("Key found at address: %d\n", mid);
		}
		return NULL;
	}
	if(args->start+1 == args->end){

			args->end=args->start;
			pthread_create(&threads[itr], NULL, binary_search, args);itr++;

			args->start=args->end=end;
			pthread_create(&threads[itr], NULL, binary_search, args);itr++;
			args->start=start; args->end=end;
	}
	if(args->arr[mid] == args->key){
		printf("Key found at address: %d\n", mid);
	}
	
		args->end = mid-1;
		binary_search(args);
		pthread_create(&threads[itr], NULL, binary_search, args);itr++;
	
		args->start = mid+1;
		args->end = end;
		binary_search(args);
		pthread_create(&threads[itr], NULL, binary_search, args);itr++;
}