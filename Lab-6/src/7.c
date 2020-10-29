#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

#define ITRS 100000

int num_s=0, num_c=0;
void* runner (void* args);
int whereIsPoint(float x, float y);

int main (){

	pthread_t tid[8];

	for(int i=0; i<8; i++){
		pthread_create(&tid[i], NULL, runner, NULL);
	}

	for(int i=0; i<8; i++){
		pthread_join(tid[i], NULL);
	}

	float pi = 4.0 * num_c / num_s;

	printf("%d:%d Approximate Value of PI = %f\n", num_s, num_c, pi);

	return 0;

}

int whereIsPoint(float x, float y){

	float distance = sqrt((x*x) + (y*y));

	if(distance < 1)
		return 1;
	else
		return 0;

}

void* runner (void* args){

	time_t t;
	srand((unsigned) time(&t));
	float x, y;
	for(int i=0; i<ITRS; i++){
		x = (float)rand() / RAND_MAX;
		y = (float)rand() / RAND_MAX;

		if(whereIsPoint(x, y)){
			num_c += 1;
		}
	}

	num_s += ITRS;
	return NULL;
}