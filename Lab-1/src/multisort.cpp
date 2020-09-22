#include<stdio.h>
#include<stdlib.h>

typedef int (*comp) (int a, int b);

char help[] = "[!] Invalid Input:\nCorrect usage: ./mysort <t> <n> <q> <arr>\nwhere\nt : type of array : c - character, i - integer, f - float\nn : number of elements in array\nq = 1 : Sort in Ascending Order, q = 0 : Sort in Descending Order\narr : n space seperated integers\n";

//Functions needed for integer sorting
void integer (int argc, char* argv[]);
void sort (int *array, int n, comp cmp);
int ascd (int a, int b);
int desc (int a, int b);

//Functions needed for float sorting
void floating (int argc, char* argv[]);
void sort (float *array, int n, comp cmp);
float ascd (float a, float b);
float desc (float a, float b);

//Functions needed for character sorting
void character (int argc, char* argv[]);
void sort (char *array, int n, comp cmp);
int ascd (char a, char b);
int desc (char a, char b);

int main (int argc, char* argv[]){

	if(argc == 1 || argc == 2 || argc == 3 || argc == 4){
		printf("%s", help);
		exit(-1);
	}

	int n = argc - 4, i=0;

	if(atoi(argv[2]) != n){
		printf("%s", help);
		exit(-1);
	}

	char t = argv[1][0];
	switch(t){

		case 'c':{
				character(argc, argv);
				break;
		}
		case 'i':{
				integer(argc, argv);
				break;
		}

		case 'f':{
				floating(argc, argv);
				break;
		}

		default:	printf("%s", help); exit(-1);
	}

	printf("\n\n");
	return 0;
}

void integer (int argc, char* argv[]){

	int n = argc - 4, i=0, *array = new int [n];

	for(i=0; i<n; i++)
		array[i] = atoi(argv[i+4]);

	if(atoi(argv[3]) == 1){
		sort(array, n, ascd);
		printf("\n-----Sorted in Ascending Order-----\n");
	}
	else if(atoi(argv[3]) == 0){
		sort(array, n, desc);
		printf("\n-----Sorted in Descending Order-----\n");
	}
	else{
		printf("%s", help);
		exit(-1);
	}
	for(i=0; i<n; i++)
		printf("%d ", array[i]);

}

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

void floating (int argc, char* argv[]){

	int n = argc - 4, i=0;
	float *array = new float [n];

	for(i=0; i<n; i++)
		array[i] = atof(argv[i+4]);

	if(atoi(argv[3]) == 1){
		sort(array, n, ascd);
		printf("\n-----Sorted in Ascending Order-----\n");
	}
	else if(atoi(argv[3]) == 0){
		sort(array, n, desc);
		printf("\n-----Sorted in Descending Order-----\n");
	}
	else{
		printf("%s", help);
		exit(-1);
	}
	for(i=0; i<n; i++)
		printf("%f ", array[i]);

}

void sort (float *array, int n, comp cmp){

	int i=0, j=0;
	float temp;
	
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

float ascd (float a, float b){
	return a-b;
}

float desc (float a, float b){
	return b-a;
}

void character (int argc, char* argv[]){

	int n = argc - 4, i=0;
	char *array = new char [n];

	for(i=0; i<n; i++)
		array[i] = argv[i+4][0];

	if(atoi(argv[3]) == 1){
		sort(array, n, ascd);
		printf("\n-----Sorted in Ascending Order-----\n");
	}
	else if(atoi(argv[3]) == 0){
		sort(array, n, desc);
		printf("\n-----Sorted in Descending Order-----\n");
	}
	else{
		printf("%s", help);
		exit(-1);
	}
	for(i=0; i<n; i++)
		printf("%c ", array[i]);

}

void sort (char *array, int n, comp cmp){

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

int ascd (char a, char b){
	return a-b;
}

int desc (char a, char b){
	return b-a;
}