#include<iostream>

using namespace std;

typedef float (*comp) (float a, float b);

float ascd (float a, float b){
	return a-b;
}
float desc (float a, float b){
	return b-a;
}

template<class DT>
class sorter{
	
	public:
	comp cmp;
	void sort (DT *array, int n, bool opt){
		
		int i=0, j=0;
		DT temp;
		cmp = (opt)?ascd:desc;

		for(i=0; i<n; i++){
			for(j=0; j<n-1; j++){
				if(cmp(float(array[j]), float(array[j+1])) > 0){
					temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
		if(cmp == ascd){
			printf("\n-----Sorted in Ascending Order-----\n");
		}
		else{
			printf("\n-----Sorted in Descending Order-----\n");
		}
		for(i=0; i<n; i++)
			cout<<array[i]<<" ";
	}
};

char help[] = "[!] Invalid Input:\nCorrect usage: ./smartsort <t> <n> <q> <arr>\nwhere\nt : type of array : c - character, i - integer, f - float\nn : number of elements in array\nq = 1 : Sort in Ascending Order, q = 0 : Sort in Descending Order\narr : n space seperated integers\n";

void validate(int argc, char* argv[]){

	if(argc == 1 || argc == 2 || argc == 3 || argc == 4){
		printf("%s", help);
		exit(-1);
	}
	if(atoi(argv[2]) != argc-4){
		printf("%s", help);
		exit(-1);
	}
	switch(argv[1][0]){
		case 'c':break;
		case 'i':break;
		case 'f':break;
		default: printf("%s", help); exit(-1);
	}
	if(!(atoi(argv[3]) == 0 || atoi(argv[3]) == 1)){
		printf("%s", help);
		exit(-1);
	}


}

int main(int argc, char* argv[]){

	validate(argc, argv);

	int n = argc - 4, i=0;

	switch(argv[1][0]){

		case 'c':{
			char *array = new char [n];
			for(i=0; i<n; i++)
				array[i] = argv[i+4][0];
			sorter<char> sortaa;
			sortaa.sort(array, n, atoi(argv[3]));
			break;
		}
		case 'i':{
			int *array = new int [n];
			for(i=0; i<n; i++)
				array[i] = atoi(argv[i+4]);
			sorter<int> sortaa;
			sortaa.sort(array, n, atoi(argv[3]));
			break;
		}
		case 'f':{
			float *array = new float [n];
			for(i=0; i<n; i++)
				array[i] = atof(argv[i+4]);
			sorter<float> sortaa;
			sortaa.sort(array, n, atoi(argv[3]));
			break;
		}
		default:
			printf("%s", help); exit(-1);
	}

	printf("\n\n");
	return 0;
}