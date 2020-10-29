#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

struct arguments
{
	int arr[10];
	int n;
	int opt;
};

void* sort (void *arg){
	
	struct arguments* args = (struct arguments*)arg;
	int opt = args->opt;
	if(args->opt){
		printf("Descending Array:      ");
	}
	else{
		printf("Ascending Array:       ");
	}
	
	for(int i=0; i<args->n; i++){
		for(int j=1; j<args->n-i; j++){
			if(((opt*(args->arr[j] < args->arr[j-1])) + ((1-opt)*(args->arr[j] > args->arr[j-1])))){
				args->arr[j] += args->arr[j-1];
				args->arr[j-1] = args->arr[j] - args->arr[j-1];
				args->arr[j] -= args->arr[j-1];
			}
		}
	}
	
	for(int i=0; i<args->n; i++)
		printf("%d ", args->arr[i]);
	printf("\n");

	pthread_exit(NULL);
}

int main (){

	struct arguments arg_asc, arg_dsc;

	printf("Enter size of array: ");
	scanf("%d", &arg_asc.n);

	printf("Enter elements of array: ");
	for(int i=0; i<arg_asc.n; i++)
		scanf("%d", &arg_asc.arr[i]);

	printf("Original Array:        ");
	for(int i=0; i<arg_asc.n; i++)
		printf("%d ", arg_asc.arr[i]);
	printf("\n");

	arg_dsc = arg_asc;

	struct arguments *asc_ptr=&arg_asc, *dsc_ptr=&arg_dsc;
	pthread_t asc, dsc;
	
	arg_asc.opt = 1;
	pthread_create(&asc, NULL, sort, asc_ptr);
	arg_dsc.opt = 0;
	pthread_create(&dsc, NULL, sort, dsc_ptr);
	
	pthread_join(asc, NULL);
	pthread_join(dsc, NULL);

	return 0;

}