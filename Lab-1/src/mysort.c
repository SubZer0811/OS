/*
This program is for question 2 of the programming assignment.
*/

#include<stdio.h>
#include<stdlib.h>

typedef int (*comp) (int a, int b);

char help[] = "[!] Invalid Input:\nCorrect usage: ./mysort <n> <q> <arr>\nwhere\nn : number of elements in array\nq = 1 : Sort in Ascending Order, q = 0 : Sort in Descending Order\narr : n space seperated integers\n";

void sort (int *array, int n, comp cmp){

	int i=0, j=0, temp=0;

	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
			if(cmp(array[j], array[j+1]) > 0){
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

int ascd (int a, int b){
	return a-b;
}

int desc (int a, int b){
	return b-a;
}

int main (int argc, char* argv[]){

	if(argc == 1 || argc == 2 || argc == 3){
		printf("%s", help);
		exit(-1);
	}

	int n = argc - 3, i=0;

	if(atoi(argv[1]) != n){
		printf("%s", help);
		exit(-1);
	}

	int *array = malloc(n*sizeof(int));

	for(i=0; i<n; i++)
		array[i] = atoi(argv[i+3]);

	if(atoi(argv[2]) == 1){
		sort(array, n, ascd);
		printf("\n-----Sorted in Ascending Order-----\n");
	}
	else if(atoi(argv[2]) == 0){
		sort(array, n, desc);
		printf("\n-----Sorted in Descending Order-----\n");
	}
	else{
		printf("%s", help);
		exit(-1);
	}
	
	for(i=0; i<n; i++)
		printf("%d ", array[i]);

	printf("\n\n");
	return 0;
}