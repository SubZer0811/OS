#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct mmm {		// stands for mean median mode
	int arr[100], n, median, mode;
	float mean;
};

void* mean (void*);
void* median (void*);
void* mode (void*);

int main(int argc, char const *argv[]){

	// int array[100]={0}, n=0, i=0, j=0, temp=0;
	struct mmm args;
	
	args.n = atoi(argv[1]);
	for(int i=0; i<args.n; i++){
		args.arr[i] = atoi(argv[i+2]);
	}

	// Initialize elements of args
	args.mean = 0;
	args.median = 0;
	args.mode = 0;

	// Sort the array
	for(int i=0; i<args.n; i++){
		for(int j=0; j<args.n-1; j++){
			if(args.arr[j] > args.arr[j+1]){
				int temp = args.arr[j];
				args.arr[j] = args.arr[j+1];
				args.arr[j+1] = temp;
			}
		}
	}

	struct mmm* args_ptr = &args;
	pthread_t tid[3];
	pthread_create(&tid[0], NULL, mean, args_ptr);
	pthread_create(&tid[1], NULL, median, args_ptr);
	pthread_create(&tid[2], NULL, mode, args_ptr);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	printf("Mean: %f\nMedian: %d\nMode: %d\n", args.mean, args.median, args.mode);

	return 0;
}

void* mean (void* args){
	struct mmm* arg = (struct mmm*)args;

	for(int i=0; i<arg->n; i++){
		arg->mean += arg->arr[i];
	}
	arg->mean /= arg->n;
	return NULL;
}

void* median (void* args){
	struct mmm* arg = (struct mmm*)args;
	arg->median = arg->arr[arg->n/2];
	return NULL;
}

void* mode (void* args){
	struct mmm* arg = (struct mmm*)args;

	int max_count = 0, count = 1, curr = arg->arr[0];
	arg->mode = arg->arr[0];
	for(int i=1; i<arg->n; i++){
		if(arg->arr[i] != curr){
			if(count > max_count){
				max_count = count;
				arg->mode = curr;
			}
			curr = arg->arr[i];
			count = 1;
		}
		else{
			count += 1;
		}
	}
	return NULL;
}
