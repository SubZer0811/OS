#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main (){

	int A[][3] = {
				{3, 1, 5},
				{2, 7, 9},
				{4, 1, 2}
				};

	int B[][2] = {
				{1, 1},
				{3, 1},
				{0, 1}
				};

	int const m=3, n=3, p=3, q=2; // n = p;

	int prod[m][q], sum=0;

	for(int c=0; c<m; c++){
		for(int d=0; d<q; d++){
			for(int k=0; k<p; k++){
				pid_t pid = vfork();
				if(pid == 0){
					sum = sum + A[c][k] * B[k][d];
					exit(0);
				}
			}
			prod[c][d] = sum;
			sum = 0;
		}
	}

	for(int i=0; i<m; i++){
		for(int j=0; j<q; j++){
			printf("%d ", prod[i][j]);
		}
		printf("\n");
	}

	return 0;
}